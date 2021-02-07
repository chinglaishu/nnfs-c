#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "./include/denseLayer.h"
#include "./utils/utilfunction.h"
#include "./include/hyperParameter.h"
#include "./include/activation.h"
#include "./include/loss.h"
#include "./include/accuracy.h"
#include "./include/optimizer.h"
#include "./include/model.h"
#include "./utils/pnghandler.h"
#include "./utils/datahandler.h"

int main() {
  printf("%s\n", "start");
  srand((unsigned int)time(NULL));

  char *trainDirName = "fashion_mnist_images/train";
  char *testDirName = "fashion_mnist_images/test";

  int totalTrain = loop2DDir_count(trainDirName);
  int totalTest = loop2DDir_count(testDirName);
  int totalPixel = getTotalPixel("0000.png");
  // int classSize = loopDir_count(trainDirName);
  // printf("total train: %d, test: %d, pixel: %d, classSize: %d\n", totalTrain, totalTest, totalPixel, classSize);

  double **xTrainList = (double **) malloc(totalTrain * sizeof(int *));
  int *yTrainList = (int **) malloc(totalTrain * sizeof(int *));
  loop2DDir(trainDirName, totalTrain, totalPixel, xTrainList, yTrainList);

  double **xTestList = (double **) malloc(totalTest * sizeof(int *));
  int *yTestList = (int **) malloc(totalTest * sizeof(int *));
  loop2DDir(testDirName, totalTest, totalPixel, xTestList, yTestList);

  shuffleXAndY(xTrainList, yTrainList, totalTrain);
  printArray_double(xTrainList[0], totalPixel);

  DenseLayer layer1;
  denseLayer_init(&layer1, layer1InputNum, layer1NeuronNum, 1, 0, 0, 0, 0);
  denseLayer_otherInit(&layer1, batchSize);

  Activation_ReLu activation_ReLu1;
  activation_ReLu_init(&activation_ReLu1, batchSize, layer1NeuronNum, batchSize, layer1NeuronNum);

  DenseLayer layer2;
  denseLayer_init(&layer2, layer2InputNum, layer2NeuronNum, 2, 0, 0, 0, 0);
  denseLayer_otherInit(&layer2, batchSize);

  Activation_ReLu activation_ReLu2;
  activation_ReLu_init(&activation_ReLu2, batchSize, layer2NeuronNum, batchSize, layer2NeuronNum);

  DenseLayer layer3;
  denseLayer_init(&layer3, layer3InputNum, layer3NeuronNum, 3, 0, 0, 0, 0);
  denseLayer_otherInit(&layer3, batchSize);

  Activation_Softmax activation_Softmax;
  activation_Softmax_init(&activation_Softmax, batchSize, layer3NeuronNum, batchSize, layer3NeuronNum);

  int *predictList = (int *) malloc(batchSize * sizeof(int));
  activation_Softmax_predict(&activation_Softmax, predictList, batchSize, layer3NeuronNum);

  Loss loss;
  loss_init(&loss, batchSize, layer3NeuronNum);

  Accuracy accuracy;

  Optimizer optimizer;
  optimizer_init(&optimizer, 0.001, 1e-3, 1e-7, 0.9, 0.999);

  Model model;
  model_init(&model, &loss, &optimizer, &accuracy);
  model_addLayer(&model, &layer1, "denseLayer", true);
  model_addLayer(&model, &activation_ReLu1, "activation_ReLu", false);
  model_addLayer(&model, &layer2, "denseLayer", true);
  model_addLayer(&model, &activation_ReLu2, "activation_ReLu", false);
  model_addLayer(&model, &layer3, "denseLayer", true);
  model_addLayer(&model, &activation_Softmax, "activation_Softmax", false);

  printf("start train\n");

  model_train(&model, xTrainList, totalTrain, yTrainList, 10, 1);

  printf("%s\n", "end");
  return 0;
}
