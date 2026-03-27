#include <stdint.h>

#include "addr_mode.h"
#include "instr.h"
#include "logic.h"

OPCode decode(uint8_t code) { return instr_table[code]; }

void exec(C6502 *cpu, OPCode c) {
  uint16_t program_counter_state = cpu->pc;
  uint16_t addr = c.mode(cpu);
  c.inst(cpu, addr);
  if (cpu->pc == program_counter_state) {
    cpu->pc += (c.size - 1);
  }
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winitializer-overrides"

#define OP(OPCODE, CODE, MODE, SIZE, CYCLES)                                   \
  [OPCODE] = {CODE, MODE, #CODE, #MODE, SIZE, CYCLES}

const OPCode instr_table[256] = {
    [0 ... 255] = {ILL, IMP, "ILL", "IMP", 1, 1},

    OP(0x00, BRK, IMM, 1, 2),

    OP(0xE6, INC, ZRP, 2, 5),
    OP(0xF6, INC, ZRX, 2, 6),
    OP(0xEE, INC, ABS, 3, 6),
    OP(0xF6, INC, ABX, 3, 7),

    OP(0xE8, INX, IMP, 1, 2),

    OP(0xC8, INY, IMP, 1, 2),

    OP(0x4C, JMP, ABS, 3, 3),
    OP(0x6C, JMP, IND, 3, 5),

    OP(0x20, JSR, ABS, 3, 6),

    OP(0xA9, LDA, IMM, 2, 2),
    OP(0xA5, LDA, ZRP, 2, 3),
    OP(0xB5, LDA, ZRX, 2, 4),
    OP(0xAD, LDA, ABS, 3, 4),
    OP(0xBD, LDA, ABX, 3, 4),
    OP(0xB9, LDA, ABY, 3, 4),
    OP(0xA1, LDA, IDX, 2, 6),
    OP(0xB1, LDA, IDY, 2, 5),

    OP(0xA2, LDX, IMM, 2, 2),
    OP(0xA6, LDX, ZRP, 2, 3),
    OP(0xB6, LDX, ZRY, 2, 4),
    OP(0xAE, LDX, ABS, 3, 4),
    OP(0xBE, LDX, ABY, 3, 4),

    OP(0xA0, LDY, IMM, 2, 2),
    OP(0xA4, LDY, ZRP, 2, 3),
    OP(0xB4, LDY, ZRY, 2, 4),
    OP(0xAC, LDY, ABS, 3, 4),
    OP(0xBC, LDY, ABY, 3, 4),

    OP(0xEA, NOP, IMP, 1, 2),

    OP(0x09, ORA, IMM, 2, 2),
    OP(0x05, ORA, ZRP, 2, 3),
    OP(0x15, ORA, ZRX, 2, 4),
    OP(0x0D, ORA, ABS, 3, 4),
    OP(0x1D, ORA, ABX, 3, 4),
    OP(0x19, ORA, ABY, 3, 4),
    OP(0x01, ORA, IDX, 2, 6),
    OP(0x11, ORA, IDY, 2, 5),

    OP(0x48, PHA, IMP, 1, 3),

    OP(0x08, PHP, IMP, 1, 3),

    OP(0x68, PLA, IMP, 1, 4),

    OP(0x28, PLP, IMP, 1, 4),

    OP(0x60, RTS, IMP, 1, 6),

    OP(0x38, SEC, IMP, 1, 2),

    OP(0xF8, SED, IMP, 1, 2),

    OP(0x79, SEI, IMP, 1, 2),

    OP(0x85, STA, ZRP, 2, 3),
    OP(0x95, STA, ZRX, 2, 4),
    OP(0x8D, STA, ABS, 3, 4),
    OP(0x9D, STA, ABX, 3, 5),
    OP(0x99, STA, ABY, 3, 5),
    OP(0x81, STA, IDX, 2, 6),
    OP(0x91, STA, IDY, 2, 6),

    OP(0x86, STX, ZRP, 2, 3),
    OP(0x96, STX, ZRY, 2, 4),
    OP(0x8E, STX, ABS, 3, 4),

    OP(0x84, STY, ZRP, 2, 3),
    OP(0x94, STY, ZRY, 2, 4),
    OP(0x8C, STY, ABS, 3, 4),

    OP(0xAA, TAX, IMP, 1, 2),

    OP(0xA8, TAY, IMP, 1, 2),

    OP(0xBA, TSX, IMP, 1, 2),

    OP(0x8A, TXA, IMP, 1, 2),

    OP(0x9A, TXS, IMP, 1, 2),

    OP(0x98, TYA, IMP, 1, 2),

#undef OP
};

#pragma GCC diagnostic pop
