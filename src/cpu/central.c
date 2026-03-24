#include <stdint.h>

#include "cpu/central.h"
#include "cpu/control.h"
#include "cpu/logic.h"

CPU cpu() {
  Control c;
  Logic l = logic();

  CPU cpu;
  cpu.control = c;
  cpu.logic = l;

  return cpu;
}

void load(CPU *cpu, uint8_t program[]) {
  int finish_loading = 0;
  for (int i = 0, mem = 0x8000; finish_loading == 0; i++, mem++) {
    uint8_t val = program[i];
    cpu->control.memory[mem] = val;
    if (val == 0x00) {
      finish_loading = 1;
    }
  }
}

void exec(CPU *cpu, OPCode c) {
  uint16_t addr = c.mode(&cpu->control);
  c.inst(&cpu->control, addr);
};

void run(CPU *cpu) {
  uint8_t value;
  OPCode inst;
  while (1) {
    value = mem_read(&cpu->control, cpu->control.counter);
    inst = decode(&cpu->logic, value);
    exec(cpu, inst);
  }
};
