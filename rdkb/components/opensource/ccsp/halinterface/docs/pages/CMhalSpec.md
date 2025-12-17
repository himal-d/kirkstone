# Broadband CM HAL Documentation




# Version and Version History


1.0.0 Initial Revision covers existing Broadband CM HAL implementation.

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture

# Description
The diagram below describes a high-level software architecture of the Broadband CM HAL module stack. 

![Broadband CM HAL Architecture Diag](broadband_cm_hal_architecture.png)

Broadband CM HAL is an abstraction layer implemented to abstract the underlying Cable Modem hardware and interact with the underlying vendor software through a standard set of APIs. CM HAL provides interfaces for integrating WAN interfaces with RDK-B. CM related parameters are fetched through CM HAL APIs. Mainly CcspCMAgent, GW provisioning processes are linked to CM HAL.
 
# Component Runtime Execution Requirements

## Initialization and Startup

The below mentioned APIs initialize the Broadband CM HAL layers/code. Broadband CM client module should call the mentioned APIs initially during bootup/initialization.

1. cm_hal_InitDB

CM HAL doesn't mandate any predefined requirements for implementation of these API's. It is upto the 3rd party vendors to handle it appropriately to meet operational requirements.

For Independent API's 3rd party implementation is expected to work without any prerequisties.

Failure to meet these requirements will likely result in undefined and unexpected behaviour.


## Threading Model

Broadband CM HAL is not thread safe, any module which is invoking the Broadband CM HAL API should ensure calls are made in a thread safe manner.

Different 3rd party vendors allowed to create internal threads to  meet the operational requirements. In this case 3rd party implementations should be responsible to synchronize between the calls, events and cleanup the thread.

## Process Model



## Memory Model

Broadband CM HAL client module is responsible to allocate and deallocate memory for necessary APIs as specified in API documentation.
Different 3rd party vendors allowed to allocate memory for internal operational requirements. In this case 3rd party implementations should be responsible to deallocate internally.

## Power Management Requirements

The Broadband CM HAL is not involved in any of the power management operation.
Any power management state transitions MUST not affect the operation of the Broadband CM HAL.

## Asynchronous Notification Model

None

## Blocking calls

Broadband CM HAL APIs are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant Broadband CM specification. The APIs should probably just send a message to a driver event handler task. Any calls that can fail due to the lack of a response from connected device should have a timeout period in accordance with any relevant documentation. 

## Internal Error Handling

All the Broadband CM HAL APIs should return error synchronously as a return argument. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. Application/Client is responsible to persist any settings related to Broadband CM feature.


# Nonfunctional requirements

Following non functional requirement should be supported by the Broadband CM HAL component.

## Logging and debugging requirements

Broadband CM HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

## Memory and performance requirements

Make sure Broadband CM HAL is not contributing more to memory and CPU utilization while performing normal Broadband CM operations. Commensurate with the operation required.


## Quality Control

Broadband CM HAL implementation should pass Coverity, Black duck scan, valgrind checks without any issue.

There should not be any memory leaks/corruption introduced by HAL and underneath 3rd party software implementation.

## Licensing

Broadband CM HAL implementation is expected to released under the Apache License. 

## Build Requirements

Broadband CM HAL source code should be build under Linux Yocto environment and should be delivered as a shared library libcm_mgnt.so
  

## Variability Management

Any new API introduced should be implemented by all the 3rd party module and RDK generic code should be compatible with specific version of Broadband CM HAL software

## Platform or Product Customization

None

# Interface API Documentation

Covered as per Doxygen documentations.

## Theory of operation and key concepts

Covered as per "Description" sections.
All HAL function prototypes and datatype definitions are available in cm_hal.h file.
  1.  Components/Processes must include cm_hal.h to make use of Broadband CM HAL capabilities
  2.  Components/Processes must include linker dependency for libcm_mgnt.

### UML Diagrams

#### Sequence Diagram

![Broadband CM HAL Sequence Diagram](broadband_cm_hal_sequence.png)
