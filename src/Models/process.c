#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/Headers/process.h"
#include "../Utils/Headers/instruction.h"

Process* process_create(int pid, int ax, int bx, int cx, int quantum, Instruction* instructions, int num_inst) {
    Process* p = malloc(sizeof(Process));
    if (!p) return NULL;

    p->pid = pid;
    p->pc = 0;
    p->ax = ax;
    p->bx = bx;
    p->cx = cx;
    p->quantum = quantum;
    strcpy(p->state, "Ready");
    p->num_instructions = num_inst;

    p->instructions = malloc(sizeof(Instruction) * num_inst);
    if (!p->instructions) {
        free(p);
        return NULL;
    }

    for (int i = 0; i < num_inst; ++i) {
        p->instructions[i] = instructions[i];
    }

    return p;
}

void process_free(Process* p) {
    if (p) {
        free(p->instructions);
        free(p);
    }
}

void process_execute_instruction(Process* p) {
    if (p->pc < 0 || p->pc >= p->num_instructions) {
        printf("[ERROR] PC fuera de rango: %d\n", p->pc);
        return;
    }

    Instruction* inst = &p->instructions[p->pc];
    execute_instruction(inst, p); // usamos la función unificada

    // Si no fue un salto, avanzamos PC
    if (inst->type != INST_JMP) {
        p->pc++;
    }
}

int process_has_finished(const Process* p) {
    return p->pc >= p->num_instructions;
}

void process_print_state(const Process* p) {
    printf("  PID=%d | PC=%d | AX=%d | BX=%d | CX=%d | State=%s\n",
        p->pid, p->pc, p->ax, p->bx, p->cx, p->state);
}
