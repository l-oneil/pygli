cmake_minimum_required(VERSION 3.15...3.25)
project(pygli VERSION ${SKBUILD_PROJECT_VERSION})

# CMake Include's
include(ExternalProject)
include(FetchContent)

# Build Settings
set(CMAKE_CXX_STANDARD 17)
set(COMMON_FLAGS "")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "--debug -g ${COMMON_FLAGS} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${COMMON_FLAGS}")

# Third Party
add_subdirectory(external)

# Python Library
add_subdirectory(src)
