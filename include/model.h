#ifndef _model_H
#define _model_H
#include "./hyperParameter.h"
#include "./denseLayer.h"
#include "../utils/linklist.h"
#include "./loss.h"
#include "./optimizer.h"
#include "./accuracy.h"

typedef struct model {
  LinkList *layerList;
  LinkList *trainableList;
  Loss *loss;
  Optimizer *optimizer;
  Accuracy *accuracy;
} Model;

void model_init(Model *model, Loss *loss, Optimizer *optimizer, Accuracy *accuracy);

void model_addLayer(Model *model, int *layer, char *type, bool isTrainable);

void model_train(Model *model, double **inputList, int totalInputNum, int *trueList, int epochs, int printEvery);

double **model_forward(Model *model, double **xList, int sampleNum, bool isTraining);

void model_backward(Model *model, double **outputList, int *yList, int shapeOne, int shapeTwo);

#endif
