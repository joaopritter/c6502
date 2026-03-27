#include <stdint.h>

#include "control.h"
#include "flags.h"
#include "instr.h"

void BRK(C6502 *c, uint16_t addr) { c->running = 0; };

void LDA(C6502 *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->a = param;
  assign_nz_flags(c, c->a);
};

void LDX(C6502 *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->x = param;
  assign_nz_flags(c, c->x);
}

void LDY(C6502 *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->y = param;
  assign_nz_flags(c, c->y);
}

void PHA(C6502 *c, uint16_t addr) { stack_push(c, c->a); }

void PHP(C6502 *c, uint16_t addr) {
  uint8_t flags = c->status;
  // The B flag and extra bit are both pushed as 1.
  flags |= BREAK_FLAG;
  flags |= EXTRA_FLAG;
  stack_push(c, flags);
  assign_break_flag(c, 1);
}

void PLA(C6502 *c, uint16_t addr) {
  uint8_t val = stack_pop(c);
  c->a = val;
  assign_nz_flags(c, val);
}

void SED(C6502 *c, uint16_t addr) { assign_decimal_flag(c, 1); }

void SEI(C6502 *c, uint16_t addr) { assign_interrupt_disable_flag(c, 1); }

void STA(C6502 *c, uint16_t addr) { mem_write(c, addr, c->a); }

void STX(C6502 *c, uint16_t addr) { mem_write(c, addr, c->x); }

void STY(C6502 *c, uint16_t addr) { mem_write(c, addr, c->y); }

void TAX(C6502 *c, uint16_t addr) {
  c->x = c->a;
  assign_nz_flags(c, c->x);
}

void TAY(C6502 *c, uint16_t addr) {
  c->y = c->a;
  assign_nz_flags(c, c->y);
}

void TSX(C6502 *c, uint16_t addr) {
  c->x = c->sp;
  assign_nz_flags(c, c->x);
}

void TXA(C6502 *c, uint16_t addr) {
  c->a = c->x;
  assign_nz_flags(c, c->a);
}

void TXS(C6502 *c, uint16_t addr) {
  c->sp = c->x;
  assign_nz_flags(c, c->sp);
}

void TYA(C6502 *c, uint16_t addr) {
  c->a = c->y;
  assign_nz_flags(c, c->a);
}

void ILL(C6502 *c, uint16_t addr) { c->running = 0; };
