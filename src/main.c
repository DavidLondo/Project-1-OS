#include <stdio.h>
#include "Utils/Headers/aux.h"

int main() {

    FILE *fptr;

    fptr = fopen("test.txt", "r");

    char process_list[100];

    if (fptr != NULL) {
        // Logic
        // while(fgets(fptr, 100, fptr)) {
        //     printf("%s", fptr);
        // }
    } else {
        printf("Error opening file.\n");
        return 1;
    }

    fclose(fptr);
}