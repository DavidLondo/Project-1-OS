#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Headers/loader.h"
#include "Headers/instruction.h"
#include "Headers/parser.h"
#include "Headers/process.h"

void load_processes_from_file(FILE* file, Queue* queue) {
    char line[256];
    int pid, ax, bx, cx, quantum;

    while (fgets(line, sizeof(line), file)) {
        if (!parse_process_line(line, &pid, &ax, &bx, &cx, &quantum)) {
            printf("Línea inválida: %s", line);
            continue;
        }

        Instruction instructions[MAX_INSTRUCTIONS];
        int num_inst = load_instructions_from_file(pid, instructions);

        if (num_inst < 0) {
            printf("Can not load the file instructions for PID %d\n", pid);
            continue;
        }

        Process* p = process_create(pid, ax, bx, cx, quantum, instructions, num_inst);
        printf("LOADED: %p -> pid: %d quantum: %d\n", (void*)p, p->pid, p->quantum);
        queue_enqueue(queue, p);
        printf("Process %d loaded. \n", pid);
        process_print_state(p);
    }
}
