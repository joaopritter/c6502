#include "addr_mode.h"
#include "cpu/control.h"
#include <stdint.h>

uint16_t IMM(Control *cu) { return cu->counter++; };

uint16_t IMP(Control *cu) { return 0; };
