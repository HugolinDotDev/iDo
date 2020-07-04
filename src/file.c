#include "../include/file.h"

bool str_to_bool(const char* value)
{
    if (!strcmp(value, "t"))
        return true;
    return false;
}

Task* read_task(const char* filename, unsigned int id)
{
    Reader* reader = Reader_factory(filename);
    Task* task = NULL;
    while ((reader->read = getline(&(reader->line), &(reader->len), reader->fp)) != -1)
    {
        char* tmp = strtok(reader->line, ";");
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

            task = Task_factory(fid, accomplished, priority, text, creation_str, end_str);
            break;
        }
    }
    Reader_destructor(reader);
    return task;
}

void read_tasks(const char* filename, Tasks* tasks)
{
    Reader* reader = Reader_factory(filename);
    while ((reader->read = getline(&(reader->line), &(reader->len), reader->fp)) != -1)
    {
        unsigned int id;
        bool accomplished;
        char priority;
        char* text;
        char* creation_str;
        char* end_str;

        char* tmp = strtok(reader->line, ";");
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
        Tasks_add(tasks, task);
    }
    Reader_destructor(reader);
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
