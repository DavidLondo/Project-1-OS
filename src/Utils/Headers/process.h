#ifndef PROCESS_H
#define PROCESS_H

#define MAX_STATE_LEN 20
#include "instruction.h"

typedef struct Process {
    int pid;
    int pc; // Program counter
    int ax, bx, cx; // Registros
    int quantum;
    char state[MAX_STATE_LEN];
    Instruction* instructions;
    int num_instructions;
} Process;

Process* process_create(int pid, int ax, int bx, int cx, int quantum,
                        Instruction* instructions, int num_inst);

void process_free(Process* p);
void process_execute_instruction(Process* p);
int process_has_finished(const Process* p);
void process_print_state(const Process* p);

#endif
