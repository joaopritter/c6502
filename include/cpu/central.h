#ifndef CENTRAL_H
#define CENTRAL_H
#include "cpu/control.h"
#include "cpu/logic.h"

#define STACK_RESET 0xfd

typedef struct {
  Control control;
  Logic logic;
} CPU;

CPU init_cpu();

void reset(CPU *cpu);

void load(CPU *cpu, uint8_t program[]);

void exec(CPU *cpu, OPCode c);

void run(CPU *cpu);
#endif
