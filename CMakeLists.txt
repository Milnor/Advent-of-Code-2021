cmake_minimum_required(VERSION 3.17)
project(AoC2021 CXX)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

add_executable(advent   src/main.cpp)
#                        src/Submarine.cpp)

target_include_directories(advent PUBLIC "${CMAKE_SOURCE_DIR}/include/")
