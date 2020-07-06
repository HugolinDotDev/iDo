#pragma once

#include <stdlib.h>

#include "../include/task.h"

extern ssize_t read_task(const char* filename, unsigned int id, Task** task);
extern void read_tasks(const char* filename, Tasks** tasks);
extern bool write_task(const char* filename, const char* task);
extern bool set_state_task(const char* filename, const char* command, Task* task);
extern bool rm_task(const char* filename, unsigned int id);
