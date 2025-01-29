#ifndef RESTORATION_H
#define RESTORATION_H


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

// #include "atom.h"
#include "seq.h"



int diff_nums_chars1(const char *line, Seq_T matrix, Seq_T atom_sequence);
int diff_nums_chars2(const char* line, char* correct_atom, Seq_T matrix, 
                                                Seq_T atom_sequence, int width);
void separate(const char* line, Seq_T newRow, char* atom_val);
int check_atoms(Seq_T atom_sequence, const char* atom);
Seq_T correct_matrix(Seq_T matrix, int size_matrix, int index);

//For testing
void create_P2_file(Seq_T matrix);

#endif


