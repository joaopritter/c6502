#include "addr_mode.h"
#include "cpu/control.h"
#include <stdint.h>

uint16_t IMM(Control *c) { return c->counter++; };

uint16_t ABS(Control *c) {
  uint8_t lo = mem_read(c, c->counter++);
  uint8_t hi = mem_read(c, c->counter++);
  return (uint16_t)(lo + (hi << 8));
};

uint16_t ABX(Control *c) {
  uint8_t lo = mem_read(c, c->counter++);
  uint8_t hi = mem_read(c, c->counter++);
  return (uint16_t)(lo + (hi << 8) + c->x);
}

uint16_t ABY(Control *c) {
  uint8_t lo = mem_read(c, c->counter++);
  uint8_t hi = mem_read(c, c->counter++);
  return (uint16_t)(lo + (hi << 8) + c->y);
}

uint16_t ZRX(Control *c) {
  uint8_t base = c->memory[c->counter++];
  return (base + c->x) & 0xFF;
}

uint16_t IMP(Control *c) { return 0; };

uint16_t ZRP(Control *c) { return mem_read(c, c->counter++); }
