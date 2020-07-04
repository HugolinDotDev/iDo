#include "../include/reader.h"

Reader* Reader_factory(const char* filename)
{
    Reader* reader = malloc(sizeof(Reader));
    reader->line = NULL;
    reader->len = 0;
    reader->fp = fopen(filename, "r");
    fatal(reader->fp != NULL, "fp is a null pointer", 1);
    return reader;
}

void Reader_destructor(Reader* reader)
{
    free(reader->line);
    fclose(reader->fp);
    free(reader);
}
