/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "imageloader.h"


// print the error message and exit;
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

// return weather the cell is alive in (row, col).
int8_t isLive(Image *image, int row, int clo);
//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
    if (image == NULL) {
	printf("Image is NULL!\n");
	exit(0);
    }

    if (image->image == NULL) {
	printf("Image has no image contains!\n");
	exit(0);
    }
    Color *ans = malloc(sizeof(Color));
    if (ans == NULL) {
	allocation_failed();
    }
    int8_t liveNum = 0;
    int32_t sumR = 0, sumG = 0, sumB = 0;

    for (int i = row - 1; i <= row + 1; i += 1) {
	for (int j = col - 1; j <= col + 1; j += 1) {
	    int realI = (i + image->rows) % image->rows;
	    int realJ = (j + image->cols) % image->cols;
	    if (i == row && j == col) {
		continue;
	    }

	    if (isLive(image, realI, realJ)) {
		liveNum += 1;
		sumR += image->image[realI][realJ].R;
		sumG += image->image[realI][realJ].G;
		sumB += image->image[realI][realJ].B;
	    }
	}
    }
    if (isLive(image, row, col)) {
	if(rule & (1<<(liveNum + 9))) {
	    *ans = image->image[row][col];
	} else {
	    ans->B = 0;
	    ans->G = 0;
	    ans->R = 0;
	}
    } else {
	if(rule & (1<<(liveNum))) {
	    if (liveNum > 0) {
		ans->B = (uint8_t)(sumB / liveNum);
		ans->G = (uint8_t)(sumG / liveNum);
		ans->R = (uint8_t)(sumR / liveNum);	
	    } else {
		ans->B = 0;
		ans->G = 0;
		ans->R = 0;	
	    }
	} else {
	    ans->B = 0;
	    ans->G = 0;
	    ans->R = 0;
	}
	
    }
    return ans;
}


int8_t isLive(Image *image, int row, int col) {
    if (image->image[row][col].B != 0 ||
	image->image[row][col].G != 0 ||
	image->image[row][col].R != 0) {
	return 1;
    }
    return 0;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
    if (image == NULL) {
	printf("image is NULL\n");
	exit(0);
    }

    if (image->image == NULL) {
	printf("image contains no image!\n");
	exit(0);
    }
    Image *newImage = malloc(sizeof(Image));
    if (newImage == NULL) {
	allocation_failed();
    }
    newImage->rows = image->rows;
    newImage->cols = image->cols;
    setup_image(newImage);
    for (int i = 0; i < image->rows; i += 1) {
	for (int j = 0; j < image->cols; j += 1) {
	    Color *tmp = evaluateOneCell(image, i, j, rule);
	    newImage->image[i][j] = *tmp;
	    free(tmp);
	}
    }
    return newImage;
}

void processCLI(int argc, char **argv, char **filename, uint32_t *rule) 
{
	if (argc != 3) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}
	*filename = argv[1];
	*rule = (uint32_t)strtol(argv[2], NULL, 0);
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    Image *image;
    char *filename;
    Image *newImage;
    uint32_t rule;
    processCLI(argc, argv, &filename, &rule);
    image = readData(filename);
    newImage = life(image, rule);
    freeImage(image);
    writeData(newImage);
    freeImage(newImage);
}
