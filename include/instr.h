#ifndef INSTR_H
#define INSTR_H

#include "cpu/control.h"
#include <stdint.h>

// Loads a value into the accumulator.
void LDA(Control *c, uint16_t addr);

// Loads a value into X.
void LDX(Control *c, uint16_t addr);

// Loads a value into X.
void LDY(Control *c, uint16_t addr);

// Copies the accumulator value to the X register.
void TAX(Control *c, uint16_t addr);

// Stores de value of A to the current stack position.
void PHA(Control *c, uint16_t addr);

// Stores the status flags to the current stack position.
void PHP(Control *c, uint16_t addr);

// Pops the value from stack and assign it to A.
void PLA(Control *c, uint16_t addr);

//
void TXS(Control *c, uint16_t addr);

// Store value of A in memory.
void STA(Control *c, uint16_t addr);

// Store value of X in memory.
void STX(Control *c, uint16_t addr);

// Store value of Y in memory.
void STY(Control *c, uint16_t addr);

// Triggers an interrupt request (IRQ).
// TODO: Proper IRQ handling.
void BRK(Control *c, uint16_t addr);

// Dummy instruction that does nothing.
void ILL(Control *c, uint16_t addr);
#endif
