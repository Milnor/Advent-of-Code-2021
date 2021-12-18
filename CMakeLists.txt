cmake_minimum_required(VERSION 3.17)
project(AoC2021 C CXX)

#[==[
include_directories("${CMAKE_SOURCE_DIR}/include" 
	"${CMAKE_SOURCE_DIR}/src")
#]==]

add_executable(advent   src/main.cpp)
#                        src/Submarine.cpp)

target_include_directories(advent PUBLIC "${CMAKE_SOURCE_DIR}/include/")
