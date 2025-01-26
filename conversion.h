#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *generate_p5_pgm(int *pixels, int width, int height, int maxValue, size_t *output_size);

int exampleConversion();

#endif