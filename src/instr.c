#include "instr.h"
#include "cpu/control.h"
#include <stdint.h>
#include <stdlib.h>

void LDA(Control *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->a = param;
};

void TAX(Control *c, uint16_t addr) {
  c->x = c->a;
  update_zero_and_negative_flags(c, c->x);
}

void BRK(Control *c, uint16_t addr) { exit(0); };

void ILL(Control *c, uint16_t addr) { exit(1); };
