#include "../include/file.h"

const char* read_task(const char* filename, unsigned int id)
{

}

void read_tasks(const char* filename, Task** tasks)
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
        bool accomplished = false;
        char priority;
        char* text;
        char* creation_str;
        char* end_str;

        char* tmp = strtok(line, ";");
        id = atoi(tmp);
        tmp = strtok(NULL, ";");
        // Ici sera le accomplished
        tmp = strtok(NULL, ";");
        priority = tmp;
        text = strtok(NULL, ";");
        creation_str = strtok(NULL, ";");
        end_str = strtok(NULL, ";");
        end_str[10] = '\0';

        Task* task = Task_factory(id, accomplished, priority, text, creation_str, end_str);
        tasks[i] = task;
        i++;
    }
    free(line);
    fclose(fp);
}

int write_task(const char* filename, const char* task)
{

}

int delete_task(const char* filename, unsigned int id)
{

}
