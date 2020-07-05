#include "../include/cmd.h"

const char* COMMANDS[] = { "h", "la", "ls", "add", "edit", "rm", "tick", "ntick", "find", "findby" };

bool is_number(const char* string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] < 48 || string[i] > 57)
            return false;
    }
    return true;
}

void print_help()
{
    printf(YEL "Usage : " RST "todoit COMMAND [OPTIONS]\n\n"
            GRN "la         " RST "Print the tasks with details\n"
            GRN "ls         " RST "Print the tasks\n"
            GRN "add        " RST "Add a task\n"
            GRN "edit       " RST "Edit a task\n"
            GRN "rm         " RST "Delete a task\n"
            GRN "check      " RST "Complete a task\n"
            GRN "uncheck    " RST "Uncomplete a task\n"
            GRN "find       " RST "Find a task by its id\n"
            GRN "findby     " RST "Find by a filter\n");
}

bool check_cmd_exists(const char* cmd)
{
    unsigned int len = sizeof(COMMANDS) / sizeof(COMMANDS[0]);
    for (unsigned int i = 0; i < len; i++)
    {
        if (!strcmp(cmd, COMMANDS[i]))
        {
            return true;
        }
    }
    printf(RED "Command '%s' does not exist\n" RST, cmd);
    return false;
}

bool process_cmd(int argc, const char* argv[])
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
        read_tasks("tasks.csv", &tasks);
        if (tasks->count == 0)
        {
            printf(YEL "You have nothing to do for now\n" RST);
            return true;
        }
        if (!strcmp(cmd, "la"))
        {
            for (int i = 0; i < tasks->count; i++)
                Task_pretty(tasks->arr[i]);
        }
        else
        {
            for (int i = 0; i < tasks->count; i++)
                Task_print(tasks->arr[i]);
        }
        for (int i = 0; i < tasks->count; i++)
            Task_destructor(tasks->arr[i]);
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
            printf(RED "Argument 'id' must be a null or positive number, '%s' given\n", argv[2]);
            return false;
        }
        Task* task = NULL;
        read_task("tasks.csv", atoi(argv[2]), task);
        if (task == NULL)
        {
            printf(RED "Task with id #%s not found\n" RST, argv[2]);
            return false;
        }
        set_state_task("tasks.csv", argv[1], task);
        Task_pretty(task);
        Task_destructor(task);
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
            printf(RED "Argument 'id' must be a null or positive number, '%s' given\n", argv[2]);
            return false;
        }
        Task* task = NULL;
        read_task("tasks.csv", atoi(argv[2]), &task);
        if (task == NULL)
        {
            printf(RED "Task with id #%s not found\n" RST, argv[2]);
            return false;
        }
        Task_pretty(task);
        Task_destructor(task);
    }
    return true;
}

int parse_cmd(int argc, const char* argv[])
{
    int status = 0;
    if (argc > 1)
    {
        if (check_cmd_exists(argv[1]))
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
        printf(YEL "Type 'h' for help\n");
    }
    return status;
}
