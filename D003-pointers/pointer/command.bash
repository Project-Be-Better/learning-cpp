#!/bin/bash

BUILD_DIR=build
EXECUTABLE=main

if [ "$1" == "clean" ]; then 
    echo "Cleaning up..."
    rm -rf "$BUILD_DIR"
fi 

mkdir -p "$BUILD_DIR" && cd "$BUILD_DIR" || exit 1

echo "Building..."

cmake ..
cmake --build .
echo "Running..."
./$EXECUTABLE
