#include <stdio.h>
#include <stdlib.h>
#include "readaline.h"

size_t readaline(FILE *inputfd, char **datapp)
{
    if (inputfd == NULL || datapp == NULL) {
        fprintf(stderr, "Runtime error\n");
        exit(1);
    }

    size_t count = 0;
    size_t capacity = 1001;
    char ch;
    char *buffer = malloc(capacity);

    while ((ch = fgetc(inputfd)) != EOF) { 

        if (count == 1001)
        {
            buffer[++count] = '\n';
            return count;
        }
           

        buffer[count] = ch;
        count++;

        if (ch == '\n')
            break;
    }

    if (ferror(inputfd)) {
        fprintf(stderr, "Error reading from the file\n");
        fclose(inputfd);
        exit(1);
    }    

    if (count > 0)
    {
        buffer[count + 1] = '\0';

        *datapp = buffer;

        return count;
    }
    else
    {
        free(buffer);
        return 0;
    }
}

char* increase_cap (char* buffer, size_t capacity)
{
    char* new_buff = realloc(buffer, capacity);

    if (new_buffer == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free(buffer);
        exit(1);
    }

    return new_buff;
}

