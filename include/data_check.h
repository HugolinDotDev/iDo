#pragma once

#include "../include/date.h"

#ifndef MAX_TEXT
    #define MAX_TEXT 201
#endif

extern bool is_number(const char* string);
extern bool is_valid_text(const char* text);
extern bool check_priority(const char* priority);
extern bool check_date(const char* date);
extern void create_text(int argc, char* argv[], char* buffer);
extern bool check_text(int argc, char* argv[]);
