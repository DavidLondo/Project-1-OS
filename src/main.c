#include <stdio.h>
#include "Utils/Headers/aux.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <archivo>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    
        if (file != NULL) {
            // Logic
            // while(fgets(fptr, 100, fptr)) {
            //     printf("%s", fptr);
            // }
        } else {
            printf("Error opening file.\n");
            return 1;
        }

    char process_list[100]; // Define size for the buffer

    fclose(file);

    return 0;
}