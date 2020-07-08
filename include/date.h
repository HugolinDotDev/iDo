#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/fatal.h"
#include "../include/data_check.h"

#ifndef DATE_SIZE
    #define DATE_SIZE 11
#endif
#ifndef MIN_YEAR
    #define MIN_YEAR 1800
#endif
#ifndef MAX_YEAR
    #define MAX_YEAR 9999
#endif

typedef struct Date {
    int day;
    int month;
    int year;
    char toString[DATE_SIZE];
} Date;

extern Date* Date_factory(const char* date_str);
extern bool Date_valid(Date* date);
extern void Date_destructor(Date* date);
