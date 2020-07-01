#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/fatal.h"

#ifndef DATE_SIZE
    #define DATE_SIZE 11
#endif

typedef struct Date {
    unsigned int day;
    unsigned int month;
    unsigned int year;
    char toString[DATE_SIZE];
} Date;

extern Date* Date_factory(const char* date_str);
extern void Date_destructor(Date* date);
extern void Date_debug(Date* date);
