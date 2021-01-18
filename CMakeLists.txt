cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collabserver-example-mindmap)
message(STATUS "Building project ${PROJECT_NAME}")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# Compiler Flags
message(STATUS "Detected Operating System: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "No CMAKE_BUILD_TYPE set for ${PROJECT_NAME}: uses default Release")
    message(WARNING "Available build types: Debug Release RelWithDebInfo MinSizeRel")
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "CMAKE_BUILD_TYPE for ${PROJECT_NAME}: ${CMAKE_BUILD_TYPE}")


# Dependencies
message(STATUS "Adding dependencies for ${PROJECT_NAME}")
include_directories("${PROJECT_SOURCE_DIR}/gitmodules/collabserver-datatypes/include")
add_subdirectory("${PROJECT_SOURCE_DIR}/gitmodules/collabserver-datatypes")


# Executable
message(STATUS "Building executable")
include_directories("${PROJECT_SOURCE_DIR}/src/")
file(GLOB_RECURSE srcFilesExecutable "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME}-exe ${srcFilesExecutable})
add_custom_target(run ${PROJECT_NAME}-exe)
