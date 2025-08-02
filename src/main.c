#include <stdio.h>
#include <stdlib.h>

#include "Utils/Headers/loader.h"
#include "Utils/Headers/queue.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <archivo>\n", argv[0]);
        return 1;
    }

    // File log
    FILE *log = fopen("logger.log", "a+");
    if (log == NULL) {
        printf("Error opening logger.log\n");
        return 1;
    }

    // Processes file
    FILE *processes = fopen(argv[1], "r");
    if (processes == NULL) {
        fprintf(log, "Error opening file: %s\n", argv[1]);
        fclose(log);
        return 1;            
    }

    fprintf(log, "File %s opened succesfully!\n", argv[1]);
    
    // Processes queue
    Queue* queue = queue_create();
    if (!queue) {
        fprintf(log, "Error making processes queue");
        fclose(processes);
        fclose(log);
        return 1;
    }

    load_processes_from_file(processes, queue);
    fprintf(log, "Processes load to the queue");

    queue_destroy(queue);
    fclose(processes);
    fclose(log);

    return 0;
}