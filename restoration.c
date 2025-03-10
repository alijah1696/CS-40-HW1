#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "atom.h"
#include "seq.h"
#include "restoration.h"


/*
 * name:      diff_nums_chars1(const char *line, Seq_T matrix, 
              Seq_T atom_sequence) (short for "differentiate between numbers and
              other characters version 1")
 * purpose:   using a helper function called separate, it differentiates
              between numbers and injected characters. The numbers are stored 
              inside a sequence called newRow, while the non-digit characters
              are stored using atoms. Atoms were used because their 
              implementation allows for easy comparrison between them, making 
              them ideal to detect equalities between injected sequences.
 * arguments: the line of text, a sequence of sequences of pointers to integers
              (converted to binary for the final p5 file), and a sequence of 
              atoms
 * returns:   -1 if it did not find any 2 equal atoms in atom_sequence or the 
 *            index at which the an identical atoms was found (chechk the 
 *            implementation of check_atoms for more details)
 * Author: Darius-Stefan Iavorschi
 */
int diff_nums_chars1(const char *line, Seq_T matrix, Seq_T atom_sequence)
{
    assert(line != NULL);

    int capacity = 1001;
    Seq_T newRow = Seq_new(capacity);
    char* atom_val = malloc(capacity);

    if (!atom_val) {
        perror("Failed to allocate memory for atom_val");
        exit(1);
    }

    int size_atom = separate(line, newRow, atom_val);

    // printf("The value of atom_val is: %s\n", atom_val);

    Seq_addhi(matrix, newRow);

    const char *atom = Atom_new(atom_val, size_atom);

    // printf("The value of atom is: %s\n", atom);

    Seq_addhi(atom_sequence, (void *)atom);

    free(atom_val);

    return check_atoms(atom_sequence, atom);
}


/*
 * name:      diff_nums_chars2(const char* line, const char* correct_atom, Seq_T matrix, 
                                                Seq_T atom_sequence, int width) (short for "differentiate between numbers and
              other characters version 2")
 * purpose:   using a helper function called separate, it differentiates
              between numbers and injected characters. The difference between this function and diff_nums_chars1 is that 
 * arguments: the line of text, a sequence of sequences of pointers to integers
              (converted to binary for the final p5 file), and a sequence of 
              atoms
 * returns:   -1 if it did not find any 2 equal atoms in atom_sequence or the 
 *            index at which the an identical atoms was found (chechk the 
 *            implementation of check_atoms for more details)
 * Author: Darius-Stefan Iavorschi
 */
int diff_nums_chars2(const char* line, const char* correct_atom, Seq_T matrix, 
                                                Seq_T atom_sequence, int width)
{
    assert(line != NULL);
    assert(correct_atom != NULL);

    int capacity = 1001;
    Seq_T newRow = Seq_new(capacity);
    char* atom_val = malloc(capacity);
    int fl = 0;


    if (!atom_val) {
        perror("Failed to allocate memory for atom_val");
        exit(1);
    }

    // Create a new function to only check the atom == correct_atom statement
    int size_atom = separate(line, newRow, atom_val);

    const char *atom = Atom_new(atom_val, size_atom);

    if (atom == correct_atom)
    {
        // printf("Printing Seq_length(newRow): %d\n", Seq_length(newRow));
        // printf("The width is: %d\n", width);

        assert(Seq_length(newRow) == width);

        Seq_addhi(atom_sequence, (void *) atom);
        Seq_addhi(matrix, newRow);
    }
    else
    {
        int length = Seq_length(newRow);
        for (int i = 0; i < length; i++) {
            free(Seq_get(newRow, i)); // each is an int*, so free it
        }
        Seq_free(&newRow);
        fl++;
    }
        

    free(atom_val);

    return fl;
}




int separate(const char* line, Seq_T newRow, char* atom_val)
{
    int capacity = 1001;
    char ch;
    int size_atom = 0;

    while ((ch = *line++) != '\n')
    {
        if (isdigit((unsigned char)ch)) 
        {
            char *num = malloc(4);
            if (!num) {
                perror("Failed to allocate memory for num\n");
                exit(1);
            }

            num[0] = ch;
            int length = 1;

            while ((ch = *line++) != '\n')
            {
                if (isdigit((unsigned char)ch))
                {
                    num[length] = ch;
                    length++;
                    if (length >= 5) { // It should not exceed 4 (3 digits plus the null character)
                        printf("Number exceeds 3 digits: %s\n", num);
                        free(num);
                        exit(1); 
                    }
                }
                else
                {     
                    num[length] = '\0';                
                    if (size_atom >= capacity - 1) 
                    {  
                        fprintf(stderr, "atom_val buffer overflow\n");
                        exit(1);
                    }
                    atom_val[size_atom++] = ch;
                    break;
                }
            }

            int *number_ptr = malloc(sizeof(*number_ptr));
            if (!number_ptr) {
                perror("Failed to allocate memory for number_ptr\n");
                free(num);
                exit(1);
            }

            *number_ptr = atoi(num);
            free(num); 

            //printf("The number_ptr value is %d\n", *number_ptr);

            assert(-1 < *number_ptr);
            assert(*number_ptr < 256);

            Seq_addhi(newRow, number_ptr);

            if (ch == '\n') {
                break;
            }
        } 
        else 
        {   
            if (size_atom >= capacity - 1) 
            {  
                fprintf(stderr, "atom_val buffer overflow\n");
                exit(1);
            }
            atom_val[size_atom++] = ch;
        }
    }
    atom_val[size_atom] = '\0';

    return size_atom;
}

int construct_injected_sequence(const char* line, char* atom_val)
{
    int capacity = 1001;
    char ch;
    int size_atom = 0;

    while ((ch = *line++) != '\n')
    {
        if (isdigit((unsigned char)ch)) 
        {
            continue;
        } 
        else 
        {   
            if (size_atom >= capacity - 1) 
            {  
                fprintf(stderr, "atom_val buffer overflow\n");
                exit(1);
            }
            atom_val[size_atom++] = ch;
        }
    }
    atom_val[size_atom] = '\0';

    return size_atom;
}



void construct_newRow(const char* line, Seq_T newRow)
{
    char ch;

    while ((ch = *line++) != '\n')
    {
        if (isdigit((unsigned char)ch)) 
        {
            char *num = malloc(4);
            if (!num) {
                perror("Failed to allocate memory for num\n");
                exit(1);
            }

            num[0] = ch;
            int length = 1;

            while ((ch = *line++) != '\n')
            {
                if (isdigit((unsigned char)ch))
                {
                    num[length] = ch;
                    length++;
                    // It should not exceed 4 (3 digits plus the null character)
                    if (length >= 5) { 
                        printf("Number exceeds 3 digits: %s\n", num);
                        free(num);
                        exit(1); 
                    }
                }
                else
                {     
                    num[length] = '\0';                
                    break;
                }
            }

            int *number_ptr = malloc(sizeof(*number_ptr));
            if (!number_ptr) {
                perror("Failed to allocate memory for number_ptr\n");
                free(num);
                exit(1);
            }

            *number_ptr = atoi(num);
            free(num); 

            //printf("The number_ptr value is %d\n", *number_ptr);

            assert(-1 < *number_ptr);
            assert(*number_ptr < 256);

            Seq_addhi(newRow, number_ptr);

            if (ch == '\n') {
                break;
            }
        } 

    }
}


int check_atoms(Seq_T atom_sequence, const char* atom)
{
    
    for (int i = 0; i < Seq_length(atom_sequence) - 1; i++) {
        const char *current_atom = Seq_get(atom_sequence, i);
        // printf("\n");
        // printf("i: %d\n", i);
        // printf("%p\n", current_atom);
        // printf("%p\n", atom);
        if (current_atom == atom)
        {
            // printf("Found the indices\n");

            // printf("First index %d\n", i);

            // printf("Second index %d\n", Seq_length(atom_sequence));
            return i;
        }
            
    }
    // printf("returning %d", -1);
    return -1;
}

Seq_T correct_matrix(Seq_T matrix, int size_matrix, int index)
{
    // 1. Build the new matrix with the two “correct” rows
    Seq_T new_matrix = Seq_seq(Seq_get(matrix, index),
                               Seq_get(matrix, size_matrix - 1),
                               NULL);

    // 2. Free all other rows
    //    (Don’t free the rows at index and size_matrix-1 
    //     because they're in new_matrix)
    for (int i = 0; i < size_matrix; i++) {
        if (i != index && i != size_matrix - 1) {
            Seq_T row = Seq_get(matrix, i);
            int length = Seq_length(row);
            for (int j = 0; j < length; j++) {
                int *number_ptr = Seq_get(row, j);
                free(number_ptr); 
            }
            Seq_free(&row);
        }
    }

    // 3. Now free the old matrix
    Seq_free(&matrix);

    // 4. Return the new one
    return new_matrix;
}



// For testing purposes
void printing_matrix_to_file(Seq_T matrix, const char *filename)
{
    FILE *file = fopen(filename, "w"); // Open file in write mode
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    for (size_t i = 0; i < (size_t)Seq_length(matrix); i++)
    {
        Seq_T row = (Seq_T)Seq_get(matrix, i);
        for (size_t j = 0; j < (size_t)Seq_length(row); j++) 
        {
            int *num_ptr = (int *)Seq_get(row, j);
            if (num_ptr) {
                if (j + 1 == (size_t)Seq_length(row))
                    printf("%d", *num_ptr);
                else
                    printf("%d ", *num_ptr);
            } else {
                printf("NULL ");
            }
        } 
    }

    // fprintf(file, "create_P2_file was successful\n");
    fclose(file); // Close the file
}

void printing_atom_seq(Seq_T atom_sequence)
{
    printf("Printing the atom_sequence: \n");
    for (size_t j = 0; j < (size_t)Seq_length(atom_sequence); j++) 
    {
        char *str = Seq_get(atom_sequence, j);
        if (str) {
            printf("%s", str);
        } else {
            printf("NULL ");
        }
    }
    printf("\n");
}



