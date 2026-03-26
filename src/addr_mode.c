#include "addr_mode.h"
#include "cpu/control.h"
#include <stdint.h>

uint16_t ACC(Control *c) { return 0; }

uint16_t IMM(Control *c) { return c->pc++; };

uint16_t ABS(Control *c) {
  uint8_t lo = mem_read(c, c->pc++);
  uint8_t hi = mem_read(c, c->pc++);
  return (uint16_t)(lo + (hi << 8));
};

uint16_t ABX(Control *c) {
  uint8_t lo = mem_read(c, c->pc++);
  uint8_t hi = mem_read(c, c->pc++);
  return (uint16_t)(lo + (hi << 8) + c->x);
}

uint16_t ABY(Control *c) {
  uint8_t lo = mem_read(c, c->pc++);
  uint8_t hi = mem_read(c, c->pc++);
  return (uint16_t)(lo + (hi << 8) + c->y);
}

uint16_t ZRX(Control *c) {
  uint8_t base = c->memory[c->pc++];
  return (base + c->x) & 0xFF;
}

uint16_t ZRY(Control *c) {
  uint8_t base = c->memory[c->pc++];
  return (base + c->y) & 0xFF;
}

uint16_t IND(Control *c) {
  uint8_t lo = mem_read(c, c->pc++);
  uint8_t hi = mem_read(c, c->pc++);
  return (uint16_t)(lo + (hi << 8));
}

uint16_t IDX(Control *c) {
  uint8_t arg = c->memory[c->pc++];
  uint8_t zerop_addr = (arg + c->x) & 0xFF;
  uint8_t lo = mem_read(c, zerop_addr);
  uint8_t hi = mem_read(c, (zerop_addr + 1) & 0xFF);
  return (uint16_t)(lo | (hi << 8));
}

uint16_t IDY(Control *c) {
  uint8_t arg = c->memory[c->pc++];
  uint8_t zerop_addr = (arg + c->y) & 0xFF;
  uint8_t lo = mem_read(c, zerop_addr);
  uint8_t hi = mem_read(c, (zerop_addr + 1) & 0xFF);
  return (uint16_t)(lo | (hi << 8));
}

uint16_t REL(Control *c) {
  uint8_t arg = c->memory[c->pc++];
  return (uint16_t)(c->pc + arg);
}

uint16_t IMP(Control *c) { return 0; };

uint16_t ZRP(Control *c) { return mem_read(c, c->pc++); }
