#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double getdoubleRandomNum(double maxNum) {
  return ((double)rand())/RAND_MAX * maxNum;
}

int getIntRandomNum(int maxNum) {
  return rand() % maxNum;
}

void create2DArrayWithNum(double **array, int shapeOne, int shapeTwo, double useNum, bool isRandom) {
  // int **arr = (int **) malloc(shapeOne * sizeof(int *));
  for (int i = 0 ; i < shapeOne ; i++) {
    array[i] = (double *) malloc(shapeTwo * sizeof(double));
    for (int a = 0 ; a < shapeTwo ; a++) {
      double putNum = (isRandom) ? getdoubleRandomNum(useNum) : useNum;
      array[i][a] = putNum;
    }
  }
}

void create1DArrayWithNum_int(int *array, int arrayLength, int useNum, bool isRandom) {
  for (int i = 0 ; i < arrayLength ; i++) {
    int putNum = (isRandom) ? getIntRandomNum(useNum) : useNum;
    array[i] = putNum;
  }
}

void fill2DArrayAsRandom(int **array, int shapeOne, int shapeTwo, int maxNum) {
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      array[i][a] = rand() % maxNum;
    }
  }
}

void printArray(int *array, int arrayLength) {
  printf("start print array with length: %d\n", arrayLength);
  for (int i = 0 ; i < arrayLength ; i++) {
    printf("%d: %d\n", i, array[i]);
  }
  printf("print array end\n");
}

void print2DArray_int(int **array, int shapeOne, int shapeTwo) {
  printf("start print array with shape: [%d][%d]", shapeOne, shapeTwo);
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      printf("[%d][%d]: %d", i, a, array[i][a]);
    }
  }
  printf("print array end");
}

void print2DArray_double(double **array, int shapeOne, int shapeTwo) {
  printf("start print array with shape: [%d][%d]\n", shapeOne, shapeTwo);
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      printf("[%d][%d]: %f\n", i, a, array[i][a]);
    }
  }
  printf("print array end\n");
}

void conditionMalloc2DArray_double(double **array, int arrayLength) {
  printf("array: %p\n", array);
  if (array == NULL) {
    array = (double **) malloc(arrayLength * sizeof(int *));
    if (array == NULL) {
      printf("2D array double malloc fail\n");
    }
  }
}

void conditionMalloc2DArray_int(int **array, int arrayLength) {
  if (array == NULL) {
    array = (int **) malloc(arrayLength * sizeof(int *));
    if (array == NULL) {
      printf("2D array int malloc fail\n");
    }
  }
}

void conditionMalloc1DArray_double(double *array, int arrayLength) {
  if (array == NULL) {
    array = (double *) malloc(arrayLength * sizeof(double));
    if (array == NULL) {
      printf("1D array double malloc fail\n");
    }
  }
}

void conditionMalloc1DArray_int(int *array, int arrayLength) {
  if (array == NULL) {
    array = (int *) malloc(arrayLength * sizeof(int));
    if (array == NULL) {
      printf("1D array int malloc fail\n");
    }
  }
}

void printArray_double(double *array, int arrayLength) {
  printf("start print array with length: %d\n", arrayLength);
  for (int i = 0 ; i < arrayLength ; i++) {
    printf("%d: %f\n", i, array[i]);
  }
  printf("print array end\n");
}
