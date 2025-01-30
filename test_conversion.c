#include <stdio.h>
#include <stdlib.h>
#include "readaline.h"
#include "seq.h"
#include "readaline.h"
#include "conversion.h"

// Function to print a sequence of characters (for testing purposes)
void print_sequence(Seq_T sequence) {
    for (int i = 0; i < Seq_length(sequence); i++) {
        char *ch = Seq_get(sequence, i);
        printf("%c", *ch);
    }
    printf("\n");
}

// Function to test conversion and write to binary file
void conversion_test_tiny() {
    FILE *file = fopen("tinypix.txt", "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    char *line = NULL;
    size_t len;

    // Create a sequence to store all lines (each line is a sequence of integers)
    Seq_T all_lines = Seq_new(0);
    
    FILE *out = fopen("tinytest", "w"); // Open output file in binary mode

    // Read and process each line from the file
    while ((len = readaline(file, &line)) > 0) {
        // Convert the line into a sequence of integers
        Seq_T line_sequence = convert_line_to_sequence(line);

        // Add the sequence to the main sequence
        Seq_addhi(all_lines, line_sequence);

        // Free the line buffer after processing
        free(line);
        line = NULL;
    }

    // Print all sequences (for testing purposes)
    for (int i = 0; i < Seq_length(all_lines); i++) {
        Seq_T line_sequence = Seq_get(all_lines, i);
        //print_sequence(line_sequence);
        writeRowToBinary(line_sequence, out);
    }

    // Free all sequences and their contents
    for (int i = 0; i < Seq_length(all_lines); i++) {
        Seq_T line_sequence = Seq_get(all_lines, i);
        for (int j = 0; j < Seq_length(line_sequence); j++) {
            int *num = Seq_get(line_sequence, j);
            printf("Number: %d\n", *num);
            free(num); // Free each integer
        }
        Seq_free(&line_sequence); // Free the sequence of integers
    }

    writeP5Header(4, 4, out);

    Seq_free(&all_lines); // Free the main sequence

    fclose(file);
    fclose(out);
}

    

int main() {

    conversion_test_tiny();
    return 0;
}