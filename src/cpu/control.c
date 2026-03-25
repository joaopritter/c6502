#include <stdint.h>

#include "cpu/control.h"

uint8_t mem_read(Control *c, uint16_t addr) {
  uint8_t val = c->memory[addr];
  return val;
}

void update_zero_and_negative_flags(Control *c, uint8_t result) {
  if (result) {
    c->flag = c->flag | 0b00000010;
  } else {
    c->flag = c->flag & 0b11111101;
  }

  if ((result & 0b10000000) != 0) {
    c->flag = c->flag | 0b10000000;
  } else {
    c->flag = c->flag & 0b01111111;
  }
}
