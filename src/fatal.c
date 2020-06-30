#include "../include/fatal.h"

void fatal(int assert, const char message[], int status)
{
    if (!assert)
    {
        fprintf(stderr, "Error: %s\nCode: %d\n", message, status);
        exit(status);
    }
}