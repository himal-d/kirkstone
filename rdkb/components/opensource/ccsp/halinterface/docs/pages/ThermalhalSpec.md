@mainpage

# Fan and Thermal HAL Documentation




# Version and Version History


1.0.0 Initial Revision covers existing Fan and Thermal HAL implementation.

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture

# Description
The diagram below describes a high-level software architecture of the Fan and Thermal HAL module stack. 

![Fan And Thermal HAL Architecture Diag](fan_thermal_hal_architecture.png)

Fan and Thermal HAL is an abstraction layer implemented to abstract the underlying hardware and interact with the underlying vendor software through a standard set of APIs to get hardware specific details such as fan status, fan speed, fan temperature, radio temperature, input current, input power etc. It can also set the fan speeds and MaxOverride parameter(Set the fan to maximum speed) and perform power monitoring functions.
 
# Component Runtime Execution Requirements

## Initialization and Startup

The below mentioned APIs initialize the Thermal HAL layers/code. Fan and Thermal HAL client module should call the mentioned APIs initially during bootup/initialization.

1. platform_hal_initThermal
2. platform_hal_LoadThermalConfig

RDK Thermal HAL doesn't mandate any predefined requirements for implementation of these API's. it is upto the 
3rd party vendors to handle it appropriately to meet operational requirements.

For Independent API's 3rd party implementation is expected to work without any prerequisties.

Failure to meet these requirements will likely result in undefined and unexpected behaviour.


## Threading Model

Fan and Thermal HAL is not thread safe, any module which is invoking the Thermal HAL api should ensure calls are made in a thread safe manner.

Different 3rd party vendors allowed to create internal threads to  meet the operational requirements. In this case 3rd party implementations should be responsible to synchronize between the calls, events and cleanup the thread.


## Memory Model

Fan and Thermal HAL client module is responsible to allocate and deallocate memory for necessary APIs as specified in API documentation.
Different 3rd party vendors allowed to allocate memory for internal operational requirements. In this case 3rd party implementations should be responsible to deallocate internally.

## Power Management Requirements

Fan and Thermal HAL contains the following APIs for power monitoring.

1. platform_hal_getInputCurrent - To get input current
2. platform_hal_getInputPower - To get input power


## Asynchronous Notification Model

None

## Blocking calls

Thermal HAL API's are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant specification.
Any calls that can fail due to the lack of a response should have a timeout period in accordance with any relevant documentation.

## Internal Error Handling

All the Fan and Thermal HAL APIs should return error synchronously as a return argument. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. Application/Client is responsible to persist any settings related to their implementation.


# Nonfunctional requirements

Following non functional requirement should be supported by the Fan and Thermal HAL component.

## Logging and debugging requirements

Fan and Thermal HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

## Memory and performance requirements

Make sure Thermal HAL is not contributing more to memory and CPU utilization while performing normal operations. Commensurate with the operation required.


## Quality Control

Fan and Thermal HAL implementation should pass Coverity, Black duck scan, valgrind checks without any issue.

There should not be any memory leaks/corruption introduced by HAL and underneath 3rd party software implementation.

## Licensing

Fan and Thermal HAL implementation is expected to released under the Apache License. 

## Build Requirements

Fan and Thermal HAL source code should be build under Linux Yocto environment and should be delivered as a shared library libhal_thermal
  

## Variability Management

Any new API introduced should be implemented by all the 3rd party module and RDK generic code should be compatible with specific version of Fan and Thermal HAL software

## Platform or Product Customization

None

# Interface API Documentation

Covered as per Doxygen documentations.

## Theory of operation and key concepts

Covered as per "Description" sections.
All Thermal HAL function prototypes and datatype definitions are available in platform_hal.h file.
  1.  Components/Processes must include platform_hal.h to make use of Fan and Thermal HAL capabilities
  2.  Components/Processes must include linker dependency for libhal thermal.

### UML Diagrams

#### Sequence Diagram

![Fan and Thermal HAL Sequence Diagram](fan_thermal_hal_sequence.png)
