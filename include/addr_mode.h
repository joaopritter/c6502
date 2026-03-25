#ifndef ADDR_MODE_H
#define ADDR_MODE_H

#include "cpu/control.h"
#include <stdint.h>

// typedef enum {
//   IMPLICIT,    // no address operand.
//   ACCUMULATOR, // act on the accumulator.
//   IMMEDIATE,   // doesnt fetch from memory.
//   ZERO_PAGE,   // fetches from 8 bit address on zero page.
//   ZERO_PAGE_X, // val = PEEK((arg + X) % 256).
//   ZERO_PAGE_Y, // val = PEEK((arg + Y) % 256).
//   ABSOLUTE,    // fetch from 16-bit address anywhere in memory.
//   ABSOLUTE_X,  // val = PEEK(arg + X).
//   ABSOLUTE_Y,  // val = PEEK(arg + X).
//   INDIRECT, // special addressing mode that can jump to address stored in
//   16-bit
//             // pointer anywhere in memory.
//   INDEXED_INDIRECT, // val = PEEK(PEEK((arg + X) % 256) + PEEK((arg + X + 1)
//   %
//                     // 256) * 256).
//   INDIRECT_INDEXED, // val = PEEK(PEEK(arg) + PEEK((arg + 1) % 256) * 256 +
//   Y). RELATIVE, // branch instructions have a relative 8-bit signed offset
//   relative
//             // to current PC.
// } AddressingMode;

uint16_t IMM(Control *c);

uint16_t ABS(Control *c);

uint16_t ABX(Control *c);

uint16_t ABY(Control *c);

uint16_t IMP(Control *c);

uint16_t ZRP(Control *c);
#endif
