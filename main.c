#include <stdio.h>
#include <stdlib.h>
#include "readaline.h"
//#include "list.h"

int main(int argc, char *argv[])
{
    
    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        char* line = NULL;
        // int ok = 0;

        while (readaline(file, &line) > 0)
        {
            printf("%s\n", line);
            free(line);
        }
        fclose(file);
    }
}
