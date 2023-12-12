#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void index_to_string(int number, char stringIn[6]) {
	char temp[6];
	char *stringOut = malloc(3*sizeof(char));

	if (number > 999) {
		printf("Track number is too big (int_to_string function).\n");
		exit(2);
	}

	if (number < 10) {
		strcat(stringOut, "0");
	}
	if (number < 100) {
		strcat(stringOut, "0");
	}

	sprintf(temp, "%d", number);
	strcat(stringOut, temp);
	strcpy(stringIn, stringOut);
	
	return;
}

void copyPixel(FILE *origFile, FILE *newFile) {
	unsigned char color;
	for (int i=0; i<3; ++i) {
		color = fgetc(origFile);
		fputc(color, newFile);
	}
	return;
}
