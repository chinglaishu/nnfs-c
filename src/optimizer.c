#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hyperParameter.h"
#include "../include/denseLayer.h"
#include "../utils/utilfunction.h"
#include "../utils/arraycalculate.h"
#include "../include/optimizer.h"
#include <math.h>

void optimizer_init(Optimizer *optimizer, double learningRate, double decay,
  double epsilon, double beta1, double beta2) {
  optimizer->learningRate = learningRate;
  optimizer->decay = decay;
  optimizer->epsilon = epsilon;
  optimizer->beta1 = beta1;
  optimizer->beta2 = beta2;
}

void optimizer_preUpdate(Optimizer *optimizer) {
  optimizer->currentLearningRate = optimizer->learningRate *
    (1 / (1 + optimizer->decay * optimizer->iterationCount));
}

void optimizer_update(Optimizer *optimizer, DenseLayer *denseLayer) {
  optimizer_calculate_momentum(optimizer->beta1, denseLayer->weightMomentumList,
    denseLayer->dWeightList, denseLayer->inputNum, denseLayer->neuronNum);
  optimizer_calculate_momentum(optimizer->beta1, denseLayer->biasMomentumList,
    denseLayer->dBiasList, 1, denseLayer->neuronNum);

  double **weightMomentumCorrect = (double **) malloc(denseLayer->inputNum * sizeof(int *));
  optimizer_calculate_correct(optimizer->beta1, optimizer->iterationCount, weightMomentumCorrect,
    denseLayer->weightMomentumList, denseLayer->inputNum, denseLayer->neuronNum);
  double **biasMomentumCorrect = (double **) malloc(1 * sizeof(int *));
  optimizer_calculate_correct(optimizer->beta1, optimizer->iterationCount, biasMomentumCorrect,
    denseLayer->biasMomentumList, 1, denseLayer->neuronNum);

  // print2DArray_double(weightMomentumCorrect, denseLayer->inputNum, denseLayer->neuronNum);

  optimizer_calculate_cache(optimizer->beta2, denseLayer->weightCacheList,
    denseLayer->dWeightList, denseLayer->inputNum, denseLayer->neuronNum);
  optimizer_calculate_cache(optimizer->beta2, denseLayer->biasCacheList,
    denseLayer->dBiasList, 1, denseLayer->neuronNum);

  double **weightCacheCorrect = (double **) malloc(denseLayer->inputNum * sizeof(int *));
  optimizer_calculate_correct(optimizer->beta2, optimizer->iterationCount,
    weightCacheCorrect, denseLayer->weightCacheList,
    denseLayer->inputNum, denseLayer->neuronNum);
  double **biasCacheCorrect = (double **) malloc(1 * sizeof(int *));
  optimizer_calculate_correct(optimizer->beta2, optimizer->iterationCount,
    biasCacheCorrect, denseLayer->biasCacheList,
    1, denseLayer->neuronNum);

  // print2DArray_double(weightMomentumCorrect, denseLayer->inputNum, denseLayer->neuronNum);
  // print2DArray_double(weightCacheCorrect, denseLayer->inputNum, denseLayer->neuronNum);

  optimizer_updateValue(optimizer->currentLearningRate, optimizer->epsilon,
    denseLayer->weightList, weightMomentumCorrect, weightCacheCorrect,
    denseLayer->inputNum, denseLayer->neuronNum);
  optimizer_updateValue(optimizer->currentLearningRate, optimizer->epsilon,
    denseLayer->biasList, biasMomentumCorrect, biasCacheCorrect,
    1, denseLayer->neuronNum);

  free2DArray_double(weightMomentumCorrect, denseLayer->inputNum);
  free2DArray_double(biasMomentumCorrect, 1);

  free2DArray_double(weightCacheCorrect, denseLayer->inputNum);
  free2DArray_double(biasCacheCorrect, 1);
}

void optimizer_postUpdate(Optimizer *optimizer) {
  optimizer->iterationCount = optimizer->iterationCount + 1;
}

void optimizer_updateValue(double currentLearningRate, double epsilon, double **valueList, double **correctMomentumList, double **correctCacheList, int shapeOne, int shapeTwo) {
  // printf("rate: %f, correct momentum: %f, correct cache: %f\n", -currentLearningRate, correctMomentumList[0][0], sqrt(correctCacheList[0][0]));
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      double addValue = (-currentLearningRate * correctMomentumList[i][a]) /
        (sqrt(correctCacheList[i][a]) + epsilon);
      if (i == 0 && a == 0) {
        printf("value: %f, addValue: %f\n", valueList[i][a], addValue);
      }
      valueList[i][a] = valueList[i][a] + addValue;
      if (i == 0 && a == 0) {
        printf("aftervalue: %f\n", valueList[i][a]);
      }
    }
  }
}

void optimizer_calculate_momentum(double beta1, double **momentumList, double **dValueList, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      momentumList[i][a] = beta1 * momentumList[i][a] + 
        (1 - beta1) * dValueList[i][a];
    }
  }
}

void optimizer_calculate_cache(double beta2, double **cacheList, double **dValueList, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    for (int a = 0 ; a < shapeTwo ; a++) {
      cacheList[i][a] = beta2 * cacheList[i][a] +
        (1 - beta2) * dValueList[i][a] * dValueList[i][a];
    }
  }
}

void optimizer_calculate_correct(double betaValue, int iterationCount, double **newArray, double **momentumOrCacheList, int shapeOne, int shapeTwo) {
  for (int i = 0 ; i < shapeOne ; i++) {
    newArray[i] = (double *) malloc(shapeTwo * sizeof(double));
    for (int a = 0 ; a < shapeTwo ; a++) {
      newArray[i][a] = momentumOrCacheList[i][a] / (1 - pow(betaValue, iterationCount + 1));
    }
  }
}
