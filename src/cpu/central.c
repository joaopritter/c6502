#include <stdint.h>

#include "cpu/central.h"
#include "cpu/control.h"
#include "cpu/logic.h"

CPU init_cpu() {
  CPU cpu = {0};

  cpu.control.a = 0;
  cpu.control.x = 0;
  cpu.control.y = 0;
  cpu.control.sp = STACK_RESET;
  cpu.control.pc = 0x8000;
  cpu.control.status = 0b100100;
  cpu.logic = init_logic();
  return cpu;
}

void reset(CPU *cpu) {
  cpu->control.a = 0;
  cpu->control.x = 0;
  cpu->control.y = 0;
  cpu->control.sp = STACK_RESET;
  cpu->control.pc = 0x8000;
  cpu->control.status = 0b100100;
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
  cpu->control.pc = 0x8000;
}

void exec(CPU *cpu, OPCode c) {
  uint8_t program_counter_state = cpu->control.pc;
  uint16_t addr = c.mode(&cpu->control);
  c.inst(&cpu->control, addr);
  if (cpu->control.pc == program_counter_state) {
    cpu->control.pc += (c.size - 1);
  }
};

void run(CPU *cpu) {
  uint8_t value;
  OPCode inst;

  cpu->control.running = 1;
  while (cpu->control.running == 1) {
    value = mem_read(&cpu->control, cpu->control.pc);
    cpu->control.pc++;
    inst = decode(&cpu->logic, value);
    exec(cpu, inst);
  }
};
