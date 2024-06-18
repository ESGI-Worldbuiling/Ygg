#!/bin/bash

# This script is mainly used for Github Actions.

if [ ! -d "build" ]; then
    mkdir build
else
    rm -rf build
    mkdir build
fi

echo -e "\e[33mBuilding CMake project\e[0m"

cmake -B ./build -S ./ -DYGG_BUILD_CLIENT=OFF -DYGG_BUILD_TESTS=ON

echo -e "\e[33mFinished with succes building CMake project\e[0m"