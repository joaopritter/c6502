#include "instr.h"
#include "cpu/control.h"
#include <stdint.h>
#include <stdlib.h>

void LDA(Control *cu, uint16_t addr) {
  uint8_t param = cu->memory[addr];
  cu->a = param;
};

void BRK(Control *cu, uint16_t addr) { exit(0); };

void ILL(Control *cu, uint16_t addr) { exit(1); };
