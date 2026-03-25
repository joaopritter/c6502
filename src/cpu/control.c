#include <stdint.h>

#include "cpu/control.h"

uint8_t mem_read(Control *c, uint16_t addr) {
  uint8_t val = c->memory[addr];
  return val;
}

void mem_write(Control *c, uint16_t addr, uint8_t value) {
  c->memory[addr] = value;
}
