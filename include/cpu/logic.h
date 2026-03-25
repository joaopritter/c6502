#ifndef LOGIC_H
#define LOGIC_H
#include <stdint.h>

#include "control.h"

typedef uint16_t (*address_mode)(Control *cu);
typedef void (*instruction)(Control *cu, uint16_t addr);

typedef struct {
  instruction inst;
  char s_inst[4];
  address_mode mode;
  char s_mode[4];
  int size;
  uint8_t cycles;
} OPCode;

static void init_opcode(OPCode *op, instruction code, address_mode mode,
                        uint8_t size, uint8_t cycles, const char *s_inst,
                        const char *s_mode);

typedef struct {
  OPCode op_code_table[256];
} Logic;

Logic init_logic();

OPCode decode(Logic *l, uint8_t code);
#endif // !LOGIC_H
