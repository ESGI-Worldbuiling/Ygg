cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "20")

project(Ygg VERSION 0.0.1 DESCRIPTION "A library for generative worldbuilding")

add_subdirectory(Libs)
add_subdirectory(Ygg)