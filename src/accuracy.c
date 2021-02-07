#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hyperParameter.h"
#include "../include/denseLayer.h"
#include "../utils/utilfunction.h"
#include "../utils/arraycalculate.h"
#include "../include/accuracy.h"

double accuracy_calculate(Accuracy *accuracy, int *predictList, int *trueList, int arrayLength) {
  int sameValueCount = countSameValueOnSameIndex(predictList, trueList, arrayLength);
  double accuracyValue = (double) sameValueCount / (double) arrayLength;
  accuracy->accumulatedSum = accuracy->accumulatedSum + sameValueCount;
  accuracy->accumulatedCount = accuracy->accumulatedCount + arrayLength;
  return accuracyValue;
}

double accuracy_calculate_accumulated(Accuracy *accuracy) {
  double accuracyValue = accuracy->accumulatedSum / accuracy->accumulatedCount;
  return accuracyValue;
}

void accuracy_newPass(Accuracy *accuracy) {
  accuracy->accumulatedSum = 0;
  accuracy->accumulatedCount = 0;
}
