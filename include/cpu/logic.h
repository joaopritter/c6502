#ifndef LOGIC_H
#define LOGIC_H
#include <stdint.h>

#include "control.h"

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

// Equivalent of the logic unit of the CPU containing all the arithmetic and
// logical operations supported.
typedef struct {
  // Table with all OPCodes supported, indexed by the code itself.
  OPCode op_code_table[256];
} Logic;

static void init_opcode(OPCode *op, instruction code, address_mode mode,
                        uint8_t size, uint8_t cycles, const char *s_inst,
                        const char *s_mode);

// Initiate the logic unit with all OP Codes registered.
Logic init_logic();

// Locate which OPCode is indexed at the address of given code and return the
// instruction, will return ILLEGAL operation if references a code not yet
// supported.
OPCode decode(Logic *l, uint8_t code);
#endif // !LOGIC_H
