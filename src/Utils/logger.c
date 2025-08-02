#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"

static FILE *file = NULL;

void init_logger(const char *filename) {
    if (file == NULL) {
        file = fopen(filename, "a+");
        if (file == NULL) {
            fprintf(stderr, "Error opening log file: %s\n", filename);
            exit(1);
        }
    } else {
        fprintf(stderr, "Logger already initialized.\n");
    }
}

void log_message(const char *message) {
    if (file == NULL) {
        fprintf(stderr, "Logger not initialized.\n");
        return;
    }
}

void close_logger() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}