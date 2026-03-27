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

#pragma GCC diagnostic ignored "-Winitializer-overrides"

#define OP(OPCODE, CODE, MODE, SIZE, CYCLES)                                   \
  [OPCODE] = {CODE, MODE, #CODE, #MODE, SIZE, CYCLES}
const OPCode instr_table[256] = {
    [0 ... 255] = {ILL, IMP, "ILL", "IMP", 1, 1},

    OP(0x69, ADC, IMM, 2, 2),
    OP(0x65, ADC, ZRP, 2, 3),
    OP(0x75, ADC, ZRX, 2, 4),
    OP(0x6D, ADC, ABS, 3, 4),
    OP(0x7D, ADC, ABX, 3, 4),
    OP(0x79, ADC, ABY, 3, 4),
    OP(0x61, ADC, IDX, 2, 6),
    OP(0x71, ADC, IDY, 2, 5),

    OP(0x29, AND, IMM, 2, 2),
    OP(0x25, AND, ZRP, 2, 3),
    OP(0x35, AND, ZRX, 2, 4),
    OP(0x2D, AND, ABS, 3, 4),
    OP(0x3D, AND, ABX, 3, 4),
    OP(0x39, AND, ABY, 3, 4),
    OP(0x21, AND, IDX, 2, 6),
    OP(0x31, AND, IDY, 2, 5),

    OP(0x90, BCC, REL, 2, 3),

    OP(0xB0, BCS, REL, 2, 3),

    OP(0xF0, BEQ, REL, 2, 3),

    OP(0x2C, BIT, ABS, 3, 4),
    OP(0x24, BIT, ZRP, 2, 3),

    OP(0x30, BMI, REL, 2, 3),

    OP(0xD0, BNE, REL, 2, 3),

    OP(0x10, BPL, REL, 2, 3),

    OP(0x00, BRK, IMM, 1, 2),

    OP(0x50, BVC, REL, 2, 3),

    OP(0x70, BVS, REL, 2, 3),

    OP(0x18, CLC, IMP, 1, 2),

    OP(0xD8, CLD, IMP, 1, 2),

    OP(0x58, CLI, IMP, 1, 2),

    OP(0xB8, CLV, IMP, 1, 2),

    OP(0xC9, CMP, IMM, 2, 2),
    OP(0xC5, CMP, ZRP, 2, 3),
    OP(0xD5, CMP, ZRX, 2, 4),
    OP(0xCD, CMP, ABS, 3, 4),
    OP(0xDD, CMP, ABX, 3, 4),
    OP(0xD9, CMP, ABY, 3, 4),
    OP(0xC1, CMP, IDX, 2, 6),
    OP(0xD1, CMP, IDY, 2, 5),

    OP(0xE0, CPX, IMM, 2, 2),
    OP(0xE4, CPX, ZRP, 2, 3),
    OP(0xEC, CPX, ABS, 3, 4),

    OP(0xC0, CPY, IMM, 2, 2),
    OP(0xC4, CPY, ZRP, 2, 3),
    OP(0xCC, CPY, ABS, 3, 4),

    OP(0xC6, DEC, ZRP, 2, 5),
    OP(0xD6, DEC, ZRX, 2, 6),
    OP(0xCE, DEC, ABS, 3, 6),
    OP(0xDE, DEC, ABX, 3, 7),

    OP(0xCA, DEX, IMP, 1, 2),

    OP(0x88, DEY, IMP, 1, 2),

    OP(0x49, EOR, IMM, 2, 2),
    OP(0x45, EOR, ZRP, 2, 3),
    OP(0x55, EOR, ZRX, 2, 4),
    OP(0x4D, EOR, ABS, 3, 4),
    OP(0x5D, EOR, ABX, 3, 4),
    OP(0x59, EOR, ABY, 4, 4),
    OP(0x41, EOR, IDX, 2, 6),
    OP(0x51, EOR, IDY, 2, 5),

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
