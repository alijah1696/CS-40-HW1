#include <stdio.h>
#include <stdlib.h>
#include "readaline.h"
#include "list.h"


int main(int argc, char *argv[])
{


    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        char* line;
        int ok = 0;

        while (readaline(&file, &*line) > 0)
        {
            if (ok == 0)
            {
                read_num_char(line, &matrix numbers, &list nonnums)
                if (check_equal_lines != (-1, -1))
                {
                    //delete all lines that are not identical
                    ok = 1;
                } 
            }
            else
            {
                //just check if the nonnums are equal to the verified line. If they are not, then do not append the numbers to the matrix

            }
            
        }
        
    }
}