#include <stdio.h>
#include <stdlib.h>

#include "restoration.h"
#include "readaline.h"
#include "seq,h"

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        FILE *file = fopen(argv[1], "r");
        
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }

        char* line = NULL;
        Seq_T matrix = Sequence_new(150);
        Seq_T atom_sequence = Seq_new(0);
        int ok = 0;
        int width = 0;
        int heigth = 0;
        int false_lines = 0;
        int total_corrupted_lines = 0;

        while (readaline(file, &line) > 0)
        {    
            printf(line);
        }
    }
    else
        printf(stderr, "Wrong number of arguments provided");
}

// {
    
//     if (argc == 2)
//     {
//         FILE *file = fopen(argv[1], "r");
        
//         if (file == NULL) {
//             perror("Error opening file");
//             return 1;
//         }

//         char* line = NULL;
//         Seq_T matrix = Sequence_new(150);
//         Seq_T atom_sequence = Seq_new(0);
//         int ok = 0;
//         int width = 0;
//         int heigth = 0;
//         int false_lines = 0;
//         int total_corrupted_lines = 0;

//         while (readaline(file, &line) > 0)
//         {
//             total_corrupted_lines++;
//             if (ok == 0)
//             {
//                 int index = diff_nums_chars1(line, &matrix, &atom_sequence);
//                 if (index != -1)
//                 {
//                     const char* correct_atom = Seq_get(atom_sequence, index);
//                     int size_matrix = Seq_length(matrix);
//                     false_lines = Seq_length(matrix) - 2;
//                     matrix = correct_matrix(matrix, size_matrix, index);
//                     ok = 1;
//                 }
//             }
//             else
//             {
//                 false_lines+= diff_nums_chars2(line, correct_atom, matrix, atom_sequence, width);
//             }

//             free(line);
//         }

//         assert(total_corrupted_lines - Seq_length(matrix) == failed_lines);
//         fclose(file);
//         create_P2_file(matrix);
//     }
// }