# WAN HAL Documentation

# Version and Version History

1.0.0 Initial Revision covers existing WAN HAL implementation.

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture

# Description
The diagram below describes a high-level software architecture of the WAN HAL module stack. 

![WAN HAL Architecture Diag](images/WAN_HAL_Architetcture.png)

WAN HAL is an abstraction layer, implemented to interact with vendor software for setting the specific details such as modes, connection enable/disable, QoS configuration, Ipv4 config. etc.
This HAL layer is intended to be a common HAL,should be usable by any Ccspcomponents or Processes.

# Component Runtime Execution Requirements

## Initialization and Startup

Below Initialization API's provide opportunity for the HAL code to initialize the appropriate DB's, start threads etc. 

WAN HAL client module is expected to call the corresponding API Once during bootup before invoking Dependent API's.

1. wan_hal_Init()

RDK WAN HAL doesn't mandates any predefined requirements for implementation of these API's. it is upto the 
3rd party vendors to handle it appropriately to meet operational requirements.

For Independent API's 3rd party implementation is expected to work without any prerequisties.

Failure to meet these requirements will likely result in undefined and unexpected behaviour.

## Threading Model

WAN HAL is not thread safe, any module which is invoking the WAN HAL api should ensure calls are made in a thread safe manner.

Different 3rd party vendors allowed to create internal threads to meet the operational requirements. In this case 3rd party implementations
should be responsible to synchronize between the calls, events and cleanup the thread.

## Memory Model

WAN HAL client module is responsible to allocate and deallocate memory for necessary API's as specified in API Documentation.

Different 3rd party vendors allowed to allocate memory for internal operational requirements. In this case 3rd party implementations
should be responsible to deallocate internally.

## Power Management Requirements

The WAN HAL is not involved in any of the power management operation.
Any power management state transitions MUST not affect the operation of the WAN HAL. 

## Asynchronous Notification Model
None

## Blocking calls

WAN HAL API's are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant specification. 
Any calls that can fail due to the lack of a response should have a timeout period in accordance with any relevant documentation.

## Internal Error Handling

All the WAN HAL API's should return error synchronously as a return argument. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. Application/Client is responsible to persist any settings related to their implementation.


# Nonfunctional requirements

Following non functional requirement should be supported by the WAN HAL component.

## Logging and debugging requirements

WAN HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

## Memory and performance requirements

Make sure WAN HAL is not contributing more to memory and CPU utilization while performing normal operations and Commensurate with the operation required.


## Quality Control

WAN HAL implementation should pass Coverity, Black duck scan, valgrind checks without any issue.

There should not be any memory leaks/corruption introduced by HAL and underneath 3rd party software implementation.


## Licensing

WAN HAL implementation is expected to released under the Apache License. 

## Build Requirements

WAN HAL source code should be build under Linux Yocto environment and should be delivered as a shared library libhal_wan.so
  

## Variability Management

Any new API introduced should be implemented by all the 3rd party module and RDK generic code should be compatible with specific version of WAN HAL software

## WAN or Product Customization

None

## Interface API Documentation

Covered as per Doxygen documentations.

## Theory of operation and key concepts

Covered as per "Description" sections in the API documentation.

All HAL function prototypes and datatype definitions are available in WAN_hal.h file.
    
     1. Components/Process must include WAN_hal.h to make use of WAN hal capabilities.
     2. Components/Process should add linker dependency for libhal_wan.

### UML Diagrams

#### Sequence Diagram

![WAN HAL Sequence Diagram](WAN_HAL_Sequence_Diagram.png)
