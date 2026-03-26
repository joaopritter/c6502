#include "control.h"
#include <stdint.h>
#include <stdio.h>

// Sources and Refs:
// - https://www.nesdev.org/wiki/
// - https://bugzmanov.github.io/nes_ebook/
// - https://github.com/gianlucag/mos6502

int main(void) {
  uint8_t program[3] = {0xA9, 0xC0, 0x00};
  C6502 cpu = init_cpu();
  load(&cpu, program);
  printf("[CPU] A: %d | PC: %d\n", cpu.a, cpu.pc);
  run(&cpu);
  printf("[CPU] A: %d | PC: %d\n", cpu.a, cpu.pc);
  return 0;
}
