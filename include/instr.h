#ifndef INSTR_H
#define INSTR_H

#include "control.h"
#include <stdint.h>

// Triggers an interrupt request (IRQ).
// TODO: Proper IRQ handling.
void BRK(C6502 *c, uint16_t addr);

// Loads a value into the accumulator.
void LDA(C6502 *c, uint16_t addr);

// Loads a value into X.
void LDX(C6502 *c, uint16_t addr);

// Loads a value into X.
void LDY(C6502 *c, uint16_t addr);

// Stores de value of A to the current stack position.
void PHA(C6502 *c, uint16_t addr);

// Stores the status flags to the current stack position.
void PHP(C6502 *c, uint16_t addr);

// Pops the value from stack and assign it to A.
void PLA(C6502 *c, uint16_t addr);

// Set decimal flag.
void SED(C6502 *c, uint16_t addr);

// Set interrupt disable flag.
void SEI(C6502 *c, uint16_t addr);

// Store value of A in memory.
void STA(C6502 *c, uint16_t addr);

// Store value of X in memory.
void STX(C6502 *c, uint16_t addr);

// Store value of Y in memory.
void STY(C6502 *c, uint16_t addr);

// Copies the accumulator value to the X register.
void TAX(C6502 *c, uint16_t addr);

// Copies the accumulator value to the Y register.
void TAY(C6502 *c, uint16_t addr);

// Copies the stack pointer value to the X register.
void TSX(C6502 *c, uint16_t addr);

// Copies the X register value to the accumulator.
void TXA(C6502 *c, uint16_t addr);

// Copies the X register value to the stack pointer.
void TXS(C6502 *c, uint16_t addr);

// Copies the Y register value to the accumulator.
void TYA(C6502 *c, uint16_t addr);

// Dummy instruction that does nothing.
void ILL(C6502 *c, uint16_t addr);
#endif
