#ifndef _denseLayer_H
#define _denseLayer_H

typedef struct denseLayer {
  int id;
  int inputNum; // shapeTwo of inputList
  int neuronNum;  // shapeTwo of outputList
  double weight_regularizer_L1;
  double weight_regularizer_L2;
  double bias_regularizer_L1;
  double bias_regularizer_L2;
  double **weightList; // (inputNum, neuronNum)
  double **biasList; // (1, neuronNum)
  double **inputList; // (batchSize, inputNum)
  double **outputList; // (batchSize, neuronNum)
  double **dInputList; // next layer's dvalue, same shape as inputList
  double **dWeightList; // same shape of weightList
  double **dBiasList; // same shape of biasList
  double **weightMomentumList; // same shape of weightList
  double **biasMomentumList; // same shape of biasList
  double **weightCacheList; // same shape of weightList
  double **biasCacheList; // same shape of biasList
} DenseLayer;

void denseLayer_init(DenseLayer *layer, int inputNum, int neuronNum, double id, double wL1, double wL2, double bL1, double bL2);

void denseLayer_otherInit(DenseLayer *layer, int intputListShapeOne);

void denseLayer_forward(DenseLayer *layer, double **inputList, int inputShapeOne);

void denseLayer_backward(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo);

void denseLayer_getDWeightList(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo);

void denseLayer_getDBiasList(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo);

void denseLayer_getDInputList(DenseLayer *layer, double **dValueList, int dValueShapeOne, int dValueListShapeTwo);

#endif
