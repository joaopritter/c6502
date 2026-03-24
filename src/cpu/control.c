#include <stdint.h>

#include "cpu/control.h"

uint8_t mem_read(Control *c, uint16_t addr) { return c->memory[addr]; }
