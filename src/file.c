#include "../include/file.h"

typedef struct File {
    FILE* fp;
    char mode[3];
    char* line;
    size_t len;
    ssize_t read;
} File;

File* File_factory(const char* filename, const char* mode)
{
    File* file = malloc(sizeof(File));
    file->line = NULL;
    file->len = 0;
    file->fp = fopen(filename, mode);
    fatal(file->fp != NULL, "fp is a null pointer", 1);
    return file;
}

void File_destructor(File* file)
{
    if (file->line != NULL)
        free(file->line);
    fclose(file->fp);
    free(file);
}

bool str_to_bool(const char* value)
{
    if (!strcmp(value, "t"))
        return true;
    return false;
}

ssize_t read_task(const char* filename, unsigned int id, Task** task)
{
    File* file = File_factory(filename, "r");
    while ((file->read = getline(&(file->line), &(file->len), file->fp)) != -1)
    {
        char* tmp = strtok(file->line, ";");
        unsigned int fid = atoi(tmp);
        if (id == fid)
        {
            bool accomplished;
            char priority;
            char* text;
            char* creation_str;
            char* end_str;
            
            tmp = strtok(NULL, ";");
            accomplished = str_to_bool(tmp);
            tmp = strtok(NULL, ";");
            priority = *tmp;
            text = strtok(NULL, ";");
            creation_str = strtok(NULL, ";");
            end_str = strtok(NULL, ";");
            end_str[10] = '\0';

            Task* tmp_task = Task_factory(fid, accomplished, priority, text, creation_str, end_str);
            *task = tmp_task;
            ssize_t read = file->read;
            File_destructor(file);
            return read;
        }
    }
    File_destructor(file);
    return -1;
}

void read_tasks(const char* filename, Tasks** tasks)
{
    File* file = File_factory(filename, "r");
    Tasks* tmp_tasks = Tasks_factory();
    while ((file->read = getline(&(file->line), &(file->len), file->fp)) != -1)
    {
        unsigned int id;
        bool accomplished;
        char priority;
        char* text;
        char* creation_str;
        char* end_str;

        char* tmp = strtok(file->line, ";");
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
        Tasks_add(tmp_tasks, task);
    }
    *tasks = tmp_tasks;
    File_destructor(file);
}

bool write_task(const char* filename, const char* task)
{

}

bool set_state_task(const char* filename, const char* command, Task* task)
{

}

bool rm_task(const char* filename, unsigned int id)
{

}
