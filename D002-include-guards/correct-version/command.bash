#!/bin/bash
rm -rf build
cd build || mkdir build && cd build
cmake ..
cmake --build .
echo "Running..."
./main
