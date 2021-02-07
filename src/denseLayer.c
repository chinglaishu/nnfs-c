#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hyperParameter.h"
#include "../include/denseLayer.h"
#include "../utils/utilfunction.h"
#include "../utils/arraycalculate.h"

void denseLayer_init(DenseLayer *layer, int inputNum, int neuronNum, double id, double wL1, double wL2, double bL1, double bL2) {
  layer->id = id;
  layer->inputNum = inputNum;
  layer->neuronNum = neuronNum;
  layer->weightList = (double **) malloc(inputNum * sizeof(int *)); // int * same size of double *
  layer->biasList = (double **) malloc(1 * sizeof(int *));
  create2DArrayWithNum(layer->weightList, inputNum, neuronNum, 0.01, true);
  create2DArrayWithNum(layer->biasList, 1, neuronNum, 0, false);
  layer->weight_regularizer_L1 = wL1;
  layer->weight_regularizer_L2 = wL2;
  layer->bias_regularizer_L1 = bL1;
  layer->bias_regularizer_L2 = bL2;
  denseLayer_initForOptimizer(layer, inputNum, neuronNum);
};

void denseLayer_otherInit(DenseLayer *layer, int intputListShapeOne) {
  layer->outputList = (double **) malloc(intputListShapeOne * sizeof(int*));
  create2DArrayWithNum(layer->outputList, intputListShapeOne, layer->neuronNum, 0, false);
  layer->dWeightList = (double **) malloc(layer->inputNum * sizeof(int *));
  create2DArrayWithNum(layer->dWeightList, layer->inputNum, layer->neuronNum, 0, false);
  layer->dBiasList = (double **) malloc(1 * sizeof(int *));
  create2DArrayWithNum(layer->dBiasList, 1, layer->neuronNum, 0, false);
  layer->dInputList = (double **) malloc(intputListShapeOne * sizeof(int *));
  create2DArrayWithNum(layer->dInputList, intputListShapeOne, layer->inputNum, 0, false);
}

void denseLayer_initForOptimizer(DenseLayer *layer, int inputNum, int neuronNum) {
  layer->weightMomentumList = (double **) malloc(inputNum * sizeof(int *));
  create2DArrayWithNum(layer->weightMomentumList, inputNum, neuronNum, 0, false);
  layer->weightCacheList = (double **) malloc(inputNum * sizeof(int *));
  create2DArrayWithNum(layer->weightCacheList, inputNum, neuronNum, 0, false);
  layer->biasMomentumList = (double **) malloc(1 * sizeof(int *));
  create2DArrayWithNum(layer->biasMomentumList, 1, neuronNum, 0, false);
  layer->biasCacheList = (double **) malloc(1 * sizeof(int *));
  create2DArrayWithNum(layer->biasCacheList, 1, neuronNum, 0, false);
}

void denseLayer_forward(DenseLayer *layer, double **inputList, int inputShapeOne) {
  layer->inputList = inputList;
  int commonShapeNum = layer->inputNum;
  dotProductAddBias(layer->outputList, layer->inputList, inputShapeOne, commonShapeNum, layer->weightList, commonShapeNum, layer->neuronNum, layer->biasList);
};

// dValueShapeTwo maybe next layer's neuron number
void denseLayer_backward(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo) {
  denseLayer_getDWeightList(layer, dValueList, dValueShapeOne, dValueListShapeTwo);
  denseLayer_getDBiasList(layer, dValueList, dValueShapeOne, dValueListShapeTwo);
  denseLayer_regularization_all(layer, dValueList, dValueShapeOne, dValueListShapeTwo);
  denseLayer_getDInputList(layer, dValueList, dValueShapeOne, dValueListShapeTwo);
}

void denseLayer_regularization_all(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo) {
  denseLayer_regularization(layer->dWeightList, layer->weightList, layer->inputNum, layer->neuronNum, layer->weight_regularizer_L1, layer->weight_regularizer_L2);
  denseLayer_regularization(layer->dBiasList, layer->biasList, 1, layer->neuronNum, layer->bias_regularizer_L1, layer->bias_regularizer_L2);
}

void denseLayer_regularization(double **dValueList, double **valueList, int shapeOne, int shapeTwo, double L1, double L2) {
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      int timeNum = (valueList[i][a] < 0) ? -1 : 1;
      double addL1 = L1 * timeNum;
      double addL2 = 2.0 * L2 * valueList[i][a];
      dValueList[i][a] += addL1 + addL2;
    }
  }
}

void denseLayer_getDWeightList(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo) {
  // inputShape = shape of inputList of layer
  // dvaluelistshape = [dValueShapeOne, output layer neuron num]
  // shape of dvalue list = shape of self output list
  int inputShapeOne = dValueShapeOne;
  int inputShapeTwo = layer->inputNum;
  double **transInputList = (double **) malloc(inputShapeTwo * sizeof(int *));
  create2DArrayWithNum(transInputList, inputShapeTwo, inputShapeOne, 0, false);
  transposeArray(transInputList, layer->inputList, inputShapeTwo, inputShapeOne);
  dotProduct(layer->dWeightList, transInputList, inputShapeTwo, inputShapeOne, dValueList, inputShapeOne, dValueListShapeTwo);
  free2DArray_double(transInputList, inputShapeTwo);
}

void denseLayer_getDBiasList(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo) {
  fill2DArray_double(layer->dBiasList, 1, layer->neuronNum, 0);
  Get2DArraySum(layer->dBiasList, dValueList, dValueShapeOne, dValueListShapeTwo);
}

void denseLayer_getDInputList(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo) {
  double **transWeightList = (double **) malloc(layer->neuronNum * sizeof(int *));
  create2DArrayWithNum(transWeightList, layer->neuronNum, layer->inputNum, 0, false);
  transposeArray(transWeightList, layer->weightList, layer->neuronNum, layer->inputNum);
  dotProduct(layer->dInputList, dValueList, dValueShapeOne, layer->neuronNum, transWeightList, layer->neuronNum, layer->inputNum);
  free2DArray_double(transWeightList, layer->neuronNum);
}
