#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "atom.h"


void create_array_atoms()
{
    const char *atoms[2];

    atoms[0] = Atom_string("hey");
    atoms[1] = Atom_string("hello");

    printf("%s\n", atoms[0]);
    printf("%s\n", atoms[1]);
}

int main()
{
  create_array_atoms();
}
