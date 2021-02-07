#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hyperParameter.h"
#include "../include/denseLayer.h"
#include "../utils/utilfunction.h"
#include "../include/activation.h"
#include "../utils/arraycalculate.h"
#include "../include/loss.h"
#include "../include/accuracy.h"
#include "../include/model.h"
#include "../include/optimizer.h"
#include "../utils/linklist.h"

void model_init(Model *model, Loss *loss, Optimizer *optimizer, Accuracy *accuracy) {
  LinkList *layerList = malloc(sizeof(LinkList));
  layerList->startNode = NULL;
  LinkList *trainableList = malloc(sizeof(LinkList));
  trainableList->startNode = NULL;
  model->layerList = layerList;
  model->trainableList = trainableList;
  model->loss = loss;
  model->optimizer = optimizer;
  model->accuracy = accuracy;
}

void model_addLayer(Model *model, int *layer, char *type, bool isTrainable) {
  linkList_push(model->layerList, layer, type);
  if (isTrainable) {
    linkList_push(model->trainableList, layer, type);
  }
}

void model_train(Model *model, double **inputList, int totalInputNum, int *trueList, int epochs, int printEvery) {
  for (int i = 0 ; i < epochs ; i++) {
    loss_newPass(model->loss);
    accuracy_newPass(model->accuracy);
    for (int a = 0 ; a < totalInputNum ; a+=batchSize) {
      int startIndex = a;
      int addIndex = a + batchSize;
      int endIndex = (addIndex > totalInputNum) ? totalInputNum : addIndex;
      int sampleNum = endIndex - startIndex;
      int outputLayerNeuronNum = layer3NeuronNum;
      double **xList = (double **) malloc(sampleNum * sizeof(int *));
      slice2DArray_double(inputList, xList, startIndex, endIndex, dataSize);
      
      int *yList = (int *) malloc(sampleNum * sizeof(int));
      sliceArray_int(trueList, yList, startIndex, endIndex);
      double **outputList = model_forward(model, xList, sampleNum, true);

      double lossMean = loss_calculate(model->loss, outputList, yList, sampleNum, outputLayerNeuronNum);
      double regularizationLoss = loss_getRegularization(model->trainableList);
      double totalLoss = lossMean + regularizationLoss;
      double *predictList = (double *) malloc(sampleNum * sizeof(double));
      getPredictOfLastActivationLayer(model, predictList, sampleNum, outputLayerNeuronNum);
      double accuracyValue = accuracy_calculate(model->accuracy, predictList, yList, sampleNum);
      printf("step: %d\n", a);
      printf("Loss mean: %f, regularization: %f, total: %f\n", lossMean, regularizationLoss, totalLoss);

      model_backward(model, outputList, yList, sampleNum, outputLayerNeuronNum);
      optimizer_preUpdate(model->optimizer);
      model_update_trainableLayer(model);
      optimizer_postUpdate(model->optimizer);

      free2DArray_double(xList, sampleNum);
      free(yList);
    }
    double accumulatedLoss = loss_calculate_accumulated(model->loss);
    double regularizationLoss = loss_getRegularization(model->trainableList);
    double epochLoss = accumulatedLoss;
    double epochAccuracy = accuracy_calculate_accumulated(model->accuracy);
    if (i % printEvery == 0) {
      printf("Epoch: %d, loss: %f, accuracy: %f\n, \
        learning_rate: %f\n",
        i, epochLoss, epochAccuracy, model->optimizer->currentLearningRate);
    }
  }
}

void getPredictOfLastActivationLayer(Model *model, double *predictList, int shapeOne, int shapeTwo) {
  Node *lastItem = linkList_getLastItem(model->layerList);
  char *type = lastItem->type;
  if (strcmp(type, "activation_Softmax") == 0) {
    Activation_Softmax *activation_Softmax = lastItem->data;
    activation_Softmax_predict(activation_Softmax, predictList, shapeOne, shapeTwo);
  } else {
    printf("unknown type at last activation layer: %s\n", type);
  }
}

double **model_forward(Model *model, double **xList, int sampleNum, bool isTraining) {
  Node *ptr = model->layerList->startNode;
  int neuronNum = dataSize;
  double **layerOutputList = xList;
  while (ptr != NULL) {
    char *type = ptr->type;
    // printf("forward type: %s\n", type);
    if (strcmp(type, "denseLayer") == 0) {
      DenseLayer *layer = ptr->data;
      neuronNum = layer->neuronNum;
      denseLayer_forward(layer, layerOutputList, sampleNum);
      layerOutputList = layer->outputList;
    } else if (strcmp(type, "activation_ReLu") == 0) {
      Activation_ReLu *activation_ReLu = ptr->data;
      activation_ReLu_forward(activation_ReLu, layerOutputList, sampleNum, neuronNum);
      layerOutputList = activation_ReLu->outputList;
    } else if (strcmp(type, "activation_Softmax") == 0) {
      Activation_Softmax *activation_Softmax = ptr->data;
      activation_Softmax_forward(activation_Softmax, layerOutputList, sampleNum, neuronNum);
      layerOutputList = activation_Softmax->outputList;
    }
    ptr = ptr->next;
  }
  return layerOutputList;
}

void model_backward(Model *model, double **outputList, int *yList, int shapeOne, int shapeTwo) {
  // shapeOne, shapeTwo of outputList
  int sampleNum = shapeOne;
  combineLossAndSoftmax_backward(model->loss, outputList, yList, shapeOne, shapeTwo);
  LinkList reverseLayerList;
  reverseLayerList.startNode = NULL;
  linkListReverse(&reverseLayerList, model->layerList);
  Node *ptr = reverseLayerList.startNode;
  double **dValueList = model->loss->dInputList;
  int neuronNum = shapeTwo;
  while (ptr != NULL) {
    char *type = ptr->type;
    // printf("backward type: %s\n", type);
    if (strcmp(type, "denseLayer") == 0) {
      DenseLayer *layer = ptr->data;
      denseLayer_backward(layer, dValueList, sampleNum, neuronNum);
      neuronNum = layer->inputNum;
      dValueList = layer->dInputList;
    } else if (strcmp(type, "activation_ReLu") == 0) {
      Activation_ReLu *activation_ReLu = ptr->data;
      activation_ReLu_backward(activation_ReLu, dValueList, sampleNum, neuronNum);
      dValueList = activation_ReLu->dInputList;
    } else if (strcmp(type, "activation_Softmax") == 0) {
      // already do on combineLossAndSoftmax_backward
    }
    ptr = ptr->next;
  }
}

void model_update_trainableLayer(Model *model) {
  Node *ptr = model->trainableList->startNode;
  while (ptr != NULL) {
    optimizer_update(model->optimizer, ptr->data);
    ptr = ptr->next;
  }
}
