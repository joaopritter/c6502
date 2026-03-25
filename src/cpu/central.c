#include <stdint.h>

#include "cpu/central.h"
#include "cpu/control.h"
#include "cpu/logic.h"

CPU init_cpu() {
  CPU cpu = {0};
  cpu.logic = init_logic();
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
  cpu->control.counter = 0x8000;
}

void exec(CPU *cpu, OPCode c) {
  uint8_t program_counter_state = cpu->control.counter;
  uint16_t addr = c.mode(&cpu->control);
  c.inst(&cpu->control, addr);
  if (cpu->control.counter == program_counter_state) {
    cpu->control.counter += (c.size - 1);
  }
};

void run(CPU *cpu) {
  uint8_t value;
  OPCode inst;
  while (1) {
    value = mem_read(&cpu->control, cpu->control.counter);
    cpu->control.counter++;
    inst = decode(&cpu->logic, value);
    exec(cpu, inst);
  }
};
