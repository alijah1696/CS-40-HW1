#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void read_num_char(char* line, /*matrix of numbers, list of non-nums*/)
{
    while ((ch = fgetc(line)) != '\n')
    {
        if (isdigit(ch))
            //nums[i][j] = ch;
        else
            //nonnums[i][j] = ch;
    }
}



tuple check_equal_lines(/*list of non-nums*/)
{
    for (int i = 0; i</*len(list) - 1*/; i++)
    {
        for (int j = 1; j < /*len(list)*/; j++)
        {
            if (list[i] == list[j])
                return (i, j);
        }
    }
    return (-1, -1);
}