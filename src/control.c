#include <stdint.h>

#include "control.h"
#include "opcode.h"

uint8_t mem_read(C6502 *c, uint16_t addr) {
  uint8_t val = c->memory[addr];
  return val;
}

void mem_write(C6502 *c, uint16_t addr, uint8_t value) {
  c->memory[addr] = value;
}

uint16_t stack_address(uint8_t sp) { return (uint16_t)(STACK_START + sp); }

void stack_push(C6502 *c, uint8_t value) {
  c->memory[stack_address(c->sp)] = value;
  c->sp--;
}

uint8_t stack_pop(C6502 *c) {
  c->sp++;
  return c->memory[stack_address(c->sp)];
}

C6502 init_cpu() {
  C6502 cpu = {0};

  cpu.a = 0;
  cpu.x = 0;
  cpu.y = 0;
  cpu.sp = STACK_RESET;
  cpu.pc = 0x8000;
  cpu.status = 0b100100;
  return cpu;
}

void reset(C6502 *cpu) {
  cpu->a = 0;
  cpu->x = 0;
  cpu->y = 0;
  cpu->sp = STACK_RESET;
  cpu->pc = 0x8000;
  cpu->status = 0b100100;
}

void load(C6502 *cpu, uint8_t program[]) {
  int finish_loading = 0;

  for (int i = 0, mem = 0x8000; finish_loading == 0; i++, mem++) {
    uint8_t val = program[i];
    cpu->memory[mem] = val;
    if (val == 0x00) {
      finish_loading = 1;
    }
  }
  cpu->pc = 0x8000;
}

void run(C6502 *cpu) {
  uint8_t value;
  OPCode inst;

  cpu->running = 1;
  while (cpu->running == 1) {
    value = mem_read(cpu, cpu->pc);
    cpu->pc++;
    inst = decode(value);
    exec(cpu, inst);
  }
};
