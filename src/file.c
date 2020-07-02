#include "../include/file.h"

bool str_to_bool(const char* value)
{
    if (!strcmp(value, "t"))
        return true;
    return false;
}

Task* read_task(const char* filename, unsigned int id)
{

}

void read_tasks(const char* filename, Tasks* tasks)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename, "r");
    fatal(fp != NULL, "fp is a null pointer", 1);

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        unsigned int id;
        bool accomplished;
        char priority;
        char* text;
        char* creation_str;
        char* end_str;

        char* tmp = strtok(line, ";");
        id = atoi(tmp);
        tmp = strtok(NULL, ";");
        accomplished = str_to_bool(tmp);
        tmp = strtok(NULL, ";");
        priority = *tmp;
        text = strtok(NULL, ";");
        creation_str = strtok(NULL, ";");
        end_str = strtok(NULL, ";");
        end_str[10] = '\0';

        Task* task = Task_factory(id, accomplished, priority, text, creation_str, end_str);
        Tasks_add(tasks, task, i);

        i++;
    }
    free(line);
    fclose(fp);
}

int write_task(const char* filename, const char* task)
{

}

int rm_task(const char* filename, unsigned int id)
{

}
