#ifndef PARSER_H
#define PARSER_H

#include "process.h"
#include "instruction.h"

int parse_process_line(const char* line, int* pid, int* ax, int* bx, int* cx, int* quantum);
int load_instructions_from_file(int pid, Instruction* instructions);

#endif