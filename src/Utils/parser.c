#include "Headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/Headers/instruction.h"

#define MAX_LINE_LEN 256

// Helper: convierte token a RegisterType; devuelve 1 si fue registro, 0 si no.
static int parse_register(const char* token, RegisterType* out) {
    if (strcmp(token, "AX") == 0) { *out = REG_AX; return 1; }
    if (strcmp(token, "BX") == 0) { *out = REG_BX; return 1; }
    if (strcmp(token, "CX") == 0) { *out = REG_CX; return 1; }
    *out = REG_NONE;
    return 0;
}

static void strip_comma(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == ',') {
        str[len - 1] = '\0';
    }
}

int parse_process_line(const char* line, int* pid, int* ax, int* bx, int* cx, int* quantum) {
    return sscanf(line, "PID: %d, AX=%d, BX=%d, CX=%d, Quantum=%d", pid, ax, bx, cx, quantum) == 5;
}

InstructionType get_instruction_type(const char* instr) {
    if (strcmp(instr, "ADD") == 0)  return INST_ADD;
    if (strcmp(instr, "SUB") == 0)  return INST_SUB;
    if (strcmp(instr, "MUL") == 0)  return INST_MUL;
    if (strcmp(instr, "INC") == 0)  return INST_INC;
    if (strcmp(instr, "JMP") == 0)  return INST_JMP;
    return INST_NOP;
}

/*
  Formato esperado por línea de archivo de instrucciones (por convención):
    - ADD <DEST_REG> <SRC>     (SRC puede ser REG o número)
    - SUB <DEST_REG> <SRC>
    - MUL <DEST_REG> <SRC>
    - INC <REG>
    - JMP <numero_de_instruccion>
    - NOP
  Líneas vacías o que comiencen con '#' se ignoran.
*/
int load_instructions_from_file(int pid, Instruction* instructions) {
    char filename[256];
    snprintf(filename, sizeof(filename), "instructions/%d.txt", pid);
    FILE* file = fopen(filename, "r");

    if (!file) {
        perror("Error opening instruction file");
        return -1;
    }

    char line[MAX_LINE_LEN];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_INSTRUCTIONS) {
        // Trim leading spaces
        char* p = line;
        while (*p == ' ' || *p == '\t') p++;

        // Skip empty or comments
        if (*p == '\0' || *p == '\n' || *p == '#') continue;

        char op[16] = {0}, arg1[32] = {0}, arg2[32] = {0};
        Instruction instr = {0};

        // Leer operación
        if (sscanf(p, "%15s", op) != 1) {
            continue; // línea inválida
        }

        // Inicializar campos de instrucción
        instr.type = get_instruction_type(op);
        instr.op1_reg = REG_NONE;
        instr.op2_reg = REG_NONE;
        instr.op1_val = 0;
        instr.op2_val = 0;
        instr.is_op1_reg = 0;
        instr.is_op2_reg = 0;

        switch (instr.type) {
            case INST_ADD:
            case INST_SUB:
            case INST_MUL: {
                // Intentar con coma pegada o no
                int num_tokens = sscanf(p, "%15s %31[^,],%31s", op, arg1, arg2);
                if (num_tokens < 2) {
                    num_tokens = sscanf(p, "%15s %31s %31s", op, arg1, arg2);
                }
                strip_comma(arg1);
                strip_comma(arg2);

                RegisterType dst;
                if (!parse_register(arg1, &dst)) {
                    fprintf(stderr, "Destino debe ser registro para %s: %s\n", op, line);
                    continue;
                }
                instr.op1_reg = dst;
                instr.is_op1_reg = 1;

                // Segundo operando
                if (num_tokens >= 3 && parse_register(arg2, &instr.op2_reg)) {
                    instr.is_op2_reg = 1;
                } else {
                    instr.op2_val = (num_tokens >= 3) ? atoi(arg2) : 0;
                    instr.is_op2_reg = 0;
                }
                break;
            }

            case INST_INC: {
                // Solo un operando, sin coma
                if (sscanf(p, "%15s %31s", op, arg1) < 2) {
                    fprintf(stderr, "INC requiere un registro: %s\n", line);
                    continue;
                }
                RegisterType r;
                if (!parse_register(arg1, &r)) {
                    fprintf(stderr, "INC necesita registro como operando: %s\n", line);
                    continue;
                }
                instr.op1_reg = r;
                instr.is_op1_reg = 1;
                break;
            }

            case INST_JMP: {
                if (sscanf(p, "%15s %31s", op, arg1) < 2) {
                    fprintf(stderr, "JMP requiere un número objetivo: %s\n", line);
                    continue;
                }
                instr.op1_val = atoi(arg1);
                instr.is_op1_reg = 0;
                break;
            }

            case INST_NOP:
            default:
                // NOP no hace nada
                break;
        }

        instructions[count++] = instr;
    }

    fclose(file);
    return count;
}
