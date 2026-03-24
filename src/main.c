#include "cpu/central.h"
#include <stdint.h>
#include <stdio.h>

int main(void) {
  uint8_t program[3] = {0xA9, 0xC0, 0x00};
  CPU cpu;
  load(&cpu, program);
  printf("[CPU] A: %d | PC: %d\n", cpu.control.a, cpu.control.counter);
  run(&cpu);
  printf("[CPU] A: %d | PC: %d\n", cpu.control.a, cpu.control.counter);
  return 0;
}
