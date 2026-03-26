cmake_minimum_required(VERSION 3.16)

project(c6502 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build unit tests" OFF)

set(LIB_SOURCES
    src/addr_mode.c
    src/instr.c
    src/cpu/central.c
    src/cpu/control.c
    src/cpu/logic.c
    src/cpu/flags.c
)

add_executable(c6502
    src/main.c
    ${LIB_SOURCES}
)

target_include_directories(c6502 PRIVATE
    include
    include/cpu
)

if(BUILD_TESTING)
  set(UNITY_DIR ${CMAKE_SOURCE_DIR}/extern/Unity/src)

  set(UNITY_SOURCES
        ${UNITY_DIR}/unity.c
    )

  set(TEST_SOURCES
        tests/test_instr.c
    )

  add_executable(c6502_tests
        ${UNITY_SOURCES}
        ${TEST_SOURCES}
        ${LIB_SOURCES}
    )

  target_include_directories(c6502_tests PRIVATE
        include
        include/cpu
        ${UNITY_DIR}
    )

  enable_testing()
  add_test(NAME c6502_tests COMMAND $<TARGET_FILE:c6502_tests>)

  add_custom_target(run_tests
        COMMAND $<TARGET_FILE:c6502_tests>
        DEPENDS c6502_tests
        COMMENT "Running c6502 unit tests manually..."
    )
endif()
