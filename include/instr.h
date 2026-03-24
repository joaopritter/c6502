#ifndef INSTR_H
#define INSTR_H

#include "cpu/control.h"
#include <stdint.h>

void LDA(Control *cu, uint16_t addr);

void BRK(Control *cu, uint16_t addr);
#endif
