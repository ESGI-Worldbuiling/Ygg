cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "20")

project(Ygg VERSION 0.0.1 DESCRIPTION "A library for generative worldbuilding")

include(FetchContent)

add_subdirectory(Libs)
add_subdirectory(Ygg)

option(YGG_ENABLE_TESTS "Enable tests for the Ygg library" ON)

if (YGG_ENABLE_TESTS)
    add_subdirectory(Test)
endif ()