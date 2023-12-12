#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

void index_to_string(int number, char stringIn[6]);

void copyPixel(FILE *origFile, FILE *newFile);

int getDimension(FILE *filename, int *position, unsigned char exitCondition);

#endif
