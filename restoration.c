#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "atom.h"
#include "seq.h"
#include "restoration.h"


//It is known that the lines of text have less than 1000 characters
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

    separate(line, newRow, atom_val);

    Seq_addhi(matrix, newRow);

    const char *atom = Atom_string(atom_val);
    Seq_addhi(atom_sequence, atom);

    free(atom_val);

    return check_atoms(atom_sequence, atom);
}


int diff_nums_chars2(const char* line, char* correct_atom, Seq_T matrix, 
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

    separate(line, newRow, atom_val);

    const char *atom = Atom_string(atom_val);

    if (atom == correct_atom)
    {
        assert(Seq_length(newRow) == width);

        Seq_addhi(atom_sequence, atom);
        Seq_addhi(matrix, newRow);
    }
    else
        fl++;

    free(atom_val);

    return fl;
}

void separate(const char* line, Seq_T newRow, char* atom_val)
{
    assert(line != NULL);
    assert(atom_val != NULL);

    char ch;
    size_t size_atom = 0;
    int capacity = 1001;  // Define capacity to enforce boundary checks

    while ((ch = *line++) != '\0')
    {
        if (isdigit((unsigned char)ch)) 
        {
            int* num = malloc(sizeof(int));  // Allocate memory for an int
            if (!num) 
            {
                perror("Failed to allocate memory for num");
                exit(1);
            }
            *num = ch - '0';
            Seq_addhi(newRow, num);
        } 
        else 
        {
            if (size_atom >= (size_t)(capacity - 1)) 
            {  
                fprintf(stderr, "atom_val buffer overflow\n");
                exit(1);
            }
            atom_val[size_atom++] = ch;
        }
    }
    atom_val[size_atom] = '\0';
}


int check_atoms(Seq_T atom_sequence, const char* atom)
{
    
    for (int i = 0; i < Seq_length(atom_sequence); i++) {
        const char *current_atom = (const char *)Seq_get(atom_sequence, i);
        if (current_atom == atom)
            return i;
    }
    return -1;
}

Seq_T correct_matrix(Seq_T matrix, int size_matrix, int index)
{
    if (index < 0 || index >= size_matrix) {
        fprintf(stderr, "Index %d out of bounds for matrix of size %d\n", index, size_matrix);
        exit(1);
    }

    if (size_matrix <= 0) {
        fprintf(stderr, "Invalid size_matrix: %d\n", size_matrix);
        exit(1);
    }

    Seq_T new_matrix = 
            Seq_seq(Seq_get(matrix, index), Seq_get(matrix, size_matrix - 1), NULL);
    return new_matrix;
} 

// For testing purposes
void create_P2_file(Seq_T matrix)
{
    for (size_t i = 0; i < (size_t)Seq_length(matrix); i++)  // Cast to size_t if Seq_length returns int
    {
        Seq_T row = (Seq_T)Seq_get(matrix, i);
        for (size_t j = 0; j < (size_t)Seq_length(row); j++) 
        {
            int *num_ptr = (int *)Seq_get(row, j);
            if (num_ptr) {
                printf("%d ", *num_ptr);
            } else {
                printf("NULL ");
            }
        }
        printf("\n");  // Newline after each row
    }
    printf("create_P2_file was successful\n");
}



