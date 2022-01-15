cmake_minimum_required(VERSION 3.13.1)

## Project options
option(BUILD_TESTING "Build tests" OFF)
option(BUILD_POSIX_NATIVE "Build as POSIX native target" ON)

## Global setup
if(BUILD_POSIX_NATIVE)
    set(BOARD "native_posix")
    add_definitions("-DTARGET_POSIX_NATIVE")
else()
    message(STATUS "Board not supported for now")
endif()

if(BUILD_TESTING)
    set(BUILD_TESTS ON)
endif()

if(NOT DEFINED APP_NAME)
    set(APP_NAME "app1")
endif()

## Check whether ccache exists for faster compile
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

## Find project dependencies
# Setup Zephyr RTOS
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Zephyr 2.7.0)

## Project setup (must be called after zephyr setup)
project(zephyr-application VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## Add source code
add_subdirectory(src)