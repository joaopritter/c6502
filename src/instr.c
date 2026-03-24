#include "instr.h"
#include "cpu/control.h"
#include <stdint.h>

void LDA(Control *cu, uint16_t addr) {
  uint8_t param = cu->memory[addr];
  cu->a = param;
};

void BRK(Control *cu, uint16_t addr) { return; };
