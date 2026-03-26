#ifndef FLAGS_H
#define FLAGS_H
#include <stdint.h>

#include "control.h"

#define NEGATIVE_FLAG 0b10000000
#define OVERFLOW_FLAG 0b01000000
#define EXTRA_FLAG 0b00100000
#define BREAK_FLAG 0b00010000
#define DECIMAL_FLAG 0b00001000
#define INTERRUPT_DISABLE_FLAG 0b00000100
#define ZERO_FLAG 0b00000010
#define CARRY_FLAG 0b00000001

int check_flag(Control *c, int flag);

void assign_flag(Control *c, int set, int flag);

int check_negative_flag(Control *c);

void assign_negative_flag(Control *c, uint8_t result);

int check_overflow_flag(Control *c);

void assign_overflow_flag(Control *c, uint8_t is_overflow);

int check_interrupt_disable_flag(Control *c);

void assign_interrupt_disable_flag(Control *c, uint8_t set);

int check_zero_flag(Control *c);

void assign_zero_flag(Control *c, uint8_t result);

void assign_nz_flags(Control *c, uint8_t result);

int check_break_flag(Control *c);

void assign_break_flag(Control *c, uint8_t is_break);

int check_carry_flag(Control *c);

void assign_carry_flag(Control *c, uint8_t is_carry);

#endif
