#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

void read_num_char(const char *line, List_T *matrix_nums, List_T *list_chars) {
    List_T row = NULL;

    size_t capacity = 1001;
    size_t size = 0;
    char *line_chars = malloc(capacity);

    if (!line_chars) {
        perror("Failed to allocate memory for line_chars");
        exit(1);
    }

    char ch;
    while ((ch = *line++) != '\n') 
    {
        if (isdigit(ch)) {
            char *num = malloc(sizeof(char));
            if (!num) {
                perror("Failed to allocate memory for num");
                exit(1);
            }
            *num = ch;
            row = List_push(row, num);
        } 
        else 
        {
            line_chars[size++] = ch;
        }
    } 

    line_chars[size] = '\0';

    *matrix_nums = List_push(*matrix_nums, List_reverse(row));
    *list_chars = List_push(*list_chars, line_chars);
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
