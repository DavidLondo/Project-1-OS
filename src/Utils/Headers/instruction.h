#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct Process; // Forward declaration
typedef struct Process Process;

// Tipos de instrucciones
typedef enum {
    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_INC,
    INST_JMP,
    INST_NOP
} InstructionType;

// Registros posibles
typedef enum {
    REG_AX,
    REG_BX,
    REG_CX,
    REG_NONE // para cuando el operando es un número
} RegisterType;

typedef struct {
    InstructionType type; // Tipo de instrucción
    RegisterType op1_reg; // Primer operando si es registro
    RegisterType op2_reg; // Segundo operando si es registro
    int op1_val;          // Primer operando si es número
    int op2_val;          // Segundo operando si es número
    int is_op1_reg;       // 1 si op1 es registro, 0 si es número
    int is_op2_reg;       // 1 si op2 es registro, 0 si es número
} Instruction;

// Ejecuta una instrucción sobre un proceso
void execute_instruction(Instruction* instr, Process* proc);

#endif
