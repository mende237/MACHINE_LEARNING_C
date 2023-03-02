#include "../../headers/CNN/CNN.h"
#include "../../headers/arrays/Arrayc.h"
#include "../../headers/layers/Dense.h"



void train(Layer *Network , int network_len,
        double (*losse)(Array y_pred , Array y_true) , 
        Array (*losse_prime)(Array y_pred , Array y_true), 
        int nbr_epoch , Array *X_train , Array *Y_train ,double learning_rate, int data_len){
    
     int i = 0 , epoch = 0 , j = 0;
     Array output = NULL;
     Array grad = NULL;
    //  printf("enter\n");
     while (epoch < nbr_epoch)
     {
        double error = 0;
        for (i = 0; i < data_len; i++)
        {
            //forward
            output = predict(Network , network_len , X_train[i]);
            // error
            // printfArray((Array) output , True);
            error += losse(output , Y_train[i]);
            //backward

            // printf("--------------predict--------------------\n");
            // printfArray(output , True);
            // printf("--------------reel--------------------\n");
            // printfArray(Y_train[i] , True);

            grad = losse_prime(output , Y_train[i]);
            for (j = network_len - 1 ; j >= 0; j--)
            {
                
                grad = Network[j]->backward(Network[j]->child_layer , grad , learning_rate);
                if (j != 0){
                    freeArray((Array) Network[j]->inputs);
                }
            }
            // printf("data %d\n" , i);
        }
        // printfArray(((Dense) Network[0]->child_layer)->weights , True);
        
        error /= data_len;
        printf("error => %f\n" , error);
        epoch++;
     }        
}

//je dois faire les free au moment du backward
Array predict(Layer *network , int network_len, Array input){
    Array output = input;
    int i = 0;

    // for (i = 0; i < network_len; i++)
    // {
    //     output = network[i]->forward(network[i] , output);
    // }
    for (i = 0; i < network_len; i++)
    {
        output = network[i]->forward(network[i]->child_layer , output);
    }
    
    return output;
}