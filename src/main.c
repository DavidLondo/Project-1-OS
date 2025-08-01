#include <stdio.h>
#include "Utils/Headers/aux.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <archivo>\n", argv[0]);
        return 1;
    }

    FILE *log = fopen("logger.log", "a+");

    if (log == NULL) {
        printf("Error opening log file.\n");
        return 1;
    }

    FILE *processes = fopen(argv[1], "r+");
    
        if (processes != NULL) {
            // Logic
            // while(fgets(fptr, 100, fptr)) {
            //     printf("%s", fptr);
            // }
            fprintf(log, "File opened successfully\n");
            printf("File opened successfully.\n"); // Remove later
        } else {
            printf("Error opening file.\n");
            fprintf(log, "Error opening file");
            return 1;
        }

    //char process_list[100]; // Define size for the buffer

    fclose(processes);
    fclose(log);

    return 0;
}

// How to log 
// fprintf(log, "Your log message here\n");