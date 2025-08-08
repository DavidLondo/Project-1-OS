#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Utils/Headers/scheduler.h"
#include "../Utils/Headers/queue.h"
#include "../Utils/Headers/process.h"
#include "../Utils/Headers/instruction.h"  // para execute_instruction

void simulate_scheduler(Queue* queue) {
    int clock_cycle = 0;

    while (!queue_is_empty(queue)) {
        Process* p = (Process*) queue_dequeue(queue);
        
        if (!p) {
            fprintf(stderr, "Error: Process Null when dequeue.\n");
            continue; 
        }

        printf("\n[Context Switch] PID: %d (Quantum: %d)\n", p->pid, p->quantum);
        strcpy(p->state, "Running");
        int quantum_remaining = p->quantum;

        while (quantum_remaining > 0 && p->pc < p->num_instructions) {

            printf("Cycle %d | PID %d | Executing: ", clock_cycle, p->pid);
            // Llamamos a la función que ejecuta la instrucción y que actualiza el pc internamente
            process_execute_instruction(p);

            process_print_state(p);

            quantum_remaining--;
            clock_cycle++;
            p->pc++;
        }
        strcpy(p->state, "Ready");

        if (p->pc < p->num_instructions) {
            queue_enqueue(queue, p);
        } else {
            printf("------> PID %d has finished execution. <------\n", p->pid);
            strcpy(p->state, "Terminated");
            process_print_state(p);

            process_free(p);
        }
    }

    printf("\nSimulation finished at clock cycle: %d\n", clock_cycle);
}
