#pragma once

#include "../include/ansi_colors.h"
#include "../include/date.h"

#ifndef MAX_TEXT
    #define MAX_TEXT 256
#endif
#ifndef MAX_TASKS
    #define MAX_TASKS 1024
#endif

typedef struct Task {
    unsigned int id;
    bool accomplished;
    char priority;
    char text[MAX_TEXT];
    Date* creation;
    Date* end;
} Task;

extern Task* Task_factory(unsigned int id, bool accomplished, const char priority, const char* text, 
                            const char* creation_str, const char* end_str);
extern void Task_destructor(Task* task);
extern void Task_print(Task* task);
extern void Task_pretty(Task* task);

typedef struct Tasks {
    unsigned int count;
    Task* arr[MAX_TASKS];
} Tasks;

extern Tasks* Tasks_factory();
extern void Tasks_add(Tasks* tasks, Task* task, unsigned int index);
extern void Tasks_destructor(Tasks* tasks);
