#ifndef PROCESS_H
#define PROCESS_H
#define MAX_STATE_LEN 20
#define MAX_INSTRUCTIONS 100
#include "instruction.h"

typedef struct Process {
    int pid;
    int pc;
    int ax, bx, cx;
    int quantum;
    char state[MAX_STATE_LEN];
    Instruction* instructions;
    int num_instructions;
} Process;

Process* process_create(int pid, int ax, int bx, int cx, int quantum, Instruction* instructions, int num_inst); // Process constructor
void process_free(Process* p); // free process
void process_execute_instruction(Process* p, Instruction* inst); // Execute instruction
int process_has_finished(const Process* p); 
void process_print_state(const Process* p); // Actual state

#endif