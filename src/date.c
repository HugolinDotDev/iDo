#include "../include/date.h"

Date* Date_factory(const char* date_str)
{
    Date* date = malloc(sizeof(Date));
    fatal(date != NULL, "date is a null pointer", 1);
    strcpy(date->toString, date_str);
    char string[DATE_SIZE];
    strcpy(string, date_str);
    char* day = NULL;
    char* month = NULL;
    char* year = NULL;
    day = strtok(string, "-");
    month = strtok(NULL, "-");
    year = strtok(NULL, "-");
    if (!is_number(day) && !is_number(month) && !is_number(year))
    {
        Date_destructor(date);
        return NULL;
    }
    date->day = atoi(day);
    date->month = atoi(month);
    date->year = atoi(year);
    return date;
}

bool is_leap(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)); 
}

bool Date_valid(Date* date)
{
    if (date->year < MIN_YEAR || date->year > MAX_YEAR)
        return false;
    if (date->month < 1 || date->month > 12)
        return false;
    if (date->day < 1 || date->day > 31)
        return false;
    if (date->month == 2)
    {
        if (is_leap(date->year))
        {
            if (date->day <= 29)
                return true;
            return false;
        }
        else
        {
            if (date->day <= 28)
                return true;
            return false;
        }
    }
    if (date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11)
    {
        if (date->day <= 30)
            return true;
        return false;
    }
    return true;
}

void Date_destructor(Date* date)
{
    free(date);
}
