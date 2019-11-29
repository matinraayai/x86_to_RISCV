## Project Specs
cmake_minimum_required(VERSION 3.13)
project(x86_to_riscv VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
## Project Dependencies
include_directories(src/loader)
add_executable(Main src/main.cpp)
