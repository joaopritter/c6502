#include "cpu/logic.h"
#include <stdint.h>

#include "addr_mode.h"
#include "instr.h"

Logic logic() {
  Logic l;
  OPCode c;
  OPCode op_code_table[256];

  // fill jump table with ILLEGALs
  // instr.addr = &mos6502::Addr_IMP;
  // instr.saddr = "(null)";
  // instr.code = &mos6502::Op_ILLEGAL;
  // instr.scode = "(null)";
  // instr.penalty = false;
  // instr.cycles = 0;
  // for(int i = 0; i < 256; i++)
  // {
  //    InstrTable[i] = instr;
  // }

  // insert opcodes
#define MAKE_INSTR(HEX, CODE, MODE, CYCLES)                                    \
  c.inst = CODE;                                                               \
  c.mode = MODE;                                                               \
  c.cycles = CYCLES;                                                           \
  l.op_code_table[HEX] = c;
  MAKE_INSTR(0xA9, LDA, IMM, 2);
  MAKE_INSTR(0x00, BRK, IMM, 2)

  return l;
};

OPCode decode(Logic *l, uint8_t code) { return l->op_code_table[code]; }
