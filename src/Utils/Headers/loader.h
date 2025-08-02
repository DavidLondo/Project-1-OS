#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include "queue.h"

void load_processes_from_file(FILE* f, Queue* queue);

#endif