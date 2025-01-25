#include <stdio.h>
#include "seq.h"
#include "atom.h"

int main() {
    Sequence_T atom_sequence = Sequence_new(0);

    const char *atom1 = Atom_string("Hello");
    const char *atom2 = Atom_string("World");
    const char *atom3 = Atom_string("Hello");

    Sequence_add(atom_sequence, (void *)atom1);
    Sequence_add(atom_sequence, (void *)atom2);
    Sequence_add(atom_sequence, (void *)atom3);

    // Check if the atoms are unique
    if (atom1 == atom3) {
        printf("\natom1 and atom3 point to the same unique Atom.\n");
    } else {
        printf("\natom1 and atom3 are different (this shouldn't happen).\n");
    }

    Sequence_free(&atom_sequence);
    return 0;
}
