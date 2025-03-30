#!/bin/bash
cd build || mkdir build && cd build
cmake ..
cmake --build .
echo "Running..."
./main
