#include "flags.h"

int check_flag(Control *c, int flag) { return (c->status & flag) != 0; }

void assign_flag(Control *c, int set, int flag) {
  if (set)
    c->status |= flag;
  else
    c->status &= ~flag;
}

int check_negative_flag(Control *c) { return check_flag(c, NEGATIVE_FLAG); }

void assign_negative_flag(Control *c, uint8_t result) {
  assign_flag(c, (result & NEGATIVE_FLAG) != 0, NEGATIVE_FLAG);
}

int check_overflow_flag(Control *c) { return check_flag(c, OVERFLOW_FLAG); }

void assign_overflow_flag(Control *c, uint8_t is_overflow) {
  assign_flag(c, is_overflow, OVERFLOW_FLAG);
}

int check_zero_flag(Control *c) { return check_flag(c, ZERO_FLAG); }

void assign_zero_flag(Control *c, uint8_t result) {
  assign_flag(c, result == 0, ZERO_FLAG);
}

void assign_nz_flags(Control *c, uint8_t result) {
  assign_negative_flag(c, result);
  assign_zero_flag(c, result);
}

int check_break_flag(Control *c) { return check_flag(c, BREAK_FLAG); }

void assign_break_flag(Control *c, uint8_t is_break) {
  assign_flag(c, is_break, BREAK_FLAG);
}

int check_carry_flag(Control *c) { return check_flag(c, CARRY_FLAG); }

void assign_carry_flag(Control *c, uint8_t is_carry) {
  assign_flag(c, is_carry, CARRY_FLAG);
}
