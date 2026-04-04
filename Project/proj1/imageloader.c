/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stddef.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

// print the error message and exit;
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
	printf("fail to open file %s\n", filename);
	exit(0);
    }
    Image *image = malloc(sizeof(Image));
    if (image == NULL) {
	allocation_failed();
    }
    char format[10];
    fscanf(fp, "%9s", format);
    fscanf(fp, "%u %u", &(image->cols), &(image->rows));
    // setup image, malloc its column space and row space.
    setup_image(image);

    int scalar = 0;
    fscanf(fp, "%d", &scalar);
    for (int i = 0; i < image->rows; i += 1) {
	for (int j = 0; j < image->cols; j += 1) {
	    fscanf(fp, "%hhu %hhu %hhu",
		   &(image->image[i][j].R),
		   &(image->image[i][j].G),
		   &(image->image[i][j].B));
	}
    }
    fclose(fp);
    return image;
}

//Given an image, setup the image variable of it.
void setup_image(Image *image) {
    image->image = (Color **)malloc(sizeof(Color *)
				    * image->rows);
    if (image->image == NULL) {
	allocation_failed();
    }
    for (int i = 0; i < image->rows; i += 1) {
	image->image[i] = (Color *) malloc(sizeof(Color)
					   * image->cols);
	if (image->image[i] == NULL) {
	    allocation_failed();
	}
    }
}


//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    if (image == NULL) {
	printf("Wrong variable image, must be not NULL!\n");
	exit(0);
    }

    if (image->image == NULL) {
	printf("Image is NULL\n");
	exit(0);
    }
    printf("P3\n");
    printf("%hhu %hhu\n", image->cols, image->rows);
    printf("255\n");
    for (int i = 0; i < image->rows; i += 1) {
	for (int j = 0; j < image->cols; j += 1) {
	    if (j > 0) {
		printf(" ");
	    }
	    printf("%3hhu %3hhu %3hhu",
		   image->image[i][j].R,
		   image->image[i][j].G,
		   image->image[i][j].B);
	    if (j < image->cols - 1) {
		printf("  ");
	    }
	}
	printf("\n");
    }
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
    if (image == NULL) {
	printf("Wrong variable image, must be not NULL!\n");
	exit(0);
    }

    if (image->image == NULL) {
	printf("Image is NULL\n");
	exit(0);
    }

    for (int i = 0; i < image->rows; i += 1) {
	free(image->image[i]);
    }
    free(image->image);
    free(image);
}

