#include "control.h"
#include "cpu/central.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {
  // runs before each test
}

void tearDown(void) {
  // runs after each test
}

void test_0xa9(void) {
  CPU cpu = init_cpu();
  uint8_t program[3] = {0xA9, 0x05, 0x00};
  load(&cpu, program);
  run(&cpu);
  TEST_ASSERT_EQUAL(cpu.control.a, 0x05);
}

void test_0xa5(void) {
  CPU cpu = init_cpu();
  mem_write(&cpu.control, 0x10, 0x55);
  uint8_t program[3] = {0xA5, 0x10, 0x00};
  load(&cpu, program);
  run(&cpu);
  TEST_ASSERT_EQUAL(cpu.control.a, 0x55);
}

void test_0xad(void) {
  CPU cpu = init_cpu();
  mem_write(&cpu.control, 0x0C22, 0x55);
  uint8_t program[4] = {0xAD, 0x22, 0x0C, 0x00};
  load(&cpu, program);
  run(&cpu);
  TEST_ASSERT_EQUAL(cpu.control.a, 0x55);
}

void test_0xaa(void) {
  CPU cpu = init_cpu();
  cpu.control.a = 10;
  uint8_t program[2] = {0xAA, 0x00};
  load(&cpu, program);
  run(&cpu);
  TEST_ASSERT_EQUAL(cpu.control.x, 10);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_0xa9);
  RUN_TEST(test_0xa5);
  RUN_TEST(test_0xad);
  RUN_TEST(test_0xaa);
  return UNITY_END();
}
