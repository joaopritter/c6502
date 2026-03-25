#ifndef CONTROL_H
#define CONTROL_H
#include <stdint.h>

typedef struct {
  // Placeholder for interrupting CPU.
  // TODO: Handle "On" and "Off" correctly.
  int running;

  // `$0000–$07FF`: 2 KB internal RAM.
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
  // ---
  // `$2008–$3FFF`: Mirrors of $2000–$2007 (repeated every 8 bytes).
  // `$4000–$4017`: NES APU and I/O registers:
  // | APU:
  // XXX_VOL: Duty cycle and volume.
  // XXX_SWEEP: Periodically adjust a pulse channel's period up or down.
  // XXX_LO: Low byte of period.
  // | Square Wave 1:
  // - `$4000`: SQ1_VOL.
  // - `$4001`: SQ1_SWEEP.
  // - `$4002`: SQ1_LO.
  // - `$4003`: SQ1_HI.
  // .
  // | Square Wave 2:
  // - `$4004`: SQ2_VOL.
  // - `$4005`: SQ2_SWEEP.
  // - `$4006`: SQ2_LO.
  // - `$4007`: SQ2_HI.
  // .
  // | Triangle Wave:
  // - `$4008`: TRI_TRILINEAR: Linear counter.
  // - `$4009`: [Unused].
  // - `$400A`: TRI_LO.
  // - `$400B`: TRI_HI.
  // .
  // | Noise:
  // - `$400C`: NOISE_ VOL.
  // - `$400D`: [Unused].
  // - `$400E`: NOISE_LO.
  // - `$400F`: NOISE_HI.
  // .
  // | Delta Modulation Channel:
  // - `$4010`: DMC_FREQ: IRQ flag, loop flag and frequency.
  // - `$4011`: DMC_RAW: 7 bit DAC (Digital-Analog Converter).
  // - `$4012`: DMC_START: Start address = `$C000` + `$40*$xx`.
  // - `$4013`: DMC_LEN: Sample length = `$10` * `$xx` + 1 bytes (128 * `$xx` +
  // 8 samples).
  // .
  // | PPU:
  // - `$4014`: Suspends the CPU so it can quickly copy a page of CPU memory to
  // PPU OAM using DMA.
  // .
  // | APU:
  // - `$4015`: Enable and disable individual channels, control the DMC.
  // * Write: Disable individual channels and silence the DMC after it empties.
  // * Read: Check which channels were enabled.
  // .
  // | Joystick:
  // - `$4016`: JOY1.
  // * Write: Set strobe signal to capture current state of all buttons in both
  // controllers.
  // * Read: Joystick 1 data.
  // - `$4017`: JOY2.
  // * Write: Frame counter control.
  // * Read: Joystick 2 data.
  // ---
  // `$4018–$401F`: APU and I/O functionality (Usually disabled).
  // `$4020–$FFFF`: Cartridge use:
  // - `$6000–$7FFF`: Cartridge RAM.
  // - `$8000–$FFFF`: Cartridge ROM.
  // .
  // Sources:
  // - https://www.nesdev.org/wiki/CPU_memory_map
  // - https://www.nesdev.org/wiki/2A03
  // - https://www.nesdev.org/wiki/PPU_registers
  uint8_t memory[0x10000];

  uint8_t a; // rw to memory, store arithmetic and logic results.

  uint8_t x; // rw to memory, primarily counter in loops or memaddress.

  uint8_t y; // similar to x but not interchangeable.

  // Status flags:
  // `NV_B DIZC`
  // `N` - Negative: After most instructions that have a value result, this flag
  // will contain bit 7 of that result.
  // `V` - Overflow: ADC and SBC will set this flag if the signed result would
  // be invalid, necessary for making signed comparisons. BIT will load bit 6 of
  // the addressed value directly into the V flag. Can be cleared directly with
  // CLV.
  // `_` - Unused bit.
  // `B` - No effect in the CPU directly but used by software. Represents a
  // transient signal in the CPU controlling whether it was processing an
  // interrupt when the flags were pushed. B is 0 when pushed by interrupts (NMI
  // and IRQ) and 1 when pushed by instructions (BRK and PHP).
  // `D` - On the NES, decimal mode is disabled and so this flag has no effect.
  // However, it still exists and can be observed and modified, as normal. On
  // the original 6502, this flag causes some arithmetic instructions to use
  // binary-coded decimal to make base 10 calculations easier. Can be set or
  // cleared directly with SED or CLD.
  // `I` - Interrupt Disable: Inhibits IRQ. NMI, BRK, and reset are not
  // affected. Can be set or cleared directly with SEI or CLI. Automatically set
  // by the CPU after pushing flags to the stack when any interrupt is triggered
  // (NMI, IRQ/BRK, or reset). Restored to its previous state from the stack
  // when leaving an interrupt handler with RTI. If an IRQ is pending when this
  // flag is cleared (i.e. the /IRQ line is low), an interrupt will be triggered
  // immediately. However, the effect of toggling this flag is delayed 1
  // instruction when caused by SEI, CLI, or PLP.
  // `Z` - Zero: After most instructions that have a value result, this flag
  // will either be set or cleared based on whether or not that value is equal
  // to zero.
  // `C` - Carry: After ADC, this is the carry result of the addition. After SBC
  // or CMP, both of which do subtraction, this flag will be set if no borrow
  // was the result, or alternatively a "greater than or equal" result. After a
  // shift instruction (ASL, LSR, ROL, ROR), this contains the bit that was
  // shifted out. Increment and decrement instructions do not affect the carry
  // flag. Can be set or cleared directly with SEC or CLC.
  //
  // Source: https://www.nesdev.org/wiki/Status_flags
  uint8_t flag;

  uint8_t stack_pointer; // current location on the stack.

  uint16_t counter; // position in the program
} Control;

uint8_t mem_read(Control *c, uint16_t addr);

void mem_write(Control *c, uint16_t addr, uint8_t value);

// Source: https://www.nesdev.org/wiki/
#endif
