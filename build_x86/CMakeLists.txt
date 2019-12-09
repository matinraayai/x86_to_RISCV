## Project Specs
cmake_minimum_required(VERSION 3.10)
set_property(TARGET PROPERTY C_STANDARD 11)
project(x86_to_riscv VERSION 0.1)
## Project Dependencies
### Zydis:
include_directories(Main ../zydis/include ../zydis/dependencies/zycore/include ../zydis/src)
file(GLOB ZYDIS_SOURCE "../zydis/src/*.c" "../zydis/src/Generated/*.inc" "../zydis/dependencies/zycore/src/*.c")
### Project:
include_directories(Main ../include)
file(GLOB PROJ_SOURCE "../src/*.c")
add_executable(main_x86 ${ZYDIS_SOURCE} ${PROJ_SOURCE})
### Example x86 Application
add_executable(fibonacci ../example/fibonacci.c)
