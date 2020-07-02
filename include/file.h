#pragma once

#include <stdlib.h>

#include "../include/task.h"

extern Task* read_task(const char* filename, unsigned int id);
extern void read_tasks(const char* filename, Tasks* tasks);
extern int write_task(const char* filename, const char* task);
extern int rm_task(const char* filename, unsigned int id);
