cmake_minimum_required(VERSION 3.0.0)
project(example)

find_package(pybind11 REQUIRED HINTS /home/sergiovaneg/miniconda3/include/)
find_package(Eigen3 REQUIRED)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIRS})
include_directories(SYSTEM /home/sergiovaneg/miniconda3/include/python3.9)

pybind11_add_module(example example.cpp)