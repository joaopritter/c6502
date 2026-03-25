#ifndef CONTROL_H
#define CONTROL_H
#include <stdint.h>

// source: https://www.nesdev.org/wiki/
typedef struct {
  int running;
  uint8_t memory[0x10000];
  /*
    $0000–$07FF 	$0800 	2 KB internal RAM

      - $0000-$00FF: The zero page, which can be accessed with fewer bytes and
                     cycles than other addresses.
      - $0100–$01FF: The page containing the stack, which can be located
                     anywhere here, but typically starts at $01FF and grows
                     downward
    -----------------------------------------------------------------------------
    $0800–$0FFF 	$0800 |
    $1000–$17FF 	$0800 	Mirrors of $0000–$07FF
    $1800–$1FFF 	$0800 |
    -----------------------------------------------------------------------------
    $2000–$2007 	$0008 	NES PPU (Picture Processing Unit) registers
    -----------------------------------------------------------------------------
    $2008–$3FFF 	$1FF8 	Mirrors of $2000–$2007 (repeats every 8 bytes)
    -----------------------------------------------------------------------------
    $4000–$4017 	$0018 	NES APU (Audio Processing Unit) and I/O
                          registers
    -----------------------------------------------------------------------------
    $4018–$401F 	$0008 	APU and I/O functionality that is normally
                          disabled.
    -----------------------------------------------------------------------------
    $4020–$FFFF > $BFE0 > Unmapped. Available for cartridge use.

      - $6000-$7FFF > $2000 > Usually cartridge RAM, when present.
      - $8000–$FFFF > $8000 > Usually cartridge ROM and mapper registers.
  */
  uint8_t a;    // rw to memory, store arithmetic and logic results.
  uint8_t x;    // rw to memory, primarily counter in loops or memaddress.
  uint8_t y;    // similar to x but not interchangeable.
  uint8_t flag; // 7 binary flags representing status of the processor.
  /*
    7  bit  0
    ---- ----
    NV1B DIZC
    |||| ||||
    |||| |||+- Carry
    |||| ||+-- Zero
    |||| |+--- Interrupt Disable
    |||| +---- Decimal
    |||+------ (No CPU effect; see: the B flag)
    ||+------- (No CPU effect; always pushed as 1)
    |+-------- Overflow
    +--------- Negative
  */
  uint8_t stack_pointer; // current location on the stack.
  uint16_t counter;      // position in the program
} Control;

uint8_t mem_read(Control *c, uint16_t addr);

void update_zero_and_negative_flags(Control *c, uint8_t result);
#endif
