#include <stdio.h>
#include <stdlib.h>
#include "readaline.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 1001

size_t readaline(FILE *inputfd, char **datapp) {
    if (inputfd == NULL || datapp == NULL) {

        fprintf(stderr, "readaline: invalid argument\n");
        exit(EXIT_FAILURE);
    }

    size_t capacity = INITIAL_CAPACITY;
    unsigned char *buffer = malloc(capacity);

    if (!buffer) {
        fprintf(stderr, "readaline: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    size_t length = 0;
    int ch;

    while ( (ch = fgetc(inputfd)) != EOF ) {

        if (length > 1000)
        {
            fprintf(stderr, "readaline: input line too long\n");
            exit(EXIT_FAILURE);
        }
    
        buffer[length++] = (unsigned char)ch;

        if (ch == '\n') {
            break;
        }

        // if (length >= capacity) {
        //     size_t new_capacity = capacity * 2;
        //     unsigned char *temp = realloc(buffer, new_capacity);
        //     if (!temp) {
        //         free(buffer);
        //         fprintf(stderr, "readaline: memory (re)allocation failed\n");
        //         exit(EXIT_FAILURE);
        //     }
        //     buffer = temp;
        //     capacity = new_capacity;
        // }
    }

    if (length == 0) 
    {
        free(buffer);
        *datapp = NULL;
        return 0;
    }


    if (length >= capacity) {
        unsigned char *temp = realloc(buffer, capacity + 1);
        if (!temp) {
            free(buffer);
            fprintf(stderr, "readaline: memory (re)allocation failed\n");
            exit(EXIT_FAILURE);
        }
        buffer = temp;
        capacity++;
    }
    buffer[length] = '\0';

    *datapp = (char *)buffer;
    return length;
}
