#!/bin/sh

mkdir -p build && cd build
CXX=clang++ CC=clang scan-build make ..
make -j4
