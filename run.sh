#!/bin/bash

bash shaderbuild.sh
rm -rf build
mkdir build
cd build
sudo cmake -G Ninja -DCMAKE_CXX_COMPILER=/usr/bin/clang++ ..