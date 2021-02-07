#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/activation.h"
#include "../include/hyperParameter.h"
#include "../utils/utilfunction.h"
#include "../utils/arraycalculate.h"
#include <limits.h>

void activation_ReLu_init(Activation_ReLu *activation_ReLu, int inputShapeOne, int inputShapeTwo, int dValueListShapeOne, int dValueListShapeTwo) {
  activation_ReLu->outputList = (double **) malloc(inputShapeOne * sizeof(int *));
  create2DArrayWithNum(activation_ReLu->outputList, inputShapeOne, inputShapeTwo, 0, false);
  activation_ReLu->dInputList = (double **) malloc(dValueListShapeOne * sizeof(int *));
  create2DArrayWithNum(activation_ReLu->dInputList, dValueListShapeOne, dValueListShapeTwo, 0, false);
}

void activation_ReLu_forward(Activation_ReLu *activation_ReLu, double **inputList, int inputShapeOne, int inputShapeTwo) {
  activation_ReLu->inputList = inputList;
  create2DArrayWithLimitValue(activation_ReLu->outputList, inputList, inputShapeOne, inputShapeTwo, 0.0, LONG_MAX);
}

void activation_ReLu_backward(Activation_ReLu *activation_ReLu, double **dValueList, int dValueListShapeOne, int dValueListShapeTwo) {
  reluBackward(activation_ReLu->dInputList, dValueList, dValueListShapeOne, dValueListShapeTwo);
}

void reluBackward(double **dInputList, double **dValueList, int dValueShapeOne, int dValueListShapeTwo) {
  for (int i = 0 ; i < dValueShapeOne ; i++) {
    for (int a = 0 ; a < dValueListShapeTwo ; a++) {
      double value = dValueList[i][a];
      dInputList[i][a] = (value <= 0) ? 0 : value;
    }
  }
}

void activation_Softmax_init(Activation_Softmax *activation_Softmax, int inputShapeOne, int inputShapeTwo, int dValueListShapeOne, int dValueListShapeTwo) {
  activation_Softmax->outputList = (double **) malloc(inputShapeOne * sizeof(int *));
  create2DArrayWithNum(activation_Softmax->outputList, inputShapeOne, inputShapeTwo, 0, false);
}

void activation_Softmax_forward(Activation_Softmax *activation_Softmax, double **inputList, int inputShapeOne, int inputShapeTwo) {
  allBecomeMinusMaxofRow(inputList, activation_Softmax->outputList, inputShapeOne, inputShapeTwo);
  get2DArrayExp(activation_Softmax->outputList, inputShapeOne, inputShapeTwo);
  getProbability(activation_Softmax->outputList, inputShapeOne, inputShapeTwo);
}

void activation_Softmax_backward(Activation_Softmax *activation_Softmax, double **dValueList, int dValueListShapeTwo) {

}

// predict base on self outputList
void activation_Softmax_predict(Activation_Softmax *activation_Softmax, int *predictList, int shapeOne, int shapeTwo) {
  getMaxValueIndexList(activation_Softmax->outputList, predictList, shapeOne, shapeTwo);
}
