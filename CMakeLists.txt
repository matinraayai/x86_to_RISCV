## Project Specs
cmake_minimum_required(VERSION 3.13)
project(x86_to_riscv VERSION 0.1)
## Project Dependencies
include_directories(src)
add_executable(Main src/main.c)
