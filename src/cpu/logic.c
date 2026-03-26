#include <stdint.h>
#include <string.h>

#include "addr_mode.h"
#include "cpu/logic.h"
#include "instr.h"

static void init_opcode(OPCode *op, instruction code, address_mode mode,
                        uint8_t size, uint8_t cycles, const char *s_inst,
                        const char *s_mode) {
  op->inst = code;
  op->mode = mode;
  op->size = size;
  op->cycles = cycles;

  strncpy(op->s_inst, s_inst, sizeof(op->s_inst) - 1);
  op->s_inst[sizeof(op->s_inst) - 1] = '\0';

  strncpy(op->s_mode, s_mode, sizeof(op->s_mode) - 1);
  op->s_mode[sizeof(op->s_mode) - 1] = '\0';
}

Logic init_logic() {
  Logic l;
  OPCode illegal_opcode;
  init_opcode(&illegal_opcode, ILL, IMP, 1, 1, "ILL", "IMP");

  for (int i = 0; i < 256; i++) {
    l.op_code_table[i] = illegal_opcode;
  }

#define MAKE_INSTR(HEX, CODE, MODE, SIZE, CYCLES)                              \
  init_opcode(&l.op_code_table[HEX], CODE, MODE, SIZE, CYCLES, #CODE, #MODE)

  MAKE_INSTR(0xA9, LDA, IMM, 2, 2);
  MAKE_INSTR(0xA5, LDA, ZRP, 2, 3);
  MAKE_INSTR(0xB5, LDA, ZRX, 2, 4);
  MAKE_INSTR(0xAD, LDA, ABS, 3, 4);
  MAKE_INSTR(0xBD, LDA, ABX, 3, 4);
  MAKE_INSTR(0xB9, LDA, ABY, 3, 4);
  MAKE_INSTR(0xA1, LDA, IDX, 2, 6);
  MAKE_INSTR(0xB1, LDA, IDY, 2, 5);

  MAKE_INSTR(0xA2, LDX, IMM, 2, 2);
  MAKE_INSTR(0xA6, LDX, ZRP, 2, 3);
  MAKE_INSTR(0xB6, LDX, ZRY, 2, 4);
  MAKE_INSTR(0xAE, LDX, ABS, 3, 4);
  MAKE_INSTR(0xBE, LDX, ABY, 3, 4);

  MAKE_INSTR(0xA0, LDY, IMM, 2, 2);
  MAKE_INSTR(0xA4, LDY, ZRP, 2, 3);
  MAKE_INSTR(0xB4, LDY, ZRY, 2, 4);
  MAKE_INSTR(0xAC, LDY, ABS, 3, 4);
  MAKE_INSTR(0xBC, LDY, ABY, 3, 4);

  MAKE_INSTR(0xAA, TAX, IMP, 1, 2);

  MAKE_INSTR(0x48, PHA, IMP, 1, 3);

  MAKE_INSTR(0x08, PHP, IMP, 1, 3);

  MAKE_INSTR(0x68, PLA, IMP, 1, 4);

  MAKE_INSTR(0x85, STA, ZRP, 2, 3);
  MAKE_INSTR(0x95, STA, ZRX, 2, 4);
  MAKE_INSTR(0x8D, STA, ABS, 3, 4);
  MAKE_INSTR(0x9D, STA, ABX, 3, 5);
  MAKE_INSTR(0x99, STA, ABY, 3, 5);
  MAKE_INSTR(0x81, STA, IDX, 2, 6);
  MAKE_INSTR(0x91, STA, IDY, 2, 6);

  MAKE_INSTR(0x86, STX, ZRP, 2, 3);
  MAKE_INSTR(0x96, STX, ZRY, 2, 4);
  MAKE_INSTR(0x8E, STX, ABS, 3, 4);

  MAKE_INSTR(0x84, STY, ZRP, 2, 3);
  MAKE_INSTR(0x94, STY, ZRY, 2, 4);
  MAKE_INSTR(0x8C, STY, ABS, 3, 4);

  MAKE_INSTR(0x00, BRK, IMM, 1, 2);

#undef MAKE_INSTR

  return l;
};

OPCode decode(Logic *l, uint8_t code) {
  OPCode c = l->op_code_table[code];
  return c;
}
