cmake_minimum_required(VERSION 3.16)

project(c6502 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build unit tests" OFF)
option(ENABLE_COVERAGE "Enable coverage instrumentation" OFF)

set(LIB_SOURCES
    src/addr_mode.c
    src/instr.c
    src/control.c
    src/logic.c
    src/flags.c
)

add_executable(c6502
    src/main.c
    ${LIB_SOURCES}
)

target_include_directories(c6502 PRIVATE
    include
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
        ${UNITY_DIR}
    )

  enable_testing()
  add_test(NAME c6502_tests COMMAND $<TARGET_FILE:c6502_tests>)

  add_custom_target(run_tests
        COMMAND $<TARGET_FILE:c6502_tests>
        DEPENDS c6502_tests
        COMMENT "Running c6502 unit tests manually..."
    )

  if(ENABLE_COVERAGE)
    message(STATUS "Coverage instrumentation enabled")

    target_compile_options(c6502_tests PRIVATE -O0 -g --coverage)
    target_link_options(c6502_tests PRIVATE --coverage)

    find_program(LCOV_EXEC lcov)
    find_program(GENHTML_EXEC genhtml)

    if(NOT LCOV_EXEC OR NOT GENHTML_EXEC)
      message(WARNING "lcov/genhtml not found, coverage target will not work")
    else()
      add_custom_target(coverage
          COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
          --target c6502_tests

          COMMAND $<TARGET_FILE:c6502_tests>
          COMMAND ${LCOV_EXEC} --capture --directory ${CMAKE_BINARY_DIR}
          --base-directory ${CMAKE_SOURCE_DIR} --output-file
          ${CMAKE_BINARY_DIR}/coverage.info --ignore-errors source

          COMMAND ${LCOV_EXEC} --remove ${CMAKE_BINARY_DIR}/coverage.info
          '${CMAKE_SOURCE_DIR}/extern/*' --output-file
          ${CMAKE_BINARY_DIR}/coverage.info --ignore-errors unused

          COMMAND ${GENHTML_EXEC} ${CMAKE_BINARY_DIR}/coverage.info
          --output-directory ${CMAKE_BINARY_DIR}/coverage_report

          COMMENT "Building tests, running them, and generating coverage report"

          DEPENDS c6502_tests
      )
    endif()
  endif()
endif()
