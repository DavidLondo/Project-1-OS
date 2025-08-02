#include <stdio.h>
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

    //char process_list[100]; // Define size for the buffer

    fclose(processes);
    close_logger();

    return 0;
}

// How to log 
// log_message("This is a log message.");