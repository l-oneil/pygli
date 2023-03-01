cmake_minimum_required(VERSION 3.10)
project(pygli)

# CMake Include's
include(ExternalProject)
include(FetchContent)

# Build Settings
set(CMAKE_CXX_STANDARD 17)
set(COMMON_FLAGS "-Wno-invalid-offsetof -Wall")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "--debug -g ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3 ${COMMON_FLAGS}")

# Third Party
add_subdirectory(external)

# Library
add_subdirectory(cpp)

# Python Wrapper
add_subdirectory(python)
