#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct Process;
typedef struct Process Process;

typedef enum {
    ADD,
    INC,
    SUB,
    NOP
} InstructionType;

typedef struct {
    InstructionType type;
    int operand1;
    int operand2;
    int result;
} Instruction;

// Execute the instruction on each process 
void execute_instruction(Instruction* instr, Process* proc); 

#endif