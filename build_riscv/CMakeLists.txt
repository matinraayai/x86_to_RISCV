## Project Specs
cmake_minimum_required(VERSION 3.10)
set_property(TARGET PROPERTY C_STANDARD 11)
project(x86_to_riscv VERSION 0.1)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_CXX_COMPILER "riscv64-unknown-elf-g++")
set(CMAKE_C_COMPILER "riscv64-unknown-elf-gcc")
set(CMAKE_ASM_COMPILER "riscv64-unknown-elf-gcc")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
## Project Dependencies
### Zydis:
include_directories(Main ../zydis/include ../zydis/dependencies/zycore/include ../zydis/src)
file(GLOB ZYDIS_SOURCE "../zydis/src/*.c" "../zydis/src/Generated/*.inc" "../zydis/dependencies/zycore/src/*.c")
### Project:
include_directories(Main ../include)
file(GLOB PROJ_SOURCE "../src/*.c")
add_executable(main_riscv ${ZYDIS_SOURCE} ${PROJ_SOURCE})
