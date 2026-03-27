#ifndef ADDR_MODE_H
#define ADDR_MODE_H

#include "control.h"
#include <stdint.h>

// Accumulator:
// Uses the value in the accumulator register as the value for the operation,
// i.e.: The accumulator both provides the input value and receives the result.
uint16_t ACC(C6502 *c);

// Immediate:
// Uses the 8-bit operand itself as the value for the operation, rather than
// fetching a value from a memory address.
uint16_t IMM(C6502 *c);

// Absolute:
// Fetches a 16-bit address anywhere in memory.
// I.e.: `{0xAD, 0x22, 0x0C}` reads from `0x0C22`, since the 6502 uses little
// endian addressing, the order of bytes is low -> high.
uint16_t ABS(C6502 *c);

// Absolute Indexed X:
// Fetches a 16-bit address increased of the value in register X.
// See ABS for Absolute addressing.
uint16_t ABX(C6502 *c);

// Absolute Indexed Y:
// Fetches a 16-bit address increased of the value in register Y.
// Check ABS for Absolute addressing.
uint16_t ABY(C6502 *c);

// Implied:
// No address operand, the destination of results are implied in the opcode.
uint16_t IMP(C6502 *c);

// Zero Page:
// Fetches an 8-bit address on the zero page (`$0000` - `$00FF`).
uint16_t ZRP(C6502 *c);

// Zero Page Indexed X:
// Fetches an 8-bit address on the zero page increased by the value in register
// X. See ZRP for Zero Page addressing.
// Formula: (arg + X) % 256
uint16_t ZRX(C6502 *c);

// Zero Page Indexed Y:
// Fetches an 8-bit address on the zero page increased by the value in register
// Y. See ZRP for Zero Page addressing.
// Formula: (arg + Y) % 256
uint16_t ZRY(C6502 *c);

// Indirect:
// Fetches the address stored in a 16-bit pointer anywhere in memory.
uint16_t IND(C6502 *c);

// Indexed Indirect (X):
// Fetches the address stored in a 16-bit pointer anywhere in memory increased
// by the value in the register X.
// Formula: mem_read((arg + X) % 256) + mem_read((arg + X + 1) % 256) * 256
uint16_t IDX(C6502 *c);

// Indirect Indexed (Y):
// Fetches the address stored in a 16-bit pointer anywhere in memory increased
// by the value in the register Y.
// Formula: mem_read((arg + Y) % 256) + mem_read((arg + Y + 1) % 256) * 256
uint16_t IDY(C6502 *c);

// Relative:
// User argument as the offset relative to the current counter (after op is
// read) to specify the target address.
uint16_t REL(C6502 *c);

// Source: https://www.nesdev.org/wiki/CPU_addressing_modes
#endif
