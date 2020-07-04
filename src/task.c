#include "../include/task.h"

/* SINGLE TASK */

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

void Task_set_state(Task* task, bool state)
{
    task->accomplished = state;
}

void Task_destructor(Task* task)
{
    Date_destructor(task->creation);
    Date_destructor(task->end);
    free(task);
}

int Task_cmp_default(Task* first, Task* second)
{
    if (first->id < second->id)
        return 1;
    else if (first->id > second->id)
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
    printf(YEL "#%d " RST "%s " CYN "%c " RST "%s " BLU "%s " RST "> " MAG "%s" RST "\n", task->id, str_accomplished(task->accomplished),
            task->priority, task->text, task->creation->toString, task->end->toString);
}


/** TASKS CONTAINER **/

void Task_pretty(Task* task)
{
    printf("--------------------------------------------------\n"
            YEL "#%d\n" RST
            "Accomplished : %s\n" RST
            "Priority     : " CYN "%c\n" RST
            "To do        : %s\n"
            "Created      : " BLU "%s\n" RST
            "End          : " MAG "%s\n" RST,
            task->id, str_accomplished(task->accomplished), task->priority, task->text,
            task->creation->toString, task->end->toString);
}

Tasks* Tasks_factory()
{
    Tasks* tasks = malloc(sizeof(Tasks));
    tasks->count = 0;
    return tasks;
}

void Tasks_destructor(Tasks* tasks)
{
    free(tasks);
}

void Tasks_add(Tasks* tasks, Task* task)
{
    tasks->arr[tasks->count] = task;
    tasks->count++;
}
