#include "../include/task.h"

Task* Task_factory(unsigned int id, bool accomplished, const char priority, const char* text, 
                    const char* creation_str, const char* end_str)
{
    Task* task = malloc(sizeof(Task));
    fatal(task != NULL, "task is a null pointer", 1);
    task->id = id;
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
    printf("#%d %s " YEL "%c " RST "%s %s %s\n", task->id, str_accomplished(task->accomplished),
            task->priority, task->text, task->creation->toString, task->end->toString);
}
