#include "addr_mode.h"
#include "control.h"
#include <stdint.h>

uint16_t ACC(C6502 *c) { return 0; }

uint16_t IMM(C6502 *c) { return c->pc++; };

uint16_t ABS(C6502 *c) {
  uint8_t lo = mem_read(c, c->pc++);
  uint8_t hi = mem_read(c, c->pc++);
  return (uint16_t)(lo + (hi << 8));
};

uint16_t ABX(C6502 *c) {
  uint8_t lo = mem_read(c, c->pc++);
  uint8_t hi = mem_read(c, c->pc++);
  return (uint16_t)(lo + (hi << 8) + c->x);
}

uint16_t ABY(C6502 *c) {
  uint8_t lo = mem_read(c, c->pc++);
  uint8_t hi = mem_read(c, c->pc++);
  return (uint16_t)(lo + (hi << 8) + c->y);
}

uint16_t ZRX(C6502 *c) {
  uint8_t base = c->memory[c->pc++];
  return (base + c->x) & 0xFF;
}

uint16_t ZRY(C6502 *c) {
  uint8_t base = c->memory[c->pc++];
  return (base + c->y) & 0xFF;
}

uint16_t IND(C6502 *c) {
  uint8_t ptr_lo = mem_read(c, c->pc++);
  uint8_t ptr_hi = mem_read(c, c->pc++);
  uint16_t ptr = (ptr_hi << 8) | ptr_lo;

  uint8_t lo = mem_read(c, ptr);
  uint16_t hi_addr = (ptr & 0xFF00) | ((ptr + 1) & 0x00FF); // 6502 hardware bug
  uint8_t hi = mem_read(c, hi_addr);

  return (hi << 8) | lo;
}

uint16_t IDX(C6502 *c) {
  uint8_t arg = c->memory[c->pc++];
  uint8_t zerop_addr = (arg + c->x) & 0xFF;
  uint8_t lo = mem_read(c, zerop_addr);
  uint8_t hi = mem_read(c, (zerop_addr + 1) & 0xFF);
  return (uint16_t)(lo | (hi << 8));
}

uint16_t IDY(C6502 *c) {
  uint8_t arg = c->memory[c->pc++];
  uint8_t zerop_addr = (arg + c->y) & 0xFF;
  uint8_t lo = mem_read(c, zerop_addr);
  uint8_t hi = mem_read(c, (zerop_addr + 1) & 0xFF);
  return (uint16_t)(lo | (hi << 8));
}

uint16_t REL(C6502 *c) {
  int8_t arg = (int8_t)mem_read(c, c->pc++);
  return (uint16_t)(c->pc + arg);
}

uint16_t IMP(C6502 *c) { return 0; };

uint16_t ZRP(C6502 *c) { return mem_read(c, c->pc++); }
