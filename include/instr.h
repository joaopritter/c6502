#ifndef INSTR_H
#define INSTR_H

#include "control.h"
#include <stdint.h>

// Branch if negative flag is set.
void BMI(C6502 *c, uint16_t addr);

// Branch if zero flag is clear.
void BNE(C6502 *c, uint16_t addr);

// Branch to rel address if the negative flag is clear.
void BPL(C6502 *c, uint16_t addr);

// Triggers an interrupt request (IRQ).
// TODO: Proper IRQ handling.
void BRK(C6502 *c, uint16_t addr);

// Branch if overflow clear.
void BVC(C6502 *c, uint16_t addr);

// Branch if overflow set.
void BVS(C6502 *c, uint16_t addr);

// Clear carry flag.
void CLC(C6502 *c, uint16_t addr);

// Clear decinal flag.
void CLD(C6502 *c, uint16_t addr);

// Clear interrupt disable flag.
void CLI(C6502 *c, uint16_t addr);

// Clear overflow flag.
void CLV(C6502 *c, uint16_t addr);

// Compares A to a memory value, setting flags as appropriate.
void CMP(C6502 *c, uint16_t addr);

// Compares X to a memory value, setting flags as appropriate.
void CPX(C6502 *c, uint16_t addr);

// Compares Y to a memory value, setting flags as appropriate.
void CPY(C6502 *c, uint16_t addr);

// Increment +1 to a value in memory.
void DEC(C6502 *c, uint16_t addr);

// Decrement -1 to value in register X.
void DEX(C6502 *c, uint16_t addr);

// Decrement -1 to value in register Y.
void DEY(C6502 *c, uint16_t addr);

// Exclusive-ORs a memory value and the accumulator.
void EOR(C6502 *c, uint16_t addr);

// Increment +1 to a value in memory.
void INC(C6502 *c, uint16_t addr);

// Increment +1 to value in register X.
void INX(C6502 *c, uint16_t addr);

// Increment +1 to value in register Y.
void INY(C6502 *c, uint16_t addr);

// Jump program counter to memory value.
void JMP(C6502 *c, uint16_t addr);

// Jump to subroutine and push counter to stack.
void JSR(C6502 *c, uint16_t addr);

// Loads a value into the accumulator.
void LDA(C6502 *c, uint16_t addr);

// Loads a value into X.
void LDX(C6502 *c, uint16_t addr);

// Loads a value into X.
void LDY(C6502 *c, uint16_t addr);

// No operation, does nothing.
void NOP(C6502 *c, uint16_t addr);

// Inclusive-ORs a memory value and the accumulator.
void ORA(C6502 *c, uint16_t addr);

// Stores de value of A to the current stack position.
void PHA(C6502 *c, uint16_t addr);

// Stores the status flags to the current stack position.
void PHP(C6502 *c, uint16_t addr);

// Pops the value from stack and assign it to A.
void PLA(C6502 *c, uint16_t addr);

// Pull processor status from stack and loads it into the flags.
void PLP(C6502 *c, uint16_t addr);

// Return from subroutine
void RTS(C6502 *c, uint16_t addr);

// Set carry flag.
void SEC(C6502 *c, uint16_t addr);

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
