## Project Specs
cmake_minimum_required(VERSION 3.13)
set_property(TARGET PROPERTY C_STANDARD 11)
project(x86_to_riscv VERSION 0.1)
## Project Dependencies
include_directories(Main include zydis/include zydis/dependencies/zycore/include
        zydis/src zydis/dependencies/zycore/include)
add_executable(Main src/elfparse.c src/main.c)

include_directories(Zydis include zydis/include zydis/dependencies/zycore/include)
file(GLOB ZYDIS_SOURCE "zydis/src/*.c" "zydis/src/Generated/*.inc" "zydis/dependencies/zycore/src/*.c")
add_executable(Zydis src/zydis.c ${ZYDIS_SOURCE})
