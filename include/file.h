#pragma once

#include <stdlib.h>

#include "../include/task.h"

#ifndef MAX_LINES
    #define MAX_LINES 1024
#endif

extern const char* read_task(const char* filename, unsigned int id);
extern void read_tasks(const char* filename, Task** tasks);
extern int write_task(const char* filename, const char* task);
extern int delete_task(const char* filename, unsigned int id);
