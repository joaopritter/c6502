#ifndef LOGIC_H
#define LOGIC_H
#include "control.h"
#include <stdint.h>

typedef uint16_t (*address_mode)(Control *cu);
typedef void (*instruction)(Control *cu, uint16_t addr);

typedef struct {
  instruction inst;
  address_mode mode;
  uint8_t cycles;
} OPCode;

typedef struct {
  OPCode op_code_table[256];
} Logic;

Logic logic();

OPCode decode(Logic *l, uint8_t code);
#endif // !LOGIC_H
