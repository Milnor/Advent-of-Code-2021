#!/bin/sh

mkdir -p build && cd build
CXX=clang++ CC=clang scan-build make ..
VERBOSE=1 make -j4
