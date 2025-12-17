@mainpage

# LPA HAL Documentation

# Version and Version History


1.0.0 Initial Revision covers existing Lpa HAL implementation.

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture
- `LPA` \- Local Profile Assistants

# Description
The diagram below describes a high-level software architecture of the Lpa HAL module stack. 

![Lpa HAL Architecture Diag](images/Lpa_HAL_Architecture.png)

Lpa HAL is an abstraction layer, implemented to interact with vendor software's for getting the details of the profiles on the eSIM.
This HAL layer is intended to be a common HAL,should be usable by any Ccspcomponents or Processes.

# Component Runtime Execution Requirements

## Initialization and Startup

There is no dependent API's is expected to be intialized for invoking Lpa HAL client module. But below api is used to setup the LPA SDK parameters
- `cellular_esim_lpa_init()`

RDK Lpa HAL doesn't mandates any predefined requirements for implementation of these API's. it is upto the 
3rd party vendors to handle it appropriately to meet operational requirements.

For Independent API's 3rd party implementation is expected to work without any prerequisties.

Failure to meet these requirements will likely result in undefined and unexpected behaviour.

## Threading Model

Lpa HAL is not thread safe, any module which is invoking the Lpa HAL api should ensure calls are made in a thread safe manner.

Different 3rd party vendors allowed to create internal threads to meet the operational requirements. In this case 3rd party implementations
should be responsible to synchronize between the calls, events and cleanup the thread.

## Memory Model

Lpa HAL client module is responsible to allocate and deallocate memory for necessary API's as specified in API Documentation.

Different 3rd party vendors allowed to allocate memory for internal operational requirements. In this case 3rd party implementations
should be responsible to deallocate internally.

## Power Management Requirements

The Lpa HAL is not involved in any of the power management operation.
Any power management state transitions MUST not affect the operation of the Lpa HAL. 

## Asynchronous Notification Model
None

## Blocking calls

Lpa HAL API's are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant specification. 
Any calls that can fail due to the lack of a response should have a timeout period in accordance with any relevant documentation.

## Internal Error Handling

All the Lpa HAL API's should return error synchronously as a return argument. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. Application/Client is responsible to persist any settings related to their implementation.

# Nonfunctional requirements

Following non functional requirement should be supported by the Lpa HAL component.

## Logging and debugging requirements

Lpa HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

## Memory and performance requirements

Make sure Lpa HAL is not contributing more to memory and CPU utilization while performing normal operations and Commensurate with the operation required.


## Quality Control

Lpa HAL implementation should pass Coverity, Black duck scan, valgrind checks without any issue.

There should not be any memory leaks/corruption introduced by HAL and underneath 3rd party software implementation.


## Licensing

Lpa HAL implementation is expected to released under the Apache License. 

## Build Requirements

Lpa HAL source code should be build under Linux Yocto environment and should be delivered as a shared library libesim_lpa.la.
  
## Variability Management

Any new API introduced should be implemented by all the 3rd party module and RDK generic code should be compatible with specific version of Lpa HAL software

## Platform or Product Customization

None

## Interface API Documentation

All HAL function prototypes and datatype definitions are available in lpa_hal.h file.
    
     1. Components/Process must lpa_hal.h to make use of Lpa hal capabilities.
     2. Components/Process should add linker dependency for libesim_lpa.la.

## Theory of operation and key concepts

Covered as per "Description" sections in the API documentation.

#### Sequence Diagram

```mermaid
sequenceDiagram
participant Caller
participant Lpa HAL
participant Vendor
Caller->>Lpa HAL: Modem_XXX()
Lpa HAL->>Vendor: 
Vendor ->>Lpa HAL: 
Lpa HAL->>Caller: Modem_XXX() return
```
