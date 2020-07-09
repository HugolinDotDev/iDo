#include "../include/cmd.h"

void print_help()
{
    printf(YEL "Usage : " RST "ido COMMAND <...>\n\n"
                "<id>                             " GRN "Shortcut for find\n"
            RST "find <id>                        " GRN "Find a task with it's id\n"
            RST "la                               " GRN "Print the tasks with details\n"
            RST "ls                               " GRN "Print the tasks\n"
            RST "rm <id>                          " GRN "Delete a task with it's id\n"
            RST "tick <id>                        " GRN "Complete a task with it's id\n"
            RST "ntick <id>                       " GRN "Uncomplete a task with it's id\n"
            RST "edit/e <id> <" CYN "flag" RST "> <value>       " GRN "Edit a task, editable flags are below :\n"
            CYN "  -text/-t     " GRN "                    => task's text (max 200 characters, must not include ';')\n"
            CYN "  -priority/-p " GRN "                    => task's priority\n"
            CYN "  -end/e       " GRN "                    => task's deadline (date)\n");
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
    if (!strcmp(cmd, "h") || !strcmp(cmd, "help"))
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
    else if (!strcmp(cmd, "t") || !strcmp(cmd, "tick") || !strcmp(cmd, "nt") || !strcmp(cmd, "ntick"))
    {
        if (argc < 3)
        {
            printf(RED "Argument 'id' missing " RST "-> todoit (n)tick/(n)t <id>\n");
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
                if ((!strcmp(cmd, "t") || !strcmp(cmd, "tick")) && !tasks->arr[i]->accomplished)
                {
                    Task_set_state(tasks->arr[i], true);
                    rewrite_tasks(FILENAME, tasks);
                    printf(GRN "Task #%d completed\n" RST, tasks->arr[i]->id);
                    Task_pretty(tasks->arr[i]);
                    Tasks_destructor(tasks);
                    return true;
                }
                else if ((!strcmp(cmd, "t") || !strcmp(cmd, "tick")) && tasks->arr[i]->accomplished)
                {
                    printf(RED "Task already completed\n" RST);
                }
                else if ((!strcmp(cmd, "nt") || !strcmp(cmd, "ntick")) && tasks->arr[i]->accomplished)
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
    else if (!strcmp(cmd, "f") || !strcmp(cmd, "find"))
    {
        if (argc < 3)
        {
            printf(RED "Argument 'id' missing " RST "-> todoit find/f <id>\n");
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
    else if (!strcmp(cmd, "e") || !strcmp(cmd, "edit"))
    {
        if (argc < 5)
        {
            printf(RED "Some arguments are missing " RST "-> todoit edit/e <id> <flag> <value>\n");
            return false;
        }
        if (!is_number(argv[2]))
        {
            printf(RED "Argument 'id' must be a null or positive number, '%s' given\n" RST, argv[2]);
            return false;
        }
        const char* FIELDS[] = { "-text", "-t", "-end", "-e", "-priority", "-p" };
        if (!check_cmd_exists(argv[3], FIELDS, 6))
            return false;
        Tasks* tasks = NULL;
        read_tasks(FILENAME, &tasks);
        if (tasks->count == 0)
        {
            printf(YEL "You have nothing to do for now\n" RST);
            Tasks_destructor(tasks);
            return true;
        }
        if (!strcmp(argv[3], "-p") || !strcmp(argv[3], "-priority"))
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
        else if (!strcmp(argv[3], "-e") || !strcmp(argv[3], "-end"))
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
            if (!check_text(argc, argv))
            {
                printf(RED "Argument 'value' must be a valid string\n" RST);
                Tasks_destructor(tasks);
                return false;
            }
            for (unsigned int i = 0; i < tasks->count; i++)
            {
                if (tasks->arr[i]->id == atoi(argv[2]))
                {
                    create_text(argc, argv, tasks->arr[i]->text);
                    rewrite_tasks(FILENAME, tasks);
                    printf(GRN "Task #%d text edited\n" RST, tasks->arr[i]->id);
                    Task_pretty(tasks->arr[i]);
                }
            }
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
    const char* COMMANDS[] = { "h", "help", "la", "ls", "add", "a", "edit", "e", "rm", "tick", "t", "ntick", "nt", "find", "f", "init" };
    int status = 0;
    if (argc > 1)
    {
        if (is_number(argv[1]))
        {
            Task* task = NULL;
            read_task(FILENAME, atoi(argv[1]), &task);
            if (task == NULL)
            {
                printf(RED "Task with id #%s not found\n" RST, argv[1]);
                status = 1;
            }
            else
            {
                Task_pretty(task);
                Task_destructor(task);
            }
        }
        else if (check_cmd_exists(argv[1], COMMANDS, 16))
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
        printf(CYN "iDo, easy todo list,\nwritten in C by Hugolin MARIETTE.\n\n" RST
               YEL "Type 'h' for help\n" RST);
    }
    return status;
}
