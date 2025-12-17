##
cmake_minimum_required(VERSION 3.2)
project(lxccpid)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES_LXCCPID_BIN *.cpp lxccpid/*.cpp)
include_directories(.)
SET(EXECUTABLE_OUTPUT_PATH bin)

add_executable(lxccpid ${SOURCE_FILES_LXCCPID_BIN})
target_link_libraries(lxccpid pthread)
