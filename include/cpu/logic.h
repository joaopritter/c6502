#ifndef LOGIC_H
#define LOGIC_H
#include <stdint.h>

#include "addr_mode.h"
#include "control.h"
#include "instr.h"

// Method used to represent addressing mode behavior returning the address of
// the value to be used by the instruction.
typedef uint16_t (*address_mode)(Control *c);

// Method used to represent any cpu instruction receiving a 16bit address from
// the address mode method.
typedef void (*instruction)(Control *c, uint16_t addr);

// OP Codes represent and instruction to be executed by the CPU alongside the
// addressing mode, one instruction can (and likely will) have multiple OPCodes.
typedef struct {
    // Pointer to instruction method.
    instruction inst;

    // Pointer to addressing mode method.
    address_mode mode;

    // String used for debugging.
    char s_inst[4];

    // String used for debugging.
    char s_mode[4];

    // Instruction size in bytes.
    int size;

    // CPU Cycles required to execute instruction.
    uint8_t cycles;
} OPCode;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winitializer-overrides"

#define OP(OPCODE, CODE, MODE, SIZE, CYCLES)                                   \
  [OPCODE] = {CODE, MODE, #CODE, #MODE, SIZE, CYCLES}

#define DEFAULT_OP {ILL, IMP, "ILL", "IMP", 1, 1}

const OPCode instr_table[256] = {
    [0 ... 255] = DEFAULT_OP,
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

    OP(0xAA, TAX, IMP, 1, 2),

    OP(0x48, PHA, IMP, 1, 3),

    OP(0x08, PHP, IMP, 1, 3),

    OP(0x68, PLA, IMP, 1, 4),

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

    OP(0x00, BRK, IMM, 1, 2),

#undef OP
};

#pragma GCC diagnostic pop

// Locate which OPCode is indexed at the address of given code and return the
// instruction, will return ILLEGAL operation if references a code not yet
// supported.
OPCode decode(uint8_t code);

#endif // !LOGIC_H