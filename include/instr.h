#ifndef INSTR_H
#define INSTR_H

#include "cpu/control.h"
#include <stdint.h>

// Loads a memory value into the accumulator.
void LDA(Control *c, uint16_t addr);

// Copies the accumulator value to the X register.
void TAX(Control *c, uint16_t addr);

// Triggers an interrupt request (IRQ).
// TODO: Proper IRQ handling.
void BRK(Control *c, uint16_t addr);

// Dummy instruction that does nothing.
void ILL(Control *c, uint16_t addr);
#endif
