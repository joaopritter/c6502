#ifndef CONTROL_H
#define CONTROL_H
#include <stdint.h>

#define STACK_START 0x0100
#define STACK_RESET 0xFF

typedef struct {
  // Placeholder for interrupting CPU.
  // TODO: Handle "On" and "Off" correctly.
  int running;

  // # Memory Map.
  //
  // `$0000–$07FF`: 2 KB internal RAM.
  // - `$0100-$01FF`: Stack.
  // `$0800–$1FFF`: Mirrors of $0000–$07FF (repeated every 2 KB).
  // `$2000–$2007`: NES PPU registers.
  // - `$2000`: PPUCTRL.
  // - `$2001`: PPUMASK.
  // - `$2002`: PPUSTATUS.
  // - `$2003`: OAMADDR.
  // - `$2004`: OAMDATA.
  // - `$2005`: PPUSCROLL.
  // - `$2006`: PPUADDR.
  // - `$2007`: PPUDATA.
  // `$2008–$3FFF`: Mirrors of $2000–$2007 (repeated every 8 bytes).
  // `$4000–$4017`: NES APU and I/O registers:
  // - `$4000`: SQ1_VOL: Duty cycle and volume.
  // - `$4001`: SQ1_SWEEP: Periodically adjust a pulse channel's period.
  // - `$4002`: SQ1_LO: Low byte of period.
  // - `$4003`: SQ1_HI: High byte of period.
  // - `$4004`: SQ2_VOL.
  // - `$4005`: SQ2_SWEEP.
  // - `$4006`: SQ2_LO.
  // - `$4007`: SQ2_HI.
  // - `$4008`: TRI_TRILINEAR: Linear counter.
  // - `$4009`: [Unused].
  // - `$400A`: TRI_LO.
  // - `$400B`: TRI_HI.
  // - `$400C`: NOISE_ VOL.
  // - `$400D`: [Unused].
  // - `$400E`: NOISE_LO.
  // - `$400F`: NOISE_HI.
  // - `$4010`: DMC_FREQ: IRQ flag, loop flag and frequency.
  // - `$4011`: DMC_RAW: 7 bit DAC (Digital-Analog Converter).
  // - `$4012`: DMC_START: Start address = `$C000` + `$40*$xx`.
  // - `$4013`: DMC_LEN: Sample length = `$10` * `$xx` + 1 bytes (128 * `$xx` +
  // 8 samples).
  // - `$4014`: Suspends the CPU so it can quickly copy a page of CPU memory to
  // PPU OAM using DMA.
  // - `$4015`: Enable and disable individual channels, control the DMC.
  // * Write: Disable individual channels and silence the DMC after it empties.
  // * Read: Check which channels were enabled.
  // - `$4016`: JOY1.
  // * Write: Set strobe signal to capture current state of all buttons in both
  // controllers.
  // * Read: Joystick 1 data.
  // - `$4017`: JOY2.
  // * Write: Frame counter control.
  // * Read: Joystick 2 data.
  // `$4018–$401F`: APU and I/O functionality (Usually disabled).
  // `$4020–$FFFF`: Cartridge use:
  // - `$6000–$7FFF`: Cartridge RAM.
  // - `$8000–$FFFF`: Cartridge ROM.
  //
  // # Sources:
  // - https://www.nesdev.org/wiki/CPU_memory_map
  // - https://www.nesdev.org/wiki/2A03
  // - https://www.nesdev.org/wiki/PPU_registers
  uint8_t memory[0x10000];

  // # Accumulator.
  //
  // RW to memory, store arithmetic and logic results.
  uint8_t a;

  // # Index X.
  //
  // RW to memory, primarily counter in loops or memaddress.
  uint8_t x;

  // # Index Y.
  //
  // Behaves similarly to register X but is not interchangeable.
  uint8_t y;

  // # Status flags:
  //
  // `NV_B DIZC`
  // `N` - Negative: After most instructions that have a value result, this flag
  // will contain bit 7 of that result.
  // `V` - Overflow: ADC and SBC will set this flag if the signed result would
  // be invalid. BIT will load bit 6 of the addressed value.
  // `_` - Extra: Unused bit.
  // `B` - Break: No effect in the CPU directly but used by software.
  // `D` - Decimal: On the NES, decimal mode is disabled and so this flag has no
  // effect.
  // `I` - Interrupt Disable: Inhibits IRQ. NMI, BRK, and reset are not
  // affected.
  // `Z` - Zero: After most instructions that have a value result, this flag
  // will either be set or cleared based on whether or not that value is equal
  // to zero.
  // `C` - Carry: After ADC, this is the carry result of the addition. After SBC
  // or CMP, both of which do subtraction, this flag will be set if no borrow
  // was the result, or alternatively a "greater than or equal" result. After a
  // shift instruction (ASL, LSR, ROL, ROR), this contains the bit that was
  // shifted out.
  //
  // # Source: https://www.nesdev.org/wiki/Status_flags
  uint8_t status;

  // # Stack Pointer.
  //
  // A descending stack (or one that grows downward) starts the stack pointer at
  // the end of the array, decreases it on a push, and increases it on a pull.
  // Stack is located between `$0100-$01FF`.
  uint8_t sp;

  // # Program counter.
  //
  // Tracks the current position in the program execution.
  uint16_t pc;
} Control;

uint8_t mem_read(Control *c, uint16_t addr);

void mem_write(Control *c, uint16_t addr, uint8_t value);

// Source: https://www.nesdev.org/wiki/
#endif
