#include <stdio.h>
#include <stdlib.h>

#include "../Utils/Headers/scheduler.h"
#include "../Utils/Headers/queue.h"
#include "../Utils/Headers/process.h"

void simulate_scheduler(Queue* queue) {
    int clock_cycle = 0;

    while (!queue_is_empty(queue)) {
        Process* p = (Process*) queue_dequeue(queue);
        
        if (!p) {
            fprintf(stderr, "Error: Process Null when dequeue.\n");
            continue; 
        }

        printf("\n[Context Switch] PID: %d (Quantum: %d)\n", p->pid, p->quantum);

        int quantum_remaining = p->quantum;

        while (quantum_remaining > 0 && p->pc < p->num_instructions) {
            Instruction inst = p->instructions[p->pc];

            printf("Cycle %d | PID %d | Executing: ", clock_cycle, p->pid);
            process_execute_instruction(p, &inst);
            process_print_state(p);

            p->pc++;
            quantum_remaining--;
            clock_cycle++;
        }

        if (p->pc < p->num_instructions) {
            queue_enqueue(queue, p);
        } else {
            printf("------> PID %d has finished execution. <------\n", p->pid);
            process_free(p);
        }
    }

    printf("\nSimulation finished at clock cycle: %d\n", clock_cycle);
}