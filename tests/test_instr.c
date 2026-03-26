#include "control.h"
#include "cpu/central.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdint.h>

void setUp(void) {
  // runs before each test
}

void tearDown(void) {
  // runs after each test
}

CPU init_and_run_program(uint8_t program[]) {
  CPU cpu = init_cpu();
  load(&cpu, program);
  run(&cpu);
  return cpu;
}

// LDA

void test_0xa9(void) {
  uint8_t exp = 0x55;
  uint8_t program[3] = {0xA9, exp, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.a);
}

void test_0xa5(void) {
  uint8_t exp = 0x55;
  uint8_t program[7] = {0xA2, exp, 0x86, 0x10, 0xA5, 0x10, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.a);
}

void test_0xb5(void) {
  uint8_t exp = 0x55;
  uint8_t program[9] = {0xA2, exp, 0x86, 0x13, 0xA2, 0x03, 0xB5, 0x10, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.a);
}

void test_0xad(void) {
  uint8_t exp = 0x55;
  uint8_t program[13] = {0xA2, exp, 0x8E, 0x22, 0x0C, 0xAD, 0x22, 0x0C, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.a);
}

void test_0xbd(void) {
  uint8_t exp = 0x55;
  uint8_t program[11] = {0xA2, exp,  0x8E, 0x23, 0x0C, 0xA2,
                         0x01, 0xBD, 0x22, 0x0C, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.a);
}

void test_0xb9(void) {
  uint8_t exp = 0x55;
  uint8_t program[11] = {0xA0, 0x01, 0xA2, exp,  0x8E, 0x89,
                         0x0F, 0xb9, 0x88, 0x0F, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(0x55, cpu.control.a);
}

void test_0xa1(void) {
  uint8_t exp = 0x55;
  uint8_t program[18] = {0xA2, 0x04, 0xA0, 0xFE, 0x84, 0x14, 0xA0, 0x07, 0x84,
                         0x15, 0xA0, exp,  0x8C, 0xFE, 0x07, 0xA1, 0x10, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.a);
}

void test_0xb1(void) {
  uint8_t exp = 0x55;
  uint8_t program[18] = {0xA0, 0x04, 0xA2, 0xFE, 0x86, 0x14, 0xA2, 0x07, 0x86,
                         0x15, 0xA2, exp,  0x8E, 0xFE, 0x07, 0xB1, 0x10, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.a);
}

// PHA

void test_0x48(void) {
  uint8_t exp = 0x10;
  uint8_t program[4] = {0xA9, exp, 0x48, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.memory[0x01FF]);
}

// PHP

void test_0x08(void) {
  uint8_t program[2] = {0x08, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(0b00110100, cpu.control.memory[0x01FF]);
}

// PLA

void test_0x68(void) {
  uint8_t program[3] = {0x08, 0x68, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(0b00110100, cpu.control.a);
}

// TAX

void test_0xaa(void) {
  uint8_t exp = 0x10;
  uint8_t program[4] = {0xA9, exp, 0xAA, 0x00};
  CPU cpu = init_and_run_program(program);
  TEST_ASSERT_EQUAL(exp, cpu.control.x);
}

int main(void) {
  UNITY_BEGIN();
  // LDA
  RUN_TEST(test_0xa9);
  RUN_TEST(test_0xa5);
  RUN_TEST(test_0xb5);
  RUN_TEST(test_0xad);
  RUN_TEST(test_0xbd);
  RUN_TEST(test_0xb9);
  RUN_TEST(test_0xa1);
  RUN_TEST(test_0xb1);
  // PHA
  RUN_TEST(test_0x48);
  // PHP
  RUN_TEST(test_0x08);
  // TLA
  RUN_TEST(test_0x68);
  // TAX
  RUN_TEST(test_0xaa);
  return UNITY_END();
}
