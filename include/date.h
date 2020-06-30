#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/fatal.h"

#ifndef DATE_SIZE
    #define DATE_SIZE 11
#endif

typedef struct {
    int day;
    int month;
    int year;
    char toString[DATE_SIZE];
} Date;

extern Date* Date_factory(char * date_str);
extern void Date_destructor(Date* date);
extern void Date_debug(Date* date);
