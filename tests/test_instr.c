#include "cpu/central.h"
#include "unity.h"

void setUp(void) {
  // runs before each test
}

void tearDown(void) {
  // runs after each test
}

void test_tax(void) {
  CPU cpu = init_cpu();
  cpu.control.a = 10;
  uint8_t program[2] = {0xAA, 0x00};
  load(&cpu, program);
  run(&cpu);
  TEST_ASSERT_EQUAL(10, cpu.control.x);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_tax);
  return UNITY_END();
}
