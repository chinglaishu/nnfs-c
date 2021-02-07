#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "./utilfunction.h"

// commonShapeNum = array1ShapeTwo = array2ShapeOne
double getSingleDotProduct(double **array1, double **array2, int commonShapeNum, int shapeOne, int shapeTwo) {
  double sum = 0;
  for (int i = 0 ; i < commonShapeNum ; i++) {
    double firstNum = array1[shapeOne][i];
    double secondNum = array2[i][shapeTwo];
    sum = sum + firstNum * secondNum;
  }
  return sum;
}

double getNumWithLimitRange(double useNum, double minNum, double maxNum) {
  if (useNum < minNum) {return minNum; }
  if (useNum > maxNum) {return maxNum; }
  return useNum;
}

void dotProductAddBias(double **newArray, double **array1, int array1ShapeOne, int array1ShapeTwo, double **array2, int array2ShapeOne, int array2ShapeTwo, double **biasList) {
  int newArrayShapeOne = array1ShapeOne;
  int newArrayShapeTwo = array2ShapeTwo;
  int commonShapeNum = array1ShapeTwo;
  for (int i = 0 ; i < newArrayShapeOne ; i++) {
    // newArray[i] = (double *) malloc(newArrayShapeTwo * sizeof(double));
    for (int a = 0 ; a < newArrayShapeTwo ; a++) {
      newArray[i][a] = getSingleDotProduct(array1, array2, commonShapeNum, i, a) + biasList[0][a];
    }
  }
}

void dotProduct(double **newArray, double **array1, int array1ShapeOne, int array1ShapeTwo, double **array2, int array2ShapeOne, int array2ShapeTwo) {
  int newArrayShapeOne = array1ShapeOne;
  int newArrayShapeTwo = array2ShapeTwo;
  int commonShapeNum = array1ShapeTwo;
  for (int i = 0 ; i < newArrayShapeOne ; i++) {
    // newArray[i] = (double *) malloc(newArrayShapeTwo * sizeof(double));
    for (int a = 0 ; a < newArrayShapeTwo ; a++) {
      newArray[i][a] = getSingleDotProduct(array1, array2, commonShapeNum, i, a);
    }
  }
}

void transposeArray(double **newArray, double **array, int newArrayShapeOne, int newArrayShapeTwo) {
  for (int i = 0 ; i < newArrayShapeOne ; i++) {
    for (int a = 0 ; a < newArrayShapeTwo ; a++) {
      newArray[i][a] = array[a][i];
    }
  }
}

void Get2DArraySum(double **newArray, double **array, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      newArray[0][a] += array[i][a];
    }
  }
}

void create2DArrayWithLimitValue(double **newArray, double **array, int shapeOne, int shapeTwo, double minNum, double maxNum) {
  for (int i = 0 ; i < shapeOne ; i++) {
    // newArray[i] = (double *) malloc(shapeTwo * sizeof(double));
    getArrayWithLimitValue(array[i], newArray[i], shapeTwo, minNum, maxNum);
    /*
    for (int a = 0 ; a < shapeTwo ; a++) {
      double useNum = getNumWithLimitRange(array[i][a], minNum, maxNum);
      newArray[i][a] = useNum;
    }
    */
  }
}

void getArrayWithLimitValue(double *array, double *newArray, int arrayLength, double minNum, double maxNum) {
  for (int i = 0 ; i < arrayLength ; i++) {
    newArray[i] = getNumWithLimitRange(array[i], minNum, maxNum);
  }
}

void limitValueOnArray(double *array, int arrayLength, double minNum, double maxNum) {
  for (int i = 0 ; i < arrayLength ; i++) {
    double useNum = getNumWithLimitRange(array[i], minNum, maxNum);
    array[i] = useNum;
  }
}

double getSumOfRow(double *array, int length) {
  double sum = 0;
  for (int i = 0 ; i < length ; i++) {
    sum += array[i];
  }
  return sum;
}

double getMaxOfRow(double *array, int length) {
  double recordMaxNum = LONG_MIN;
  for (int i = 0 ; i < length ; i++) {
    if (array[i] > recordMaxNum) {
      recordMaxNum = array[i];
    }
  }
  return recordMaxNum;
}

void getProbability(double **array, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    // newArray[i] = (double *) malloc(shapeTwo * sizeof(double));
    double rowSum = getSumOfRow(array[i], shapeTwo);
    for (int a = 0 ; a < shapeTwo ; a++) {
      double value = array[i][a] / rowSum;
      array[i][a] = value;
    }
  }
}

void get2DArrayExp(double **array, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    getArrayTimeSomething(0, array[i], shapeTwo, M_E);
    /*
    for (int a = 0 ; a < shapeTwo ; a++) {
      array[i][a] = pow(M_E, (array[i][a]));
    }
    */
  }
}

void getArrayTimeSomething(int id, double *array, int arrayLength, double useNum) {
  // id:0 = pow, id:1 = log
  for (int i = 0 ; i < arrayLength ; i++) {
    if (id == 0) {
      array[i] = pow(useNum, array[i]);
    } else if (id == 1) {
      array[i] = useNum * log(array[i]);
    }
  }
}

void allBecomeMinusMaxofRow(double **array, double **newArray, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    // newArray[i] = (double *) malloc(shapeTwo * (sizeof(double)));
    double maxOfRow = getMaxOfRow(array[i], shapeTwo);
    for (int a = 0 ; a < shapeTwo ; a++) {
      newArray[i][a] = array[i][a] - maxOfRow;
    }
  }
}

// useSign = -1 = minus, 1 = add
void MinusOrAdd2DArray(double **array, double **changeArray, int shapeOne, int shapeTwo, int useSign) {
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      changeArray[i][a] = changeArray[i][a] + (array[i][a] * useSign);
    }
  }
}

void getArrayByIndex(double **array, int *indexArray, double *newArray, int shapeOne) {
  for (int i = 0 ; i < shapeOne ; i++) {
    int useIndex = indexArray[i];
    newArray[i] = array[i][useIndex];
  }
}

int getMaxValueIndexOfRow(double *array, int arrayLength) {
  double recordMaxValue = LONG_MIN;
  int recordIndex = 0;
  for (int i = 0 ; i < arrayLength ; i++) {
    if (array[i] > recordMaxValue) {
      recordMaxValue = array[i];
      recordIndex = i;
    }
  }
  return recordIndex;
}

void getMaxValueIndexList(double **array, int *newArray, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    int maxValueIndex = getMaxValueIndexOfRow(array[i], shapeTwo);
    newArray[i] = maxValueIndex;
  }
}

int countSameValueOnSameIndex(int *array1, int *array2, int arrayLength) {
  int count = 0;
  for (int i = 0 ; i < arrayLength ; i++) {
    if (array1[i] == array2[i]) {
      count = count + 1;
    }
  }
  return count;
}

void free2DArray_double(double **array, int arrayLength) {
  for (int i = 0 ; i < arrayLength ; i++) {
    free(array[i]);
  }
  free(array);
}

void free2DArray_int(int **array, int arrayLength) {
  for (int i = 0 ; i < arrayLength ; i++) {
    free(array[i]);
  }
  free(array);
}


void fill2DArray_double(double **array, int shapeOne, int shapeTwo, double useNum) {
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      array[i][a] = useNum;
    }
  }
}

void sliceArray_double(double *array, double *newArray, int startIndex, int endIndex) {
  for (int i = startIndex ; i < endIndex ; i++) {
    int useIndex = i - startIndex;
    newArray[useIndex] = array[i];
  }
}

void sliceArray_int(int *array, int *newArray, int startIndex, int endIndex) {
  for (int i = startIndex ; i < endIndex ; i++) {
    int useIndex = i - startIndex;
    newArray[useIndex] = array[i];
  }
}


void slice2DArray_double(double **array, double **newArray, int startIndex, int endIndex, int shapeTwo) {
  for (int i = startIndex ; i < endIndex ; i++) {
    int useIndex = i - startIndex;
    newArray[useIndex] = (double *) malloc(shapeTwo * sizeof(double));
    for (int a = 0 ; a < shapeTwo ; a++) {
      newArray[useIndex][a] = array[i][a];
    }
  }
}

void slice2DArray_int(int **array, int **newArray, int startIndex, int endIndex, int shapeTwo) {
  for (int i = startIndex ; i < endIndex ; i++) {
    newArray[i] = (int *) malloc(shapeTwo * sizeof(int));
    for (int a = 0 ; a < shapeTwo ; a++) {
      newArray[i][a] = array[i][a];
    }
  }
}

double getAbsSumOf2DArray_double(double **array, int shapeOne, int shapeTwo) {
  double sum = 0.0;
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      sum += fabs(array[i][a]);
    }
  }
  return sum;
}

double getSquareSumOf2DArray_double(double **array, int shapeOne, int shapeTwo) {
  double sum = 0.0;
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      sum += array[i][a] * array[i][a];
    }
  }
  return sum;
}
