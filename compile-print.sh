#!/bin/bash

gcc -w ./utils/pnghandler.c ./utils/datahandler.c ./utils/utilfunction.c ./utils/linklist.c ./utils/arraycalculate.c ./src/denseLayer.c ./src/activation.c ./src/loss.c ./src/accuracy.c ./src/optimizer.c ./src/model.c ./main.c -lpng -L/usr/local/lib -lz -L/usr/local/lib -lm
./a.out
