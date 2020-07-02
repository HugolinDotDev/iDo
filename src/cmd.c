#include "../include/cmd.h"

const char* COMMANDS[] = { "h", "la", "ls", "add", "edit", "rm", "check", "uncheck", "find", "findby" };

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
    else if (!strcmp(cmd, "la"))
    {
        Task* tasks[MAX_LINES];
        read_tasks("tasks.csv", tasks);
        // unsigned int len = sizeof(tasks) / sizeof(tasks[0]);
        for (int i = 0; i < 2; i++)
        {
            Task_print(tasks[i]);
            Task_destructor(tasks[i]);
        }
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
