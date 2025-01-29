#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seq.h"
#include "assert.h"

void writeP5Header(int width, int height, FILE *file){
    assert(width > 0);
    assert(height > 0);
    assert(file != NULL);

    // Move the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    fprintf(file, "P5\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");
}

void writeRowToBinary(Seq_T pixelRow, FILE *file) {
    assert(pixelRow != NULL);
    assert(file != NULL);

    for (int i = 0; i < Seq_length(pixelRow); i++) {
        int *pixel = Seq_get(pixelRow, i);
        assert(pixel != NULL);
        assert(*pixel >= 1 && *pixel <= 255);

        unsigned char byte = (unsigned char)(*pixel);
        fwrite(&byte, sizeof(byte), 1, file);
    }
}


