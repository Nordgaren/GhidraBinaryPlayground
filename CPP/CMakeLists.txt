cmake_minimum_required(VERSION 3.23)
set(PROJECT SampleBinaryCPP)
project(${PROJECT} CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT} main.cpp)
