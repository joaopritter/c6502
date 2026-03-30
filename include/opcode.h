#ifndef OPCODE_H
#define OPCODE_H
#include <stdint.h>

#include "control.h"

// Method used to represent addressing mode behavior returning the address of
// the value to be used by the instruction.
typedef uint16_t (*address_mode)(C6502 *c);

// Method used to represent any cpu instruction receiving a 16bit address from
// the address mode method.
typedef void (*instruction)(C6502 *c, uint16_t addr);

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

extern const OPCode instr_table[256];

// Locate which OPCode is indexed at the address of given code and return the
// instruction, will return ILLEGAL operation if references a code not yet
// supported.
OPCode decode(uint8_t code);
void exec(C6502 *cpu, OPCode c);
#endif // !OPCODE_H
