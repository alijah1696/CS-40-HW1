#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seq.h"
#include "assert.h"
#include "string.h"

// Function to write P5 header
void writeP5Header(int width, int height, FILE *file) {
    assert(width > 0);
    assert(height > 0);
    assert(file != NULL);

    // Move the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    fprintf(file, "P5\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");
}

// Function to write a row of pixels to binary file
void writeRowToBinary(Seq_T pixelRow, FILE *file) {
    assert(pixelRow != NULL);
    assert(file != NULL);

    for (int i = 0; i < Seq_length(pixelRow); i++) {
        int *pixel = Seq_get(pixelRow, i);
        assert(pixel != NULL);
        //assert(*pixel >= 1 && *pixel <= 255);

        unsigned char byte = (unsigned char)(*pixel);
        fwrite(&byte, sizeof(byte), 1, file);
    }
}

// Function to convert a line into a sequence of integers
Seq_T convert_line_to_sequence(const char *line) {
    Seq_T sequence = Seq_new(0); // Create a new sequence

    // Manually allocate memory and copy the string
    char *line_copy = malloc(strlen(line) + 1);
    if (!line_copy) {
        perror("Failed to allocate memory for line copy");
        exit(EXIT_FAILURE);
    }
    strcpy(line_copy, line);

    char *token = strtok(line_copy, " ");
    
    // Iterate through each token in the line and add it to the sequence
    while (token != NULL) {
        int *num = malloc(sizeof(int)); // Allocate memory for each integer
        if (!num) {
            perror("Failed to allocate memory for integer");
            exit(EXIT_FAILURE);
        }
        *num = atoi(token); // Convert the token to an integer
        Seq_addhi(sequence, num); // Add the integer to the sequence
        token = strtok(NULL, " "); // Move to the next token
    }

    free(line_copy); // Free the allocated memory for line_copy
    return sequence;
}


