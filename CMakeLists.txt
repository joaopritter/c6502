cmake_minimum_required(VERSION 3.16)

project(cmos6502 C)

set(CMAKE_C_STANDARD 99)

set(SOURCES
    src/main.c
    src/addr_mode.c
    src/instr.c
    src/cpu/central.c
    src/cpu/control.c
    src/cpu/logic.c
)

add_executable(game_C ${SOURCES})

target_include_directories(game_C PRIVATE
    include
    include/cpu
)
