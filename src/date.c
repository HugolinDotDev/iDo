#include "../include/date.h"

Date* Date_factory(const char* date_str)
{
    Date* date = malloc(sizeof(Date));
    fatal(date != NULL, "date is a null pointer", 1);
    strcpy(date->toString, date_str);

    char string[DATE_SIZE];
    strcpy(string, date_str);
    char* tmp = strtok(string, "/");
    date->day = atoi(tmp);
    tmp = strtok(NULL, "/");
    date->month = atoi(tmp);
    tmp = strtok(NULL, "/");
    date->year = atoi(tmp);

    return date;
}

void Date_destructor(Date* date)
{
    free(date);
}

void Date_debug(Date* date)
{
    printf("%d %d %d\n%s\n", date->day, date->month, date->year, date->toString);
}
