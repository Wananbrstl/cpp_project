#! /usr/bin/bash

cmake -B build -G Ninja
cmake --build build
cd build 
ctest  
cd ..
