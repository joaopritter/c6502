#include <stdint.h>

#include "control.h"
#include "flags.h"
#include "instr.h"

void ADC(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t mem = mem_read(c, addr);
  uint16_t res = c->a + mem + check_carry_flag(c);
  assign_carry_flag(c, res > 0xFF);

  // If the result's sign is different from both A's and memory's, signed
  // overflow (or underflow) occurred.
  // Formula = (result ^ A) & (result ^ memory) & $80
  int is_overflow = (~(c->a ^ mem) & (c->a ^ res)) & 0x80;
  assign_overflow_flag(c, is_overflow);

  c->a = (uint8_t)res & 0xFF;
  assign_nz_flags(c, c->a);
}

void AND(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  c->a = c->a & mem_read(c, addr);
  assign_nz_flags(c, c->a);
}

void BCC(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (!check_carry_flag(c))
    c->pc = addr;
}

void BCS(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (check_carry_flag(c))
    c->pc = addr;
}

void BEQ(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (check_zero_flag(c))
    c->pc = addr;
}

void BIT(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t val = mem_read(c, addr);
  uint8_t test = c->a & val;

  assign_overflow_flag(c, val & 0x40); // Bit 6 masking.
  assign_nz_flags(c, val);
}

void BMI(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (check_negative_flag(c))
    c->pc = addr;
}

void BNE(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (!check_zero_flag(c))
    c->pc = addr;
}

void BPL(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (!check_negative_flag(c))
    c->pc = addr;
}

void BRK(C6502 *c, address_mode _) { c->running = 0; };

void BVC(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (!check_overflow_flag(c))
    c->pc = addr;
}

void BVS(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  if (check_overflow_flag(c))
    c->pc = addr;
}

void CLC(C6502 *c, address_mode _) { assign_carry_flag(c, 0); }

void CLD(C6502 *c, address_mode _) { assign_decimal_flag(c, 0); }

void CLI(C6502 *c, address_mode _) { assign_interrupt_disable_flag(c, 0); }

void CLV(C6502 *c, address_mode _) { assign_overflow_flag(c, 0); }

void CMP(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t val = mem_read(c, addr);
  assign_carry_flag(c, c->a >= val);
  assign_nz_flags(c, (uint8_t)(c->a - val));
}

void CPX(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t val = mem_read(c, addr);
  assign_carry_flag(c, c->x >= val);
  assign_nz_flags(c, (uint8_t)(c->x - val));
}

void CPY(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t val = mem_read(c, addr);
  assign_carry_flag(c, c->y >= val);
  assign_nz_flags(c, (uint8_t)(c->y - val));
}

void DEC(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t val = mem_read(c, addr);
  // This is a read-modify-write instruction, meaning that it first writes the
  // original value back to memory before the modified value. This extra write
  // can matter if targeting a hardware register.
  mem_write(c, addr, val);
  val = (val - 1) & 0xFF;
  mem_write(c, addr, val);
  assign_nz_flags(c, c->x);
}

void DEX(C6502 *c, address_mode _) {
  c->x = (c->x - 1) & 0xFF;
  assign_nz_flags(c, c->x);
}

void DEY(C6502 *c, address_mode _) {
  c->y = (c->y - 1) & 0xFF;
  assign_nz_flags(c, c->y);
}

void EOR(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t param = mem_read(c, addr);
  c->a = c->a ^ param;
  assign_nz_flags(c, c->a);
}

void INC(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t val = mem_read(c, addr);
  mem_write(c, addr, val);
  val = (val + 1) & 0xFF;
  mem_write(c, addr, val);
  assign_nz_flags(c, c->x);
}

void INX(C6502 *c, address_mode _) {
  c->x = (c->x + 1) & 0xFF;
  assign_nz_flags(c, c->x);
}

void INY(C6502 *c, address_mode _) {
  c->y = (c->y + 1) & 0xFF;
  assign_nz_flags(c, c->y);
}

void JMP(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  c->pc = addr;
}

void JSR(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint16_t return_addr = c->pc - 1; // RTS adds 1 on return.
  uint8_t hi = (return_addr >> 8) & 0xFF;
  uint8_t lo = return_addr & 0xFF;
  stack_push(c, hi);
  stack_push(c, lo);
  c->pc = addr;
}

void LDA(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t param = mem_read(c, addr);
  c->a = param;
  assign_nz_flags(c, c->a);
};

void LDX(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t param = mem_read(c, addr);
  c->x = param;
  assign_nz_flags(c, c->x);
}

void LDY(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t param = mem_read(c, addr);
  c->y = param;
  assign_nz_flags(c, c->y);
}

void NOP(C6502 *c, address_mode _) { ; }

void ORA(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  uint8_t param = mem_read(c, addr);
  c->a = c->a | param;
  assign_nz_flags(c, c->a);
}

void PHA(C6502 *c, address_mode _) { stack_push(c, c->a); }

void PHP(C6502 *c, address_mode _) {
  uint8_t flags = c->status;
  // The B flag and extra bit are both pushed as 1.
  flags |= BREAK_FLAG;
  flags |= EXTRA_FLAG;
  stack_push(c, flags);
  assign_break_flag(c, 1);
}

void PLA(C6502 *c, address_mode _) {
  uint8_t val = stack_pop(c);
  c->a = val;
  assign_nz_flags(c, val);
}

void PLP(C6502 *c, address_mode _) { c->status = stack_pop(c); }

void RTS(C6502 *c, address_mode _) {
  uint8_t lo = stack_pop(c);
  uint8_t hi = stack_pop(c);
  uint16_t stack_addr = (uint16_t)(lo + (hi << 8));
  c->pc = stack_addr + 1;
}

void SEC(C6502 *c, address_mode _) { assign_carry_flag(c, 1); }

void SED(C6502 *c, address_mode _) { assign_decimal_flag(c, 1); }

void SEI(C6502 *c, address_mode _) { assign_interrupt_disable_flag(c, 1); }

void STA(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  mem_write(c, addr, c->a);
}

void STX(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  mem_write(c, addr, c->x);
}

void STY(C6502 *c, address_mode mode) {
  uint16_t addr = mode(c);
  mem_write(c, addr, c->y);
}

void TAX(C6502 *c, address_mode _) {
  c->x = c->a;
  assign_nz_flags(c, c->x);
}

void TAY(C6502 *c, address_mode _) {
  c->y = c->a;
  assign_nz_flags(c, c->y);
}

void TSX(C6502 *c, address_mode _) {
  c->x = c->sp;
  assign_nz_flags(c, c->x);
}

void TXA(C6502 *c, address_mode _) {
  c->a = c->x;
  assign_nz_flags(c, c->a);
}

void TXS(C6502 *c, address_mode _) {
  c->sp = c->x;
  assign_nz_flags(c, c->sp);
}

void TYA(C6502 *c, address_mode _) {
  c->a = c->y;
  assign_nz_flags(c, c->a);
}

void ILL(C6502 *c, address_mode _) { c->running = 0; };
