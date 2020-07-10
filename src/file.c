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

typedef struct Datas {
    File* stats;
    File* tasks;
} Datas;

Datas* Datas_factory(const char* stats_path, const char* stats_mode, const char* tasks_path, const char* tasks_mode)
{
    Datas* datas = malloc(sizeof(Datas));
    datas->stats = File_factory(stats_path, stats_mode);
    datas->tasks = File_factory(tasks_path, tasks_mode);
    return datas;
}

void Datas_destructor(Datas* datas)
{
    File_destructor(datas->stats);
    File_destructor(datas->tasks);
    free(datas);
}

bool str_to_bool(const char* value)
{
    if (!strcmp(value, "t"))
        return true;
    return false;
}

char bool_to_char(bool value)
{
    if (value)
        return 't';
    return 'f';
}

ssize_t read_task(const char* filename, unsigned int id, Task** task)
{
    File* file = File_factory(filename, "r");
    ssize_t read = 0;
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
            File_destructor(file);
            return read;
        }
        read += file->read;
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

void rewrite_tasks(const char* filename, Tasks* tasks)
{
    File* file = File_factory(filename, "w");
    for (unsigned int i = 0; i < tasks->count; i++)
    {
        fprintf(file->fp, "%d;%c;%c;%s;%s;%s\n", tasks->arr[i]->id, bool_to_char(tasks->arr[i]->accomplished),
                tasks->arr[i]->priority, tasks->arr[i]->text, tasks->arr[i]->creation->toString, tasks->arr[i]->end->toString);
    }
    File_destructor(file);
}

bool init_ido()
{
    struct stat s = { 0 };
    if (stat(".ido", &s) == -1)
    {
        mkdir(".ido", 0700);
        File* tasks = File_factory(".ido/tasks.csv", "w");
        File_destructor(tasks);
        File* config = File_factory(".ido/stats", "w");
        fprintf(config->fp, "id 0\ntasks 0\ntick 0\nntick 0\n");
        File_destructor(config);
        return true;
    }
    return false;
}
