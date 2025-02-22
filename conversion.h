#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeP5Header(int width, int height, FILE *file);

void writeRowToBinary(Seq_T pixelRow, FILE *file);

Seq_T convert_line_to_sequence(const char *line);

#endif