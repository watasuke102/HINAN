#!/usr/bin/env bash

if [[ ! -d build ]]; then
  mkdir build
fi

cd build
cmake -G Ninja -D CMAKE_BUILD_TYPE=Debug .. && clear && ninja
