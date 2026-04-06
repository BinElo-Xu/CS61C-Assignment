/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <alloca.h>
#include <stddef.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// print the error message and exit;
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

void set_color(Color **color, uint8_t n) {
    if (n == 0) {
	(*color)->B = 0;
	(*color)->G = 0;
	(*color)->R = 0;
    } else {
	(*color)->B = 255;
	(*color)->G = 255;
	(*color)->R = 255;
    }
}
//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
    Color *ans = malloc(sizeof(Color));
    if (ans == NULL) {
	allocation_failed();
    }
    uint8_t b = image->image[row][col].B;
    if ((1&b) == 1) {
	set_color(&ans, 1);
    } else {
	set_color(&ans, 0);
    }
    return ans;
}


//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
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
	    Color *tmp = evaluateOnePixel(image, i, j);
	    newImage->image[i][j] = *tmp;
	    free(tmp);
	}
    }
    return newImage;
}


void processCLI(int argc, char **argv, char **filename) 
{
	if (argc != 2) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}
	*filename = argv[1];
}
/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    Image *image;
    char *filename;
    Image *newImage;
    processCLI(argc, argv, &filename);
    image = readData(filename);
    newImage = steganography(image);
    freeImage(image);
    writeData(newImage);
    freeImage(newImage);
}

