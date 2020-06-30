#include "../include/task.h"

Task* Task_factory(bool accomplished, char priority, char * text, 
                    char * creation_str, char * end_str)
{
    Task* task = malloc(sizeof(Task));
    fatal(task != NULL, "task is a null pointer", 1);
    task->accomplished = accomplished;
    task->priority = priority;
    strcpy(task->text, text);

    Date* creation = Date_factory(creation_str);
    Date* end = Date_factory(end_str);
    task->creation = creation;
    task->end = end;
    return task;
}

void Task_destructor(Task* task)
{
    Date_destructor(task->creation);
    Date_destructor(task->end);
    free(task);
}

int Task_cmp(Task* first, Task* second)
{
    if (first->priority < second->priority)
        return 1;
    else if (first->priority > second->priority)
        return -1;
    return 0;
}

const char* str_accomplished(bool accomplished)
{
    if (accomplished)
    {
        return GRN "V"; 
    }
    return RED "X";
}

void Task_print(Task* task)
{
    printf("%s " YEL "%c " RST "%s\n", str_accomplished(task->accomplished), task->priority, task->text);
}

/*
const char* ...
    char* task_buffer = malloc(sizeof(MAX_TASK) + 1);
    snprintf(task_buffer, sizeof(MAX_TASK + 1), "%c %c %s", str_accomplished(task->accomplished),
    task->priority, task->text);
    return task_buffer;
*/
