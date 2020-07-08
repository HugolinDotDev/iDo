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
