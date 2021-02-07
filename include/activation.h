#ifndef _activation_H
#define _activation_H

typedef struct activation_ReLu {
  double **inputList;
  double **outputList;
  double **dInputList;
} Activation_ReLu;

typedef struct activation_Softmax {
  double **inputList;
  double **outputList;
  double **dInputList;
} Activation_Softmax;


void activation_ReLu_init(Activation_ReLu *activation_ReLu, int inputShapeOne, int inputShapeTwo, int dValueListShapeOne, int dValueListShapeTwo);

void activation_ReLu_forward(Activation_ReLu *activation_ReLu, double **inputList, int inputShapeOne, int inputShapeTwo);

void activation_ReLu_backward(Activation_ReLu *activation_ReLu, double **dValueList, int dValueListShapeOne, int dValueListShapeTwo);

void activation_Softmax_init(Activation_Softmax *activation_Softmax, int inputShapeOne, int inputShapeTwo, int dValueListShapeOne, int dValueListShapeTwo);

void activation_Softmax_forward(Activation_Softmax *activation_Softmax, double **inputList, int inputShapeOne, int inputShapeTwo);

void activation_Softmax_backward(Activation_Softmax *activation_Softmax, double **dValueList, int dValueListShapeTwo);

void activation_Softmax_predict(Activation_Softmax *activation_Softmax, int *predictList, int shapeOne, int shapeTwo);

#endif
