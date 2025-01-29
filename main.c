#include <stdio.h>
#include <stdlib.h>

#include "restoration.h"
#include "readaline.h"
#include "seq.h"
#include "atom.h"
#include "unit_tests.h"

// // The lines are not supposed to end with \0 because then len is going to be 1 higher 



// int main()
// {
//     test_separate_extended();
//     return 0;
// }

int main(int argc, char *argv[]) 
{
    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "rb");

        if (!file) {
            perror("fopen");
            return 1;
        }
        const char* correct_atom = NULL;

        char *line = NULL;
        size_t len;
        Seq_T matrix = Seq_new(0);
        Seq_T atom_sequence = Seq_new(0);
        int ok = 0;
        int width = 0;
        // int heigth = 0;
        int false_lines = 0;
        int total_corrupted_lines = 0;

        while ((len = readaline(file, &line)) > 0) 
        {
            printf("\n");
            printf("len: %zu", len);
            printf("\n");
            printf("Current line\n");
            printf("%s\n", line);
            total_corrupted_lines++;
            if (ok == 0)
            {
                int index = diff_nums_chars1(line, matrix, atom_sequence);
                if (index != -1)
                {
                    printf("The index is: ");
                    printf("%d", index);
                    printf("\n");

                    correct_atom = (char*) Seq_get(atom_sequence, index);

                    int size_matrix = Seq_length(matrix);
                    false_lines = Seq_length(matrix) - 2;

                    matrix = correct_matrix(matrix, size_matrix, index);

                    printf("Seq_length(Seq_get(matrix, 0)): %d\n", Seq_length(Seq_get(matrix, 0)));
                    assert(Seq_length(Seq_get(matrix, 0)) == Seq_length(Seq_get(matrix, 1)));
                    width = Seq_length(Seq_get(matrix, 0));

                    printf("%s", "The matrix after discovering the first correct 2 indices\n");
                    printing_matrix(matrix);
                    printf("\n");

                    ok = 1;
                }
                else
                {
                    printf("Have not discovered the correct 2 indices yet\n");
                }
            }
            else
            {
                false_lines+= diff_nums_chars2(line, correct_atom, matrix, atom_sequence, width);
            }

            free(line);
        }

        printf("%d", total_corrupted_lines);
        printf("\n");
        printf("%d", Seq_length(matrix));
        printf("\n");
        printf("%d", false_lines);
        printf("\n");

        assert(total_corrupted_lines - Seq_length(matrix) == false_lines);
        fclose(file);

        printf("\n");
        printf("%s", "Final matrix\n");
        printing_matrix(matrix);

        for (size_t i = 0; i < (size_t)Seq_length(matrix); i++){
            Seq_T row = (Seq_T)Seq_get(matrix, i);
            Seq_free(&row);
        }

        Seq_free(&matrix);
        Seq_free(&atom_sequence);


        return 0;
    }
    else
    {
        printf("%d", argc);
        return 1;
    }
}


