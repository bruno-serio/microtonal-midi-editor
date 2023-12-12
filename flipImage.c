#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/*
 *  ./flipImage <file_name>.ppm
 */

int main(int argc, char *argv[]) {

	// open original file and read dimensions.
	FILE *origFile = fopen(argv[1], "r");
	unsigned char output;
	int widthO, heightO, position = 2;

	if (origFile == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	fseek(origFile, 3, SEEK_SET);
	widthO = getDimension(origFile, &position, 0x20);
	heightO = getDimension(origFile, &position, 0x0a);

	// create new file with SWAPPED dimensions.
	FILE *newFile = fopen("output.ppm", "wb");
	fprintf(newFile, "P6\n%d %d\n255\n", heightO, widthO);
	
	// set cursor to image body.
	fseek(origFile, 3, SEEK_CUR);

	// move cursor to the last row, first column.
	fseek(origFile, 3*widthO*(heightO-1), SEEK_CUR);;

	for (int j=0; j<widthO; ++j) {
		fseek(origFile, 3*widthO*(heightO-1)+3*j, SEEK_SET);
		for (int i=0; i<heightO; ++i) {
			if (i>0) {
				fseek(origFile, -(widthO+1)*3, SEEK_CUR);
			}
			copyPixel(origFile, newFile);		
		}
	}

	printf("Image flipped correctly.\n");
	
	int convertStatusExitCode;

	fclose(origFile);
	fclose(newFile);
	
	convertStatusExitCode = system("convert output.ppm output.png");
	
	switch (convertStatusExitCode) {
		case -1: printf("Error converting image. Check if you have Magick Converter installed.\n");
			 break;
		case 0: printf("Image converted correctly.\n");
			break;
		default: printf("Error executing convert command.\nError code %d\n", convertStatusExitCode);
	}

	return 0;
}
