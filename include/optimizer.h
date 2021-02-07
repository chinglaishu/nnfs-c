#ifndef _optimizer_H
#define _optimizer_H
#include "./hyperParameter.h"
#include "./denseLayer.h"

// optimizer_adam
typedef struct optimizer {
  double learningRate;
  double currentLearningRate;
  double decay;
  int iterationCount;
  double epsilon;
  double beta1;
  double beta2;
} Optimizer;

void optimizer_init(Optimizer *optimizer, double learningRate, double decay,
  double epsilon, double beta1, double beta2);

void optimizer_preUpdate(Optimizer *optimizer);

void optimizer_update(Optimizer *optimizer, DenseLayer *denseLayer);

void optimizer_postUpdate(Optimizer *optimizer);

#endif
