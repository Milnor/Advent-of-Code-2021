#!/bin/sh

mkdir -p build && cd build
CXX=clang++ CC=clang scan-build -DCMAKE_BUILD_TYPE=Debug make ..
VERBOSE=1 make -j4
