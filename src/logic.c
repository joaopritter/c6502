#include <stdint.h>
#include <string.h>

#include "addr_mode.h"
#include "logic.h"
#include "instr.h"

OPCode decode(uint8_t code) {
  return instr_table[code];
}
