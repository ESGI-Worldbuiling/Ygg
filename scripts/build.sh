#!/bin/bash

# This script is mainly used for Github Actions.

if [ ! -d "build" ]; then
    mkdir build
else
    rm -rf build
    mkdir build
fi

echo "Building CMake project"

cmake -B ./build -S ./ -DYGG_BUILD_CLIENT=OFF -DYGG_BUILD_TESTS=ON

cd build && make

echo "Finished with success building CMake project"