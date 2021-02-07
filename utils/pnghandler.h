#ifndef __pnghandler_H
#define __pnghandler_H

void print2DArray_int_withshape(int **array, int shapeOne, int shapeTwo);

void getDataFromPng(char *filename, double *xList);

void read_png_file(char *filename);

bool checkIfValid(char *fileName);

#endif
