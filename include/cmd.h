#pragma once

#include "../include/file.h"

#ifndef FILENAME
    #define FILENAME ".ido/tasks.csv"
#endif

extern int parse_cmd(int argc, char* argv[]);
