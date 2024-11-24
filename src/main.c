#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <strings.h>

#include "global.h"

bool show_lines = false;
bool separate   = false;

int read_file(const char *file_path)
{
    FILE *fptr = fopen(file_path, "r");
    if (!fptr)
    {
        fprintf(stderr, "ERROR: Cannot open file: \"%s\": %s\n", file_path, strerror(errno));
        return 1;
    }

    char ch;
    char *line = malloc(sizeof(char) * 10);
    if (!line)
    {
        fclose(fptr);
        fprintf(stderr, "ERROR: %s", strerror(errno));
        return 1;   
    }
    size_t line_sz = 10;
    size_t index = 0;
    unsigned int line_count = 0;
    
    while ((ch = getc(fptr)) != EOF)
    {
        if (index >= line_sz)
        {
            line_sz *= 2;
            line = realloc(line, sizeof(char) * line_sz);
            if (!line)
            {
                fprintf(stderr, "ERROR: CANNOT REALLOCATE STRING. %s\n", strerror(errno));
                fclose(fptr);
                return 1;
            }
        }

        if (ch == '\n')
        {
            line_count++;

            line[index] = '\0';
            
            if (show_lines)
                printf("%4d ", line_count);

            printf("%s\n", line);
            memset(line, 0, sizeof(char) * index);
            index = 0;
            continue;
        }

        line[index] = ch;
        index++;
    }

    return 0;
}

int main(int argc, const char **argv)
{
    binary = argv[0];

    if (argc < 2)
    {
        catt_help();
        return 1;
    }

    int start = 1;

    for (int i = start; i < argc; i++)
    {
        const char *arg = argv[i];
        
        if (strcmp(arg, "-l") == 0)
        {
            show_lines = true;
            start++;
        }
        else if (strcmp(arg, "-s") == 0)
        {
            separate = true;
            start++;
        }
        else if (strcmp(arg, "-v") == 0)
        {
            catt_version();
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = start; i < argc; i++)
    {
        if (separate)
            printf("------------ \"%s\" ------------\n", argv[i]);
        
        if (read_file(argv[i]) != 0)
        {
            fprintf(stderr, "ERROR: Cannot read file.\n");
            exit(EXIT_FAILURE);
        }
   }

    return 0;
}
