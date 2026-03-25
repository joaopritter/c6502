#ifndef INSTR_H
#define INSTR_H

#include "cpu/control.h"
#include <stdint.h>

void LDA(Control *c, uint16_t addr);

void TAX(Control *c, uint16_t addr);

void BRK(Control *c, uint16_t addr);

void ILL(Control *c, uint16_t addr);
#endif
