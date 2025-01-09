#include "common.h"

bool check_file_extension(char *file, char *ext)
{
    const char *last_point = strrchr(file, '.');

    if (!last_point || last_point == file)
        return (false);
    return (strcmp(last_point + 1, ext) == 0);
}

void terminate(char *message)
{
    printf("ERROR: %s\n", message);
    exit(0);
}
