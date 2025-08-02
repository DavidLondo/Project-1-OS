#include "Headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_process_line(const char* line, int* pid, int* ax, int* bx, int* cx, int* quantum) {
    return sscanf(line, "PID: %d, AX=%d, BX=%d, CX=%d, Quantum=%d", pid, ax, bx, cx, quantum) == 5;
}

InstructionType get_instruction_type(const char* instr) {
    if (strcmp(instr, "ADD") == 0) return ADD;
    if (strcmp(instr, "SUB") == 0) return SUB;
    if (strcmp(instr, "INC") == 0) return INC;
    return NOP;
}

int load_instructions_from_file(int pid, Instruction* instructions) {
    char filename[256];
    snprintf(filename, sizeof(filename), "instructions/%d.txt", pid);
    FILE* file = fopen(filename, "r");

    if (!file) {
        perror("Error opening instruction file");
        return -1;
    }

    char line[128];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_INSTRUCTIONS) {
        char op[10];
        int op1 = 0, op2 = 0;

        int num_tokens = sscanf(line, "%s %d %d", op, &op1, &op2);
        instructions[count].type = get_instruction_type(op);
        instructions[count].operand1 = op1;
        instructions[count].operand2 = (num_tokens == 3) ? op2 : 0;
        instructions[count].result = 0;
        count++;
    }

    fclose(file);
    return count;
}