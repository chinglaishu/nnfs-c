#ifndef _accuracy_H
#define _accuracy_H
#include "./hyperParameter.h"

// Accuracy_Categorical
typedef struct accuracy {
  double accumulatedSum;
  int accumulatedCount;
} Accuracy;

double accuracy_calculate(Accuracy *accuracy, int *predictList, int *trueList, int arrayLength);

double accuracy_calculate_accumulated(Accuracy *accuracy);

void accuracy_newPass(Accuracy *accuracy);

#endif
