#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "seq.h"
#include "conversion.h"

// Mockup function for conversion (replace with actual function signature)
unsigned char *convert_row_to_binary(Seq_T pixels, int width, int maxValue) {
    unsigned char *binaryRow = malloc(width);
    if (!binaryRow) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < width; i++) {
        int pixel = (int)(long)Seq_get(pixels, i);
        if (pixel < 0 || pixel > maxValue) {
            fprintf(stderr, "Error: pixel value out of range\n");
            free(binaryRow);
            return NULL;
        }
        binaryRow[i] = (unsigned char)pixel;
    }
    return binaryRow;
}

void test_conversion_normal_case() {
    Seq_T pixels = Seq_seq((void *)(long)10, (void *)(long)20, (void *)(long)30, NULL);
    unsigned char *binaryRow = convert_row_to_binary(pixels, 3, 255);

    assert(binaryRow[0] == 10);
    assert(binaryRow[1] == 20);
    assert(binaryRow[2] == 30);

    free(binaryRow);
    Seq_free(&pixels);
}

void test_conversion_out_of_range() {
    Seq_T pixels = Seq_seq((void *)(long)10, (void *)(long)256, NULL); // 256 is out of range

    unsigned char *binaryRow = convert_row_to_binary(pixels, 2, 255);
    assert(binaryRow == NULL); // Should fail

    Seq_free(&pixels);
}

void test_conversion_empty_row() {
    Seq_T pixels = Seq_seq(NULL);
    unsigned char *binaryRow = convert_row_to_binary(pixels, 0, 255);
    assert(binaryRow != NULL); // Should return an empty but valid array

    free(binaryRow);
    Seq_free(&pixels);
}
// Main function to demonstrate usage
void test_conversion_turring() {
    // Example parameters
    int width = 100;                              // Image width
    int height = 136;                             // Image height
    int maxValue = 255;                         // Maximum grayscale value (1-255)

    // Create the pixel sequence
    const char *inputfileName = "turing-p2-nums.txt";
    Seq_T pixels = getPixels(inputfileName);

    // Output file name
    const char *outputfileName = "Turing-p5.pgm";

    // Generate the P5 PGM data and save to file
    generate_p5_pgm_to_file(pixels, width, height, maxValue, filename);

    // Free the sequence
    Seq_free(&pixels);
}

int main() {
    test_conversion_normal_case();
    test_conversion_out_of_range();
    test_conversion_empty_row();
    test_conversion_turring();

    printf("All conversion tests passed!\n");
    return 0;
}
