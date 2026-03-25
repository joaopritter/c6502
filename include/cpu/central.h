#ifndef CENTRAL_H
#define CENTRAL_H
#include "cpu/control.h"
#include "cpu/logic.h"

typedef struct {
  Control control;
  Logic logic;
} CPU;

CPU init_cpu();

void load(CPU *cpu, uint8_t program[]);

void exec(CPU *cpu, OPCode c);

void run(CPU *cpu);
#endif
