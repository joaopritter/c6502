cmake_minimum_required(VERSION 3.16)

project(c6502 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.c
    src/addr_mode.c
    src/instr.c
    src/cpu/central.c
    src/cpu/control.c
    src/cpu/logic.c
)

add_executable(c6502 ${SOURCES})

target_include_directories(c6502 PRIVATE
    include
    include/cpu
)
