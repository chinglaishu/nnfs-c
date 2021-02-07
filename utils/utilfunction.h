#ifndef __utilfunction_H
#define __utilfunction_H

double getdoubleRandomNum(double maxNum);

int getIntRandomNum(int maxNum);

void create2DArrayWithNum(double **array, int shapeOne, int shapeTwo, double useNum, bool isRandom);

void create1DArrayWithNum_int(int *array, int arrayLength, int useNum, bool isRandom);

void fill2DArrayAsRandom(int **array, int shapeOne, int shapeTwo, int maxNum);

void printArray(int *array, int arrayLength);

void print2DArray_int(int **array, int shapeOne, int shapeTwo);

void print2DArray_double(double **array, int shapeOne, int shapeTwo);

void conditionMalloc2DArray_double(double **array, int arrayLength);

void conditionMalloc2DArray_int(int **array, int arrayLength);

void conditionMalloc1DArray_double(double *array, int arrayLength);

void conditionMalloc1DArray_int(int *array, int arrayLength);

void printArray_double(double *array, int arrayLength);

#endif
