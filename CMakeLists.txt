## Project Specs
cmake_minimum_required(VERSION 3.13)
set_property(TARGET PROPERTY C_STANDARD 11)
project(x86_to_riscv VERSION 0.1)
## Project Dependencies
include_directories(include)
add_executable(Main src/elfparse.c src/helper.c src/main.c)
