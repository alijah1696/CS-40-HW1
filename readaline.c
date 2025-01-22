#include <stdio.h>
#include <stdlib.h>
#include "readaline.h"

size_t readaline(FILE *inputfd, char **datapp)
{
    size_t count = 0;
    int ch;
    while ((ch = fgetc(inputfd)) != EOF) { 
        


        *datapp[count] = ch;
    }

    if (ferror(inputfd)) {
        perror("Error reading from file");
        fclose(inputfd);
        return EXIT_FAILURE;
    }

    fclose(inputfd);

    return count;
}