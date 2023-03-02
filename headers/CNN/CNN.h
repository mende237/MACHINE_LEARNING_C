#ifndef CNN_H
#define CNN_H
#include "../layers/Layer.h"
#include "../arrays/Arrayc.h"



void train(Layer *Network , int network_len,
        double (*losse)(Array y_pred , Array y_true) , 
        Array (*losse_prime)(Array y_pred , Array y_true), 
        int nbr_epoch , Array *X_train , Array *Y_train , double learning_rate, int data_size);


Array predict(Layer *network , int network_len,  Array input);
#endif