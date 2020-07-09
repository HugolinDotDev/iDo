#include "../include/data_check.h"

bool is_number(const char* string)
{
    for (unsigned long i = 0; i < strlen(string); i++)
    {
        if (string[i] < 48 || string[i] > 57)
            return false;
    }
    return true;
}

bool is_valid_text(const char* text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] < 32 || text[i] == 59 || text[i] == 127)
            return false;
    }
    return true;
}

bool check_priority(const char* priority)
{
    if (strlen(priority) == 1 && priority[0] >= 40 && priority[0] <= 90)
    {
        return true;
    }
    return false;
}

bool check_date(const char* date_str)
{
    if (strlen(date_str) == 10 && date_str[2] == '-' && date_str[5] == '-')
    {
        Date* date = Date_factory(date_str);
        if (date != NULL && Date_valid(date))
        {
            Date_destructor(date);
            return true;
        }
    }
    return false;
}

void create_text(int argc, char* argv[], char* buffer)
{
    buffer[0] = '\0';
    for (int i = 4; i < argc; i++)
    {
        if (i != (argc - 1))
        {
            strcat(buffer, argv[i]);
            strcat(buffer, " ");
        }
        else
        {
            strcat(buffer, argv[i]);
            strcat(buffer, "\0");
        }
    }
}

bool check_text(int argc, char* argv[])
{
    char buffer[MAX_TEXT] = "";
    create_text(argc, argv, buffer);
    if (!is_valid_text(buffer))
        return false;
    return true;
}
