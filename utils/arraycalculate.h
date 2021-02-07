#ifndef _arraycalculate_H
#define _arraycalculate_H

double getSingleDotProduct(double **array1, double **array2, int commonShapeNum, int xIndex, int yIndex);

void dotProductAddBias(double **newArray, double **array1, int array1ShapeOne, int array1ShapeTwo, double **array2, int array2ShapeOne, int array2ShapeTwo, double **biasList);

void dotProduct(double **newArray, double **array1, int array1ShapeOne, int array1ShapeTwo, double **array2, int array2ShapeOne, int array2ShapeTwo);

void transposeArray(double **newArray, double **array, int arrayShapeOne, int arrayShapeTwo);

void Get2DArraySum(double **newArray, double **array, int shapeOne, int shapeTwo);

void create2DArrayWithLimitValue(double **newArray, double **array, int shapeOne, int shapeTwo, double minNum, double maxNum);

void limitValueOnArray(double *array, int arrayLength, double minNum, double maxNum);

double getNumWithLimitRange(double useNum, double minNum, double maxNum);

void getProbability(double **array, int shapeOne, int shapeTwo);

void get2DArrayExp(double **array, int shapeOne, int shapeTwo);

void getArrayTimeSomething(int id, double *array, int arrayLength, double useNum);

void allBecomeMinusMaxofRow(double **array, double **newArray, int shapeOne, int shapeTwo);

double getSumOfRow(double *array, int length);

double getMaxOfRow(double *array, int length);

void MinusOrAdd2DArray(double **array, double **changeArray, int shapeOne, int shapeTwo, int useSign);

void getArrayByIndex(double **array, int *indexArray, double *newArray, int shapeOne);

int getMaxValueIndexOfRow(double *array, int arrayLength);

void getMaxValueIndexList(double **array, int *newArray, int shapeOne, int shapeTwo);

int countSameValueOnSameIndex(int *array1, int *array2, int arrayLength);

void free2DArray_double(double **array, int arrayLength);

void free2DArray_int(int **array, int arrayLength);

void fill2DArray_double(double **array, int shapeOne, int shapeTwo, double useNum);

void sliceArray_double(double *array, double *newArray, int startIndex, int endIndex);

void sliceArray_int(int *array, int *newArray, int startIndex, int endIndex);

void slice2DArray_double(double **array, double **newArray, int startIndex, int endIndex, int shapeTwo);

void slice2DArray_int(int **array, int **newArray, int startIndex, int endIndex, int shapeTwo);

double getAbsSumOf2DArray_double(double **array, int shapeOne, int shapeTwo);

double getSquareSumOf2DArray_double(double **array, int shapeOne, int shapeTwo);

#endif