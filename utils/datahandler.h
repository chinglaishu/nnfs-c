#ifndef __datahandler_H
#define __datahandler_H

void combineDirName(char *newName, char *baseName, char *addName);

int loop2DDir_count(char *dirName);

int loopDir_count(char *dirName);

void loop2DDir(char *dirName, int shapeOne, int useDataSize, double **xList, int *yList);

int loopDir(char *dirName, int recordTotalIndex, int yValue, double *xList, int *yList, int useDataSize);

void swapItem_int(int *array, int index1, int index2);

void swapItem_double(double *array, int index1, int index2);

void shuffleXAndY(double *xList, int *yList, int arrayLength);

#endif
