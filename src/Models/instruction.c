#include "../Utils/Headers/process.h"
#include "../Utils/Headers/instruction.h"
#include <stdio.h>

void execute_instruction(Instruction* instr, Process* proc) {
    switch (instr->type) {
        case ADD:
            instr->result = proc->ax + proc->bx;
            proc->ax = instr->result;
            printf("    [ADD] AX = AX + BX -> %d\n", proc->ax );
            break;
        
        case INC:
            proc->ax += 1;
            instr->result = proc->ax;
            printf("    [INC] AX++ -> %d\n", proc->ax);
            break;
        
        case SUB:
            proc->cx -= 1;
            instr->result = proc->cx;
            printf("    [SUB] CX-- -> %d\n", proc->cx);
            break;
        
        case NOP:
            printf("    [NOP] No operation.\n");
            break;
        
        default:
            printf("    [ERROR] Unknown instruction. \n");
            break;
    }
}
