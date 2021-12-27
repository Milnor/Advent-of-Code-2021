cmake_minimum_required(VERSION 3.17)
project(AoC2021 CXX)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

#add_link_options("-v")

add_executable(advent   src/main.cpp)

add_library(challenges SHARED
                        src/Submarine.cpp
                        src/day01.c
                        src/day02.c
                        src/day03.c)
                    target_link_libraries(advent PRIVATE challenges)

target_include_directories(advent PUBLIC "${CMAKE_SOURCE_DIR}/include/"
                                    PUBLIC "${CMAKE_SOURCE_DIR}/src/")
                                target_link_options(advent PUBLIC "-v")                                
