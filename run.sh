#!/bin/bash

bash shaderbuild.sh
sudo rm -rf build
mkdir build
cd build
cmake -G Ninja -DCMAKE_CXX_COMPILER=/usr/bin/clang++ ..
ninja
./src/VulkanGuide