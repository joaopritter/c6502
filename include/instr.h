#ifndef INSTR_H
#define INSTR_H

#include "control.h"
#include "opcode.h"
#include <stdint.h>

// Adds the carry flag and a memory value to the accumulator.
void ADC(C6502 *c, address_mode mode);

// Bitwise and between memory value and accumulator.
void AND(C6502 *c, address_mode mode);

// Branch if carry flag is clear.
void BCC(C6502 *c, address_mode mode);

// Branch if carry flag is set.
void BCS(C6502 *c, address_mode mode);

// Branch if zero flag is set.
void BEQ(C6502 *c, address_mode mode);

// Bit test between memory value and accumulator.
void BIT(C6502 *c, address_mode mode);

// Branch if negative flag is set.
void BMI(C6502 *c, address_mode mode);

// Branch if zero flag is clear.
void BNE(C6502 *c, address_mode mode);

// Branch to rel address if the negative flag is clear.
void BPL(C6502 *c, address_mode mode);

// Triggers an interrupt request (IRQ).
// TODO: Proper IRQ handling.
void BRK(C6502 *c, address_mode mode);

// Branch if overflow clear.
void BVC(C6502 *c, address_mode mode);

// Branch if overflow set.
void BVS(C6502 *c, address_mode mode);

// Clear carry flag.
void CLC(C6502 *c, address_mode mode);

// Clear decinal flag.
void CLD(C6502 *c, address_mode mode);

// Clear interrupt disable flag.
void CLI(C6502 *c, address_mode mode);

// Clear overflow flag.
void CLV(C6502 *c, address_mode mode);

// Compares A to a memory value, setting flags as appropriate.
void CMP(C6502 *c, address_mode mode);

// Compares X to a memory value, setting flags as appropriate.
void CPX(C6502 *c, address_mode mode);

// Compares Y to a memory value, setting flags as appropriate.
void CPY(C6502 *c, address_mode mode);

// Increment +1 to a value in memory.
void DEC(C6502 *c, address_mode mode);

// Decrement -1 to value in register X.
void DEX(C6502 *c, address_mode mode);

// Decrement -1 to value in register Y.
void DEY(C6502 *c, address_mode mode);

// Exclusive-ORs a memory value and the accumulator.
void EOR(C6502 *c, address_mode mode);

// Increment +1 to a value in memory.
void INC(C6502 *c, address_mode mode);

// Increment +1 to value in register X.
void INX(C6502 *c, address_mode mode);

// Increment +1 to value in register Y.
void INY(C6502 *c, address_mode mode);

// Jump program counter to memory value.
void JMP(C6502 *c, address_mode mode);

// Jump to subroutine and push counter to stack.
void JSR(C6502 *c, address_mode mode);

// Loads a value into the accumulator.
void LDA(C6502 *c, address_mode mode);

// Loads a value into X.
void LDX(C6502 *c, address_mode mode);

// Loads a value into X.
void LDY(C6502 *c, address_mode mode);

// No operation, does nothing.
void NOP(C6502 *c, address_mode mode);

// Inclusive-ORs a memory value and the accumulator.
void ORA(C6502 *c, address_mode mode);

// Stores de value of A to the current stack position.
void PHA(C6502 *c, address_mode mode);

// Stores the status flags to the current stack position.
void PHP(C6502 *c, address_mode mode);

// Pops the value from stack and assign it to A.
void PLA(C6502 *c, address_mode mode);

// Pull processor status from stack and loads it into the flags.
void PLP(C6502 *c, address_mode mode);

// Return from subroutine
void RTS(C6502 *c, address_mode mode);

// Set carry flag.
void SEC(C6502 *c, address_mode mode);

// Set decimal flag.
void SED(C6502 *c, address_mode mode);

// Set interrupt disable flag.
void SEI(C6502 *c, address_mode mode);

// Store value of A in memory.
void STA(C6502 *c, address_mode mode);

// Store value of X in memory.
void STX(C6502 *c, address_mode mode);

// Store value of Y in memory.
void STY(C6502 *c, address_mode mode);

// Copies the accumulator value to the X register.
void TAX(C6502 *c, address_mode mode);

// Copies the accumulator value to the Y register.
void TAY(C6502 *c, address_mode mode);

// Copies the stack pointer value to the X register.
void TSX(C6502 *c, address_mode mode);

// Copies the X register value to the accumulator.
void TXA(C6502 *c, address_mode mode);

// Copies the X register value to the stack pointer.
void TXS(C6502 *c, address_mode mode);

// Copies the Y register value to the accumulator.
void TYA(C6502 *c, address_mode mode);

// Dummy instruction that does nothing.
void ILL(C6502 *c, address_mode mode);
#endif
