#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hyperParameter.h"
#include "../include/denseLayer.h"
#include "../utils/utilfunction.h"
#include "../utils/arraycalculate.h"
#include "../include/loss.h"
#include "../utils/linklist.h"

void loss_init(Loss *loss, int shapeOne, int shapeTwo) {
  loss->dInputList = (double **) malloc(shapeOne * sizeof(int *));
  create2DArrayWithNum(loss->dInputList, shapeOne, shapeTwo, 0, false);
}

// return sum of loss, shapeOne = sample size, shapeTwo = neuron num of output layer
double loss_forward(double **predictionList, int *trueList, int shapeOne, int shapeTwo) {
  int sampleNum = shapeOne;
  double *correctConfidenceList = (double *) malloc(sampleNum * sizeof(double));
  getArrayByIndex(predictionList, trueList, correctConfidenceList, sampleNum);
  double smallNum = 1e-7;
  limitValueOnArray(correctConfidenceList, sampleNum, smallNum, 1 - smallNum);
  getArrayTimeSomething(1, correctConfidenceList, sampleNum, -1);
  double sum = getSumOfRow(correctConfidenceList, sampleNum);
  free(correctConfidenceList);
  return sum;
}

// dvaluelist = prediction list as it is last function to loss
double loss_backward(Loss *loss, double **dValueList, int *trueList, int shapeOne, int shapeTwo) {
}          

double loss_getRegularization(LinkList *trainableList) {
  double regularizationLoss = 0;
  Node *ptr = trainableList->startNode;
  while (ptr != NULL) {
    DenseLayer *layer = ptr->data;
    regularizationLoss += layer->weight_regularizer_L1
      * getAbsSumOf2DArray_double(layer->weightList, layer->inputNum, layer->neuronNum);
    regularizationLoss += layer->weight_regularizer_L2
      * getSquareSumOf2DArray_double(layer->weightList, layer->inputNum, layer->neuronNum);
    regularizationLoss += layer->bias_regularizer_L1
      * getAbsSumOf2DArray_double(layer->biasList, 1, layer->neuronNum);
    regularizationLoss += layer->bias_regularizer_L2
      *getSquareSumOf2DArray_double(layer->biasList, 1, layer->neuronNum);
    ptr = ptr->next;
  }
  return regularizationLoss;
}

double loss_calculate(Loss *loss, double **predictionList, int *trueList, int shapeOne, int shapeTwo) {
  double lossSum = loss_forward(predictionList, trueList, shapeOne, shapeTwo);
  double lossMean = lossSum / shapeOne;
  loss->accumulatedSum = loss->accumulatedSum + lossSum;
  loss->accumulatedCount = loss->accumulatedCount + shapeOne;
  return lossMean;
}

double loss_calculate_accumulated(Loss *loss) {
  double dataLoss = loss->accumulatedSum / loss->accumulatedCount;
  return dataLoss;
}

double loss_newPass(Loss *loss) {
  loss->accumulatedSum = 0;
  loss->accumulatedCount = 0;
}

void combineLossAndSoftmax_backward(Loss *loss, double **dValueList, int *trueList, int shapeOne, int shapeTwo) {
  int sampleNum = shapeOne;
  for (int i = 0 ; i < shapeOne ; i++) {
    int trueIndex = trueList[i];
    for (int a = 0 ; a < shapeTwo ; a++) {
      double value = dValueList[i][a];
      double useValue = (a == trueIndex) ? value - 1 : value;
      loss->dInputList[i][a] = useValue / sampleNum;
    }
  }
}
