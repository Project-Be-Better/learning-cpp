#!/bin/bash

docker build -t teletrack_dev -f Dockerfile .

docker run --rm -it \
  -v $(pwd)/..:/app \
  -w /app \
  teletrack_dev \
  bash -c "
    rm -rf build &&
    mkdir -p build &&
    conan profile detect --force &&
    conan install . -of=build --build=missing --conf tools.cmake.cmaketoolchain:generator=False &&
    cmake -S. -Bbuild \
      -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
      -DCMAKE_BUILD_TYPE=Release &&
    cmake --build build &&
    ./build/teletrack_sim
  "
