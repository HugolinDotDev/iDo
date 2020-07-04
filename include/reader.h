#pragma once

#include <stdio.h>

typedef struct Reader {
    FILE* fp;
    char* line;
    size_t len;
    ssize_t read;
} Reader;

extern Reader* Reader_factory(const char* filename);
extern void Reader_destructor(Reader* reader);
