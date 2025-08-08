#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/Headers/process.h"


Process* process_create(int pid, int ax, int bx, int cx, int quantum, Instruction* instructions, int num_inst) {
    Process* p = (Process*)malloc(sizeof(Process));
    // Variable asignation
    p->pid = pid;
    p->pc = 0;
    p->ax = ax;
    p->bx = bx;
    p->cx = cx;
    p->quantum = quantum;
    strcpy(p->state, "Ready");
    p->num_instructions = num_inst;
    p->instructions = (Instruction*)malloc(sizeof(Instruction) * num_inst);

    for (int i = 0; i < num_inst; ++i) {
        p->instructions[i] = instructions[i]; // copy instructions
    }

    return p;
}

void process_free(Process* p) {
    if (p) {
        free(p->instructions);
        free(p);
    }
}

void process_execute_instruction(Process* p, Instruction* inst) {
    int* reg;

    // Select register (operand1)
    switch (inst->operand1) {
        case 0: reg = &p->ax; break;
        case 1: reg = &p->bx; break;
        case 2: reg = &p->cx; break;
        default: printf("Invalid operand\n"); return;
    }

    switch (inst->type) {
        case ADD:
            *reg += inst->operand2;
            printf("ADD R%d, %d\n", inst->operand1, inst->operand2);
            break;
        case SUB:
            *reg -= inst->operand2;
            printf("SUB R%d, %d\n", inst->operand1, inst->operand2);
            break;
        case INC:
            (*reg)++;
            printf("INC R%d\n", inst->operand1);
            break;
        case NOP:
        default:
            printf("NOP\n");
            break;
    }
}


int process_has_finished(const Process* p) {
    return p->pc >= p->num_instructions;
}

void process_print_state(const Process* p) {
    printf("  PID=%d | PC=%d | AX=%d | BX=%d | CX=%d | State=%s\n",
        p->pid, p->pc, p->ax, p->bx, p->cx, p->state);
}