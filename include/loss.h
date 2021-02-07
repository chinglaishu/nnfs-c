#ifndef _loss_H
#define _loss_H
#include "./hyperParameter.h"
#include "./denseLayer.h"
#include "../utils/linklist.h"

// Loss_CategoricalCrossentropy
typedef struct loss {
  int id;
  double accumulatedSum;
  int accumulatedCount;
  DenseLayer *trainableLayer[layerNum];
  double **dInputList; // next layer's dvalue, same shape as inputList
} Loss;

void loss_init(Loss *loss, int shapeOne, int shapeTwo);

// predictionList produce by softmax
double loss_forward(double **predictionList, int *trueList, int shapeOne, int shapeTwo);

// dvaluelist = prediction list as it is last function to loss
double loss_backward(Loss *loss, double **dValueList, int *trueList, int shapeOne, int shapeTwo);

double loss_getRegularization(LinkList *trainableList);

double loss_calculate(Loss *loss, double **predictionList, int *trueList, int shapeOne, int shapeTwo);

double loss_calculate_accumulated(Loss *loss);

double loss_newPass(Loss *loss);

void combineLossAndSoftmax_backward(Loss *loss, double **dValueList, int *trueList, int shapeOne, int shapeTwo);

#endif
