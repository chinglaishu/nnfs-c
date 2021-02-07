#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

int maxFileLoop = 100;

void combineDirName(char *newName, char *baseName, char *addName) {
  strcpy(newName, baseName);
  strcat(newName, "/");
  strcat(newName, addName);
}

int loop2DDir_count(char *dirName) {
  int totalCount = 0;
  DIR *d;
  struct dirent *dir;
  d = opendir(dirName);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (checkIfValid(dir->d_name)) {
        char useDirName[255];
        combineDirName(useDirName, dirName, dir->d_name);
        int count = loopDir_count(useDirName);
        totalCount += count;
      }
    }
  }
  return totalCount;
}

int loopDir_count(char *dirName) {
  int count = 0;
  DIR *d;
  struct dirent *dir;
  d = opendir(dirName);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (checkIfValid(dir->d_name)) {
        count += 1;
        if (count > maxFileLoop) {
          return count;
        }
      }
    }
  }
  return count;
}

void loop2DDir(char *dirName, int shapeOne, int useDataSize, double **xList, int *yList) {
  int recordTotalIndex = 0;
  int yValue = 0;
  DIR *d;
  struct dirent *dir;
  d = opendir(dirName);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("dir name: %s\n", dir->d_name);
      if (checkIfValid(dir->d_name)) {
        char useDirName[255];
        combineDirName(useDirName, dirName, dir->d_name);
        int recordIndex = loopDir(useDirName, recordTotalIndex, yValue, xList, yList, useDataSize);
        recordTotalIndex += recordIndex;
        yValue += 1;
      }
    }
  }
}

int loopDir(char *dirName, int recordTotalIndex, int yValue, double **xList, int *yList, int useDataSize) {
  int recordIndex = 0;
  DIR *d;
  struct dirent *dir;
  d = opendir(dirName);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (checkIfValid(dir->d_name)) {
        int xIndex = recordTotalIndex + recordIndex;
        xList[recordTotalIndex + recordIndex] = (double *) malloc(useDataSize * sizeof(double));
        char useFileName[60];
        combineDirName(useFileName, dirName, dir->d_name);
        if (recordIndex % 1000 == 0) {
          printf("filename: %s, xIndex: %d\n", useFileName, xIndex);
        }
        getDataFromPng(useFileName, xList[recordTotalIndex + recordIndex]);
        int yIndex = recordTotalIndex + recordIndex;
        yList[yIndex] = yValue;
        recordIndex += 1;
        if (recordIndex > maxFileLoop) {
          return recordIndex;
        }
      }
    }
  }
  return recordIndex;
}

void swapItem_int(int *array, int index1, int index2) {
  int recordItem = array[index1];
  array[index1] = array[index2];
  array[index2] = recordItem;
}

void swapItem_double(double *array, int index1, int index2) {
  double recordItem = array[index1];
  array[index1] = array[index2];
  array[index2] = recordItem;
}

void shuffleXAndY(double *xList, int *yList, int arrayLength) {
  for (int i = 0 ; i < arrayLength; i++) {
    int j = rand() % arrayLength; 
    swapItem_double(xList, i, j);
    swapItem_int(yList, i, j);
  }
}

void shuffle(int *array, int arrayLength) {
  for (int i = 0 ; i < arrayLength; i++) {
    int j = rand() % arrayLength; 
    int aux = array[j];
    array[j] = array[i];
    array[i] = aux;
  }
}
