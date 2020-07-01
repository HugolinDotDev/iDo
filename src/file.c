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
        char* text = malloc(MAX_TEXT);
        char* creation_str = malloc(MAX_TEXT);
        char* end_str = malloc(MAX_TEXT);

        char line_copy[300];
        strcpy(line_copy, line);

        char* tmp = strtok(line_copy, ";");
        id = atoi(tmp);
        tmp = strtok(NULL, ";");
        priority = tmp;
        tmp = strtok(NULL, ";");
        text = tmp;
        tmp = strtok(NULL, ";");
        creation_str = tmp;
        tmp = strtok(NULL, ";");
        end_str = tmp;

        Task* task = Task_factory(id, accomplished, priority, text, creation_str, end_str);
        tasks[i] = task;

        free(text);
        free(creation_str);
        free(end_str);
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
