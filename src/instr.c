#include <stdint.h>

#include "cpu/control.h"
#include "cpu/flags.h"
#include "instr.h"

void LDA(Control *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->a = param;
  assign_nz_flags(c, c->a);
};

void LDX(Control *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->x = param;
  assign_nz_flags(c, c->x);
}

void LDY(Control *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->y = param;
  assign_nz_flags(c, c->y);
}

void TAX(Control *c, uint16_t addr) {
  c->x = c->a;
  assign_nz_flags(c, c->x);
}

void PHA(Control *c, uint16_t addr) { stack_push(c, c->a); }

void PHP(Control *c, uint16_t addr) {
  uint8_t flags = c->status;
  // The B flag and extra bit are both pushed as 1.
  flags |= BREAK_FLAG;
  flags |= EXTRA_FLAG;
  stack_push(c, flags);
  assign_break_flag(c, 1);
}

void PLA(Control *c, uint16_t addr) {
  uint8_t val = stack_pop(c);
  c->a = val;
  assign_nz_flags(c, val);
}

void STA(Control *c, uint16_t addr) { mem_write(c, addr, c->a); }

void STX(Control *c, uint16_t addr) { mem_write(c, addr, c->x); }

void STY(Control *c, uint16_t addr) { mem_write(c, addr, c->y); }

void BRK(Control *c, uint16_t addr) { c->running = 0; };

void ILL(Control *c, uint16_t addr) { c->running = 0; };
