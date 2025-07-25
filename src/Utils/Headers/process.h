#include "aux.h"

typedef struct {
    int pid;
    int pc;
    int ax, bx, cx;
    int quantum;
    char estado[10];
} Process;