#include <stdint.h>

#include "control.h"

uint8_t mem_read(Control *c, uint16_t addr) {
  uint8_t val = c->memory[addr];
  return val;
}

void mem_write(Control *c, uint16_t addr, uint8_t value) {
  c->memory[addr] = value;
}

uint16_t stack_address(uint8_t sp) { return (uint16_t)(STACK_START + sp); }

void stack_push(Control *c, uint8_t value) {
  c->memory[stack_address(c->sp)] = value;
  c->sp--;
}

uint8_t stack_pop(Control *c) {
  c->sp++;
  uint16_t addr = stack_address(c->sp);
  uint8_t value = c->memory[addr];
  // Eliminate garbage from previous stack address after retrieving.
  c->memory[addr] = 0;
  return value;
}
