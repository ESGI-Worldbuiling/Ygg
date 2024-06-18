cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "20")
set(BUILD_SHARED_LIBS OFF)

project(Ygg VERSION 0.0.1 DESCRIPTION "A library for generative worldbuilding")

include(FetchContent)

option(YGG_BUILD_TESTS "Build tests for the Ygg library" ON)
option(YGG_BUILD_CLIENT "Build the Meior client" ON)

add_subdirectory(Libs)
add_subdirectory(Core)
add_subdirectory(Ygg)

if (YGG_BUILD_CLIENT)
    add_subdirectory(Meior)
endif()

if (YGG_BUILD_TESTS)
    add_subdirectory(Test)
endif ()
