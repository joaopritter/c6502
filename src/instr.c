#include <stdint.h>

#include "instr.h"
#include "cpu/control.h"
#include "cpu/flags.h"

void LDA(Control *c, uint16_t addr) {
  uint8_t param = c->memory[addr];
  c->a = param;
  assign_nz_flags(c, c->a);
};

void TAX(Control *c, uint16_t addr) {
  c->x = c->a;
  assign_nz_flags(c, c->x);
}

void BRK(Control *c, uint16_t addr) { c->running = 0; };

void ILL(Control *c, uint16_t addr) { c->running = 0; };
