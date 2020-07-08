#include "../include/cmd.h"

void print_help()
{
    printf(YEL "Usage : " RST "todoit COMMAND [OPTIONS]\n\n"
            GRN "la          " RST "Print the tasks with details\n"
            GRN "ls          " RST "Print the tasks\n"
            GRN "add         " RST "Add a task\n"
            GRN "edit        " RST "Edit a task\n"
            GRN "rm          " RST "Delete a task\n"
            GRN "tick        " RST "Complete a task\n"
            GRN "ntick       " RST "Uncomplete a task\n"
            GRN "find        " RST "Find a task by its id\n");
}

bool check_cmd_exists(const char* cmd, const char* cmds[], unsigned int len)
{
    for (unsigned int i = 0; i < len; i++)
    {
        if (!strcmp(cmd, cmds[i]))
            return true;
    }
    printf(RED "Command '%s' does not exist\n" RST, cmd);
    return false;
}

bool process_cmd(int argc, char* argv[])
{
    char cmd[10];
    strcpy(cmd, argv[1]);
    if (!strcmp(cmd, "h"))
    {
        print_help();
    }
    else if (!strcmp(cmd, "la") || !strcmp(cmd, "ls"))
    {
        Tasks* tasks;
        read_tasks(FILENAME, &tasks);
        if (tasks->count == 0)
        {
            printf(YEL "You have nothing to do for now\n" RST);
            Tasks_destructor(tasks);
            return true;
        }
        if (!strcmp(cmd, "la"))
        {
            for (unsigned int i = 0; i < tasks->count; i++)
                Task_pretty(tasks->arr[i]);
        }
        else
        {
            for (unsigned int i = 0; i < tasks->count; i++)
                Task_print(tasks->arr[i]);
        }
        Tasks_destructor(tasks);
    }
    else if (!strcmp(cmd, "tick") || !strcmp(cmd, "ntick"))
    {
        if (argc < 3)
        {
            printf(RED "Argument 'id' missing " RST "-> todoit (n)tick <id>\n");
            return false;
        }
        if (!is_number(argv[2]))
        {
            printf(RED "Argument 'id' must be a null or positive number, '%s' given\n" RST, argv[2]);
            return false;
        }
        Tasks* tasks = NULL;
        read_tasks(FILENAME, &tasks);
        if (tasks->count == 0)
        {
            printf(YEL "You have nothing to do for now\n" RST);
            Tasks_destructor(tasks);
            return true;
        }
        for (unsigned int i = 0; i < tasks->count; i++)
        {
            if (tasks->arr[i]->id == atoi(argv[2]))
            {
                if (!strcmp(cmd, "tick") && !tasks->arr[i]->accomplished)
                {
                    Task_set_state(tasks->arr[i], true);
                    rewrite_tasks(FILENAME, tasks);
                    printf(GRN "Task #%d completed\n" RST, tasks->arr[i]->id);
                    Task_pretty(tasks->arr[i]);
                    Tasks_destructor(tasks);
                    return true;
                }
                else if (!strcmp(cmd, "tick") && tasks->arr[i]->accomplished)
                {
                    printf(RED "Task already completed\n" RST);
                }
                else if (!strcmp(cmd, "ntick") && tasks->arr[i]->accomplished)
                {
                    Task_set_state(tasks->arr[i], false);
                    rewrite_tasks(FILENAME, tasks);
                    printf(GRN "Task #%d uncompleted\n" RST, tasks->arr[i]->id);
                    Task_pretty(tasks->arr[i]);
                    Tasks_destructor(tasks);
                    return true;
                }
                else
                {
                    printf(RED "Task already uncompleted\n" RST);
                }
                Task_pretty(tasks->arr[i]);
                Tasks_destructor(tasks);
                return false;
            }
        }
        printf(RED "Task with id #%s not found\n" RST, argv[2]);
        Tasks_destructor(tasks);
        return false;
    }
    else if (!strcmp(cmd, "find"))
    {
        if (argc < 3)
        {
            printf(RED "Argument 'id' missing " RST "-> todoit find <id>\n");
            return false;
        }
        if (!is_number(argv[2]))
        {
            printf(RED "Argument 'id' must be a null or positive number, '%s' given\n" RST, argv[2]);
            return false;
        }
        Task* task = NULL;
        read_task(FILENAME, atoi(argv[2]), &task);
        if (task == NULL)
        {
            printf(RED "Task with id #%s not found\n" RST, argv[2]);
            return false;
        }
        Task_pretty(task);
        Task_destructor(task);
    }
    else if (!strcmp(cmd, "edit"))
    {
        if (argc < 5)
        {
            printf(RED "Some arguments are missing " RST "-> todoit edit <id> <field> <value>\n");
            return false;
        }
        if (!is_number(argv[2]))
        {
            printf(RED "Argument 'id' must be a null or positive number, '%s' given\n" RST, argv[2]);
            return false;
        }
        const char* FIELDS[] = { "text", "t", "end", "e", "priority", "p" };
        check_cmd_exists(argv[3], FIELDS, 6);
        Tasks* tasks = NULL;
        read_tasks(FILENAME, &tasks);
        if (tasks->count == 0)
        {
            printf(YEL "You have nothing to do for now\n" RST);
            Tasks_destructor(tasks);
            return true;
        }
        if (!strcmp(argv[3], "p") || !strcmp(argv[3], "priority"))
        {
            if (!check_priority(argv[4]))
            {
                printf(RED "Argument 'value' must be a character in [A-Z], '%s' given\n" RST, argv[4]);
                Tasks_destructor(tasks);
                return false;
            }
            for (unsigned int i = 0; i < tasks->count; i++)
            {
                if (tasks->arr[i]->id == atoi(argv[2]))
                {
                    tasks->arr[i]->priority = argv[4][0];
                    rewrite_tasks(FILENAME, tasks);
                    printf(GRN "Task #%d priority edited\n" RST, tasks->arr[i]->id);
                    Task_pretty(tasks->arr[i]);
                }
            }
        }
        else if (!strcmp(argv[3], "e") || !strcmp(argv[3], "end"))
        {
            if (!check_date(argv[4]))
            {
                printf(RED "Argument 'value' must be a valid date as dd-mm-yyyy, '%s' given\n" RST, argv[4]);
                Tasks_destructor(tasks);
                return false;   
            }
            for (unsigned int i = 0; i < tasks->count; i++)
            {
                if (tasks->arr[i]->id == atoi(argv[2]))
                {
                    Date_destructor(tasks->arr[i]->end);
                    tasks->arr[i]->end = Date_factory(argv[4]);
                    rewrite_tasks(FILENAME, tasks);
                    printf(GRN "Task #%d deadline edited\n" RST, tasks->arr[i]->id);
                    Task_pretty(tasks->arr[i]);
                }
            }
        }
        else
        {
            
        }
        Tasks_destructor(tasks);
    }
    else if (!strcmp(cmd, "rm"))
    {
        if (argc < 3)
        {
            printf(RED "Argument 'id' missing " RST "-> todoit rm <id>\n");
            return false;
        }
        if (!is_number(argv[2]))
        {
            printf(RED "Argument 'id' must be a null or positive number, '%s' given\n" RST, argv[2]);
            return false;
        }
        Tasks* tasks = NULL;
        read_tasks(FILENAME, &tasks);
        if (tasks->count == 0)
        {
            printf(YEL "You have nothing to do for now\n" RST);
            Tasks_destructor(tasks);
            return true;
        }
        for (unsigned int i = 0; i < tasks->count; i++)
        {
            if (tasks->arr[i]->id == atoi(argv[2]))
            {
                Tasks* new_tasks = Tasks_factory();
                Tasks_cpy_without(tasks, new_tasks, tasks->arr[i]->id);
                rewrite_tasks(FILENAME, new_tasks);
                printf(GRN "Task #%d removed\n" RST, tasks->arr[i]->id);
                Task_pretty(tasks->arr[i]);
                Tasks_destructor(new_tasks);
                Tasks_destructor(tasks);
                return true;
            }
        }
        printf(RED "Task with id #%s not found\n" RST, argv[2]);
        Tasks_destructor(tasks);
        return false;
    }
    return true;
}

int parse_cmd(int argc, char* argv[])
{
    const char* COMMANDS[] = { "h", "la", "ls", "add", "edit", "rm", "tick", "ntick", "find", "init" };
    int status = 0;
    if (argc > 1)
    {
        if (check_cmd_exists(argv[1], COMMANDS, 10))
        {
            if (!process_cmd(argc, argv)) status = 1;
        }
        else
        {
            status = 1;
        }
    }
    else
    {
        printf(YEL "Type 'h' for help\n" RST);
    }
    return status;
}
