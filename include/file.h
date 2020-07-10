#pragma once

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/task.h"

extern ssize_t read_task(const char* filename, unsigned int id, Task** task);
extern void read_tasks(const char* filename, Tasks** tasks);
extern void rewrite_tasks(const char* filename, Tasks* tasks);
extern bool init_ido();
