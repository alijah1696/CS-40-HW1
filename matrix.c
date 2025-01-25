#include "seq.h"

//1) Initializing a matrix and adding a new row
Sequence_T matrix = Sequence_new(150);
Sequence_addhi(matrix, newRow);

//2) Initializing a row and 
Sequence_T newRow = Sequence_new(1001);
Sequence_addhi(newRow, &default_value);

// 3) Expanding capacity
Seq_T Seq_expand(Seq_T seq, Size_t capacity) {
    Seq_T new_seq = Seq_new(capacity * 2 + 2);
    
    for (int i = 0; i < Seq_length(seq); i++) 
        Seq_addhi(new_seq, Seq_get(seq, i));

    Seq_free(&seq);
    return new_seq;
}

if (Seq_length(seq) >= capacity)
    seq = Seq_expand(seq, capacity);

// 4) Create a new sequence based on the found right indices
Seq_T remove_rows(Seq_T seq, int* v) {

    assert(seq != NULL);
    assert(indices != NULL);
    assert(count == 2);
  
    Seq_T new_seq = Seq_new(150);
    Seq_addhi(new_seq, Seq_get(seq, v[0]));
    Seq_addhi(new_seq, Seq_get(seq, v[1]));

    Seq_free(&seq);
    return new_seq;
}
