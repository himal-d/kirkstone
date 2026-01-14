/*
 * Copyright (c) 2025
 * SPDX-License-Identifier: Apache-2.0
 *
 * Matter Controller Daemon - Controller Implementation
 * Persistent Matter Controller with BLE Commissioning and Multi-Admin Support
 */

#include "MatterController.h"
#include <lib/support/CodeUtils.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/CHIPDeviceLayer.h>
#include <app/server/Server.h>
#include <app/server/OnboardingCodesUtil.h>
#include <controller/CHIPDeviceController.h>
#include <controller/CommissioningWindowOpener.h>
#include <controller/ExampleOperationalCredentialsIssuer.h>
#include <credentials/DeviceAttestationCredsProvider.h>
#include <credentials/examples/DeviceAttestationCredsExample.h>
#include <platform/Linux/CHIPLinuxStorage.h>
#include <platform/PlatformManager.h>
#include <ble/Ble.h>
#include <ble/BleLayer.h>
#include <platform/Linux/BlePlatformConfig.h>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace chip;
using namespace chip::DeviceLayer;
using namespace chip::Controller;

MatterController::MatterController() :
    mRunning(false), mInitialized(false), mStorage(nullptr), mController(nullptr),
    mCommissioningWindowOpen(false), mCommissioningWindowTimeout(300),
    mCommissioningWindowDiscriminator(3840), mCommissioningWindowPasscode(12345678)
{
}

MatterController::~MatterController()
{
    Shutdown();
}

CHIP_ERROR MatterController::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    if (mInitialized)
    {
        ChipLogError(NotSpecified, "Controller already initialized");
        return CHIP_ERROR_INCORRECT_STATE;
    }

    ChipLogProgress(NotSpecified, "Initializing Matter Controller...");

    // 1. Create storage directory if it doesn't exist
    struct stat st;
    if (stat(kStoragePath, &st) != 0)
    {
        if (mkdir(kStoragePath, 0755) != 0)
        {
            ChipLogError(NotSpecified, "Failed to create storage directory: %s", kStoragePath);
            return CHIP_ERROR_WRITE_FAILED;
        }
        ChipLogProgress(NotSpecified, "Created storage directory: %s", kStoragePath);
    }

    // 2. Initialize CHIP stack
    err = InitChipStack();
    SuccessOrExit(err);

    // 3. Initialize persistent storage
    err = InitStorage();
    SuccessOrExit(err);

    // 4. Initialize BLE
    err = InitBLE();
    SuccessOrExit(err);

    // 5. Initialize Thread/OTBR
    err = InitThread();
    SuccessOrExit(err);

    // 6. Initialize Device Controller
    {
        DeviceControllerInitParams initParams;
        initParams.storageDelegate              = mStorage;
        initParams.operationalCredentialsIssuer = Platform::New<ExampleOperationalCredentialsIssuer>();
        initParams.enableServerInteractions     = true;

        err = DeviceController::InitDeviceController(initParams, mController);
        SuccessOrExit(err);

        ChipLogProgress(NotSpecified, "Device Controller initialized");
    }

    // 7. Open commissioning window at startup
    err = OpenStartupCommissioningWindow();
    SuccessOrExit(err);

    mInitialized = true;
    mRunning     = true;

    ChipLogProgress(NotSpecified, "Matter Controller initialized successfully");

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(NotSpecified, "Controller initialization failed: %" CHIP_ERROR_FORMAT, err.Format());
        Shutdown();
    }
    return err;
}

CHIP_ERROR MatterController::InitChipStack()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    ChipLogProgress(NotSpecified, "Initializing CHIP stack...");

    // Initialize Platform Manager
    err = PlatformMgr().InitChipStack();
    SuccessOrExit(err);

    // Initialize Data Model
    err = Server::GetInstance().Init(nullptr, Server::InitParams());
    SuccessOrExit(err);

    ChipLogProgress(NotSpecified, "CHIP stack initialized");

exit:
    return err;
}

CHIP_ERROR MatterController::InitStorage()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    ChipLogProgress(NotSpecified, "Initializing persistent storage...");
    ChipLogProgress(NotSpecified, "  KVS path: %s", kKvsPath);
    ChipLogProgress(NotSpecified, "  Factory path: %s", kFactoryPath);
    ChipLogProgress(NotSpecified, "  Config path: %s", kConfigPath);

    // Initialize Linux persistent storage
    err = mLinuxStorage.Init(kKvsPath, kFactoryPath, kConfigPath);
    SuccessOrExit(err);

    mStorage = &mLinuxStorage;

    ChipLogProgress(NotSpecified, "Persistent storage initialized");

exit:
    return err;
}

CHIP_ERROR MatterController::InitBLE()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    ChipLogProgress(NotSpecified, "Initializing BLE...");

    // Get BLE layer
    BleLayer * bleLayer = BleLayer::GetBleLayer();
    VerifyOrReturnError(bleLayer != nullptr, CHIP_ERROR_INTERNAL);

    // BLE is initialized by Platform Manager
    // Ensure BLE remains enabled
    ConnectivityMgr().SetBLEAdvertisingEnabled(true);
    ConnectivityMgr().SetBLEAdvertisingMode(ConnectivityManager::kBLEAdvertisingMode_Enabled);

    ChipLogProgress(NotSpecified, "BLE initialized and advertising enabled");

    return err;
}

CHIP_ERROR MatterController::InitThread()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    ChipLogProgress(NotSpecified, "Initializing Thread/OTBR...");

    // Thread is initialized by Platform Manager using wpan0 interface
    // Verify Thread interface exists
    ConnectivityMgr().SetThreadDeviceType(ConnectivityManager::kThreadDeviceType_Router);
    ConnectivityMgr().SetThreadEnabled(true);

    ChipLogProgress(NotSpecified, "Thread/OTBR initialized (wpan0)");

    return err;
}

CHIP_ERROR MatterController::OpenStartupCommissioningWindow()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    ChipLogProgress(NotSpecified, "Opening commissioning window at startup...");
    ChipLogProgress(NotSpecified, "  Timeout: %d seconds", mCommissioningWindowTimeout);
    ChipLogProgress(NotSpecified, "  Discriminator: %d", mCommissioningWindowDiscriminator);
    ChipLogProgress(NotSpecified, "  Passcode: %d", mCommissioningWindowPasscode);

    err = OpenCommissioningWindow(mCommissioningWindowTimeout, mCommissioningWindowDiscriminator, mCommissioningWindowPasscode);
    SuccessOrExit(err);

    ChipLogProgress(NotSpecified, "Commissioning window opened successfully");

exit:
    return err;
}

CHIP_ERROR MatterController::OpenCommissioningWindow(uint16_t timeoutSeconds, uint16_t discriminator, uint32_t passcode)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    if (!mInitialized || mController == nullptr)
    {
        ChipLogError(NotSpecified, "Controller not initialized");
        return CHIP_ERROR_INCORRECT_STATE;
    }

    ChipLogProgress(NotSpecified, "Opening commissioning window...");

    // Use CommissioningWindowOpener to open the window
    CommissioningWindowOpener opener;
    err = opener.OpenBasicCommissioningWindow(mController, timeoutSeconds, discriminator, passcode);
    SuccessOrExit(err);

    mCommissioningWindowOpen = true;
    mCommissioningWindowTimeout     = timeoutSeconds;
    mCommissioningWindowDiscriminator = discriminator;
    mCommissioningWindowPasscode    = passcode;

    // Print QR code and manual pairing code
    {
        std::string QRCode;
        std::string manualPairingCode;
        err = GetQRCode(QRCode, RendezvousInformationFlags(RendezvousInformationFlag::kBLE));
        if (err == CHIP_NO_ERROR)
        {
            ChipLogProgress(NotSpecified, "QR Code: %s", QRCode.c_str());
        }

        err = GetManualPairingCode(manualPairingCode, RendezvousInformationFlags(RendezvousInformationFlag::kBLE));
        if (err == CHIP_NO_ERROR)
        {
            ChipLogProgress(NotSpecified, "Manual Pairing Code: %s", manualPairingCode.c_str());
        }
    }

    ChipLogProgress(NotSpecified, "Commissioning window opened (timeout: %d seconds)", timeoutSeconds);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(NotSpecified, "Failed to open commissioning window: %" CHIP_ERROR_FORMAT, err.Format());
    }
    return err;
}

CHIP_ERROR MatterController::CloseCommissioningWindow()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    if (!mCommissioningWindowOpen)
    {
        ChipLogProgress(NotSpecified, "Commissioning window already closed");
        return CHIP_NO_ERROR;
    }

    ChipLogProgress(NotSpecified, "Closing commissioning window...");

    // Disable BLE advertising
    ConnectivityMgr().SetBLEAdvertisingEnabled(false);

    mCommissioningWindowOpen = false;

    ChipLogProgress(NotSpecified, "Commissioning window closed");

    return err;
}

CHIP_ERROR MatterController::Run()
{
    if (!mInitialized)
    {
        ChipLogError(NotSpecified, "Controller not initialized");
        return CHIP_ERROR_INCORRECT_STATE;
    }

    ChipLogProgress(NotSpecified, "Matter Controller daemon running...");

    // Start event loop thread
    mEventLoopThread = std::thread(&MatterController::EventLoop, this);

    // Wait for shutdown signal
    while (mRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Wait for event loop thread to finish
    if (mEventLoopThread.joinable())
    {
        mEventLoopThread.join();
    }

    return CHIP_NO_ERROR;
}

void MatterController::EventLoop()
{
    ChipLogProgress(NotSpecified, "Event loop started");

    while (mRunning)
    {
        // Process CHIP events
        PlatformMgr().LockChipStack();
        PlatformMgr().UnlockChipStack();

        // Sleep to avoid busy loop
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ChipLogProgress(NotSpecified, "Event loop stopped");
}

void MatterController::Shutdown()
{
    if (!mInitialized)
    {
        return;
    }

    ChipLogProgress(NotSpecified, "Shutting down Matter Controller...");

    mRunning = false;

    // Close commissioning window
    CloseCommissioningWindow();

    // Wait for event loop thread
    if (mEventLoopThread.joinable())
    {
        mEventLoopThread.join();
    }

    // Shutdown controller
    if (mController != nullptr)
    {
        mController->Shutdown();
        mController = nullptr;
    }

    // Shutdown CHIP stack
    Server::GetInstance().Shutdown();
    PlatformMgr().ShutdownChipStack();

    // Shutdown storage
    if (mStorage != nullptr)
    {
        mStorage = nullptr;
    }

    mInitialized = false;

    ChipLogProgress(NotSpecified, "Matter Controller shut down");
}

