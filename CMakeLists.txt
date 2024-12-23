cmake_minimum_required(VERSION 3.27)
project(ReedSolomonCodes)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ReedSolomonCodes
        main.cpp
        polynomial.cpp
        polynomial.hpp)
