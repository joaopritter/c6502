#include "addr_mode.h"
#include "cpu/control.h"
#include <stdint.h>

uint16_t IMM(Control *c) { return c->counter++; };

uint16_t ABS(Control *c) {
  uint16_t lo, hi, addr;

  lo = mem_read(c, c->counter++);
  hi = mem_read(c, c->counter++);

  addr = lo + (hi << 8);

  return addr;
};

uint16_t IMP(Control *c) { return 0; };
