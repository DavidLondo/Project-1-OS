#include "../Utils/Headers/process.h"
#include "../Utils/Headers/instruction.h"
#include <stdio.h>

// Helper para acceder a un registro según el enum
static int* get_register_ptr(Process* proc, RegisterType reg) {
    switch (reg) {
        case REG_AX: return &proc->ax;
        case REG_BX: return &proc->bx;
        case REG_CX: return &proc->cx;
        default: return NULL;
    }
}

void execute_instruction(Instruction* instr, Process* proc) {
    int val1 = instr->is_op1_reg ? *get_register_ptr(proc, instr->op1_reg) : instr->op1_val;
    int val2 = instr->is_op2_reg ? *get_register_ptr(proc, instr->op2_reg) : instr->op2_val;
    int* reg1_ptr = instr->is_op1_reg ? get_register_ptr(proc, instr->op1_reg) : NULL;

    switch (instr->type) {
        case INST_ADD:
            if (reg1_ptr) {
                *reg1_ptr = val1 + val2;
                printf("    [ADD] %s = %d + %d -> %d\n",
                       instr->op1_reg == REG_AX ? "AX" :
                       instr->op1_reg == REG_BX ? "BX" : "CX",
                       val1, val2, *reg1_ptr);
            }
            break;

        case INST_SUB:
            if (reg1_ptr) {
                *reg1_ptr = val1 - val2;
                printf("    [SUB] %s = %d - %d -> %d\n",
                       instr->op1_reg == REG_AX ? "AX" :
                       instr->op1_reg == REG_BX ? "BX" : "CX",
                       val1, val2, *reg1_ptr);
            }
            break;

        case INST_MUL:
            if (reg1_ptr) {
                *reg1_ptr = val1 * val2;
                printf("    [MUL] %s = %d * %d -> %d\n",
                       instr->op1_reg == REG_AX ? "AX" :
                       instr->op1_reg == REG_BX ? "BX" : "CX",
                       val1, val2, *reg1_ptr);
            }
            break;

        case INST_INC:
            if (reg1_ptr) {
                (*reg1_ptr)++;
                printf("    [INC] %s++ -> %d\n",
                       instr->op1_reg == REG_AX ? "AX" :
                       instr->op1_reg == REG_BX ? "BX" : "CX",
                       *reg1_ptr);
            }
            break;

        case INST_JMP:
            proc->pc = instr->op1_val; // salto directo
            printf("    [JMP] Saltando a instrucción %d\n", proc->pc);
            return; // no avanzar pc automáticamente

        case INST_NOP:
            printf("    [NOP] No operation.\n");
            break;

        default:
            printf("    [ERROR] Instrucción desconocida.\n");
            break;
    }

}
