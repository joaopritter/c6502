#ifndef CENTRAL_H
#define CENTRAL_H
#include "control.h"
#include "logic.h"

typedef struct {
  Control control;
} CPU;

CPU init_cpu();

void reset(CPU *cpu);

void load(CPU *cpu, uint8_t program[]);

void exec(CPU *cpu, OPCode c);

void run(CPU *cpu);
#endif
