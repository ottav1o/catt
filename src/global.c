#include "global.h"

#include <stdio.h>

const char *binary = NULL;

void catt_help(void)
{
    if (!binary)
        binary = "catt";

    printf("\"%s\" - USAGE\n", binary);
    puts("Concatenate FILEs to STDOUT.");
    puts("-l : Show lines");
    puts("-s : Separate files with \"------\"");
    puts("-v : Show version.");
    puts("-----------------------------------");
}

void catt_version(void)
{
    printf("catt version %s - (C) ottav1o, 2024.\n", VERSION);
}
