#include <stdint.h>

#include "control.h"
#include "flags.h"
#include "instr.h"

void BRK(C6502 *c, uint16_t addr) { c->running = 0; };

void INC(C6502 *c, uint16_t addr) {
  uint8_t val = c->memory[addr];
  val = (val + 1) & 0xFF;
  c->memory[addr] = val;
  assign_nz_flags(c, c->x);
}

void INX(C6502 *c, uint16_t addr) {
  c->x = (c->x + 1) & 0xFF;
  assign_nz_flags(c, c->x);
}

void INY(C6502 *c, uint16_t addr) {
  c->y = (c->y + 1) & 0xFF;
  assign_nz_flags(c, c->y);
}

void JMP(C6502 *c, uint16_t addr) { c->pc = addr; }

void JSR(C6502 *c, uint16_t addr) {
  uint16_t return_addr = c->pc - 1; // RTS adds 1 on return.
  uint8_t hi = (return_addr >> 8) & 0xFF;
  uint8_t lo = return_addr & 0xFF;
  stack_push(c, hi);
  stack_push(c, lo);
  c->pc = addr;
}

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

void NOP(C6502 *c, uint16_t addr) { ; }

void ORA(C6502 *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->a = c->a | param;
  assign_nz_flags(c, c->a);
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

void PLP(C6502 *c, uint16_t addr) { c->status = stack_pop(c); }

void RTS(C6502 *c, uint16_t addr) {
  uint8_t lo = stack_pop(c);
  uint8_t hi = stack_pop(c);
  uint16_t stack_addr = (uint16_t)(lo + (hi << 8));
  c->pc = stack_addr + 1;
}

void SEC(C6502 *c, uint16_t addr) { assign_carry_flag(c, 1); }

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
