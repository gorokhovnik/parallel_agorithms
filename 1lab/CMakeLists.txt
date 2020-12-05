cmake_minimum_required(VERSION 3.17)
project(1lab)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

add_executable(1lab main.cpp Serial.cpp Serial.h Parallel.cpp Parallel.h)