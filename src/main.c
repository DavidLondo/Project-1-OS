#include <stdio.h>
#include <stdlib.h>

#include "Utils/Headers/loader.h"
#include "Utils/Headers/queue.h"
#include "logger.h"
#include "Utils/Headers/aux.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <archivo>\n", argv[0]);
        return 1;
    }

    init_logger("log.txt");

    FILE *processes = fopen(argv[1], "r+");
    
        if (processes != NULL) {
            // Logic
            // while(fgets(fptr, 100, fptr)) {
            //     printf("%s", fptr);
            // }
            log_message("File opened successfully.");
            printf("File opened successfully.\n"); // Remove later
        } else {
            printf("Error opening file.\n");
            log_message("Error opening file.");
            return 1;
        }

    load_processes_from_file(processes, queue);
    
    simulate_scheduler(queue);
    queue_destroy(queue);
    fclose(processes);
    close_logger();

    return 0;
}

// How to log 
// log_message("This is a log message.");