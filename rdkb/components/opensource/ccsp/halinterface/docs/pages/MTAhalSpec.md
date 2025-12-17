@mainpage

# MTA HAL Documentation




# Version and Version History


1.0.0 Initial Revision covers existing MTA HAL implementation.

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture

# Description
The diagram below describes a high-level software architecture of the MTA HAL module stack. 

![MTA HAL Architecture Diag](mta_hal_architecture.png)

MTA HAL is an abstraction layer implemented to abstract the underlying MTA hardware and interact with the underlying voice vendor software through a standard set of APIs. An MTA can deliver Home Phone service in addition to High speed internet.
 
# Component Runtime Execution Requirements

## Initialization and Startup

The below mentioned APIs initialize the MTA HAL layers/code. MTA client module should call the mentioned APIs initially during bootup/initialization.

1. mta_hal_InitDB
2. mta_hal_start_provisioning

RDK MTA HAL doesn't mandates any predefined requirements for implementation of these API's. it is upto the 
3rd party vendors to handle it appropriately to meet operational requirements.

For Independent API's 3rd party implementation is expected to work without any prerequisties.

Failure to meet these requirements will likely result in undefined and unexpected behaviour.


## Threading Model

MTA HAL is not thread safe, any module which is invoking the MTA HAL api should ensure calls are made in a thread safe manner.

Different 3rd party vendors allowed to create internal threads to  meet the operational requirements. In this case 3rd party implementations should be responsible to synchronize between the calls, events and cleanup the thread.

## Process Model



## Memory Model

MTA HAL client module is responsible to allocate and deallocate memory for necessary APIs as specified in API documentation.
Different 3rd party vendors allowed to allocate memory for internal operational requirements. In this case 3rd party implementations should be responsible to deallocate internally.

## Power Management Requirements

The MTA HAL is not involved in any of the power management operation.
Any power management state transitions MUST not affect the operation of the MTA HAL.

## Asynchronous Notification Model

None

## Blocking calls

MTA HAL APIs are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant MTA specification. The APIs should probably just send a message to a driver event handler task. Any calls that can fail due to the lack of a response from connected device should have a timeout period in accordance with any relevant documentation. 

## Internal Error Handling

All the MTA HAL APIs should return error synchronously as a return argument. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. Application/Client is responsible to persist any settings related to MTA feature.


# Nonfunctional requirements

Following non functional requirement should be supported by the MTA HAL component.

## Logging and debugging requirements

MTA HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

## Memory and performance requirements

Make sure MTA HAL is not contributing more to memory and CPU utilization while performing normal MTA operations. Commensurate with the operation required.


## Quality Control

MTA HAL implementation should pass Coverity, Black duck scan, valgrind checks without any issue.

There should not be any memory leaks/corruption introduced by HAL and underneath 3rd party software implementation.

## Licensing

MTA HAL implementation is expected to released under the Apache License. 

## Build Requirements

MTA HAL source code should be build under Linux Yocto environment and should be delivered as a shared library libhal_mta.so
  

## Variability Management

Any new API introduced should be implemented by all the 3rd party module and RDK generic code should be compatible with specific version of MTA HAL software

## Platform or Product Customization

None

# Interface API Documentation

Covered as per Doxygen documentations.

## Theory of operation and key concepts

Covered as per "Description" sections.
All HAL function prototypes and datatype definitions are available in mta_hal.h file.
  1.  Components/Processes must include mta_hal.h to make use of MTA HAL capabilities
  2.  Components/Processes must include linker dependency for libhal platform.

### UML Diagrams

#### Sequence Diagram

![MTA Sequence Diagram](mta_hal_sequence.png)
