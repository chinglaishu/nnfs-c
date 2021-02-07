#ifndef _hyperParameter_H
#define _hyperParameter_H

#define batchSize 128
#define dataSize 784
// how many x factor, in this case, how many pixel
#define classSize 10

// layer
#define layerNum 3
#define layer1InputNum dataSize
#define layer1NeuronNum 128
#define layer2InputNum layer1NeuronNum
#define layer2NeuronNum 128
#define layer3InputNum layer2NeuronNum
#define layer3NeuronNum classSize

#endif