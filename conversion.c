#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to generate P5 PGM data as a byte array and save to a file
void generate_p5_pgm_to_file(int *pixels, int width, int height, int maxValue, const char *filename) {
    if (maxValue < 1 || maxValue > 255) {
        fprintf(stderr, "Error: max grayscale value must be between 1 and 255.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate the size of the header and pixel data
    char header[100];
    size_t header_length = snprintf(header, sizeof(header), "P5\n%d %d\n%d\n", width, height, maxValue);
    if (header_length >= sizeof(header)) {
        fprintf(stderr, "Error: header size exceeded.\n");
        exit(EXIT_FAILURE);
    }

    size_t pixel_data_size = width * height;
    size_t output_size = header_length + pixel_data_size; // Total size = header + pixels

    // Allocate memory for the P5 data
    unsigned char *pgm_data = malloc(output_size);
    if (pgm_data == NULL) {
        perror("Error allocating memory for P5 data");
        exit(EXIT_FAILURE);
    }

    // Copy the header into the data
    memcpy(pgm_data, header, header_length);

    // Copy the pixel data into the data
    for (int i = 0; i < width * height; i++) {
        if (pixels[i] < 0 || pixels[i] > maxValue) {
            fprintf(stderr, "Error: pixel value out of range: %d\n", pixels[i]);
            free(pgm_data);
            exit(EXIT_FAILURE);
        }
        pgm_data[header_length + i] = (unsigned char)pixels[i];
    }

    // Write the data to the file
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        free(pgm_data);
        exit(EXIT_FAILURE);
    }
    fwrite(pgm_data, 1, output_size, file);
    fclose(file);

    // Free the allocated memory
    free(pgm_data);

    printf("P5 PGM data saved to %s\n", filename);
}

// Main function to demonstrate usage
int exampleConversion() {
    // Example parameters
    int width = 3;                              // Image width
    int height = 2;                             // Image height
    int maxValue = 255;                         // Maximum grayscale value (1-255)
    int pixels[] = {10, 20, 30, 40, 50, 60};    // Pixel data (3x2 image)

    // Output file name
    const char *filename = "outputTest.pgm";

    // Generate the P5 PGM data and save to file
    generate_p5_pgm_to_file(pixels, width, height, maxValue, filename);

    return 0;
}
