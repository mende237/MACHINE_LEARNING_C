#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "headers/arrays/Arrayc.h"
#include "headers/layers/Dense.h"
#include "headers/layers/softmax.h"
#include "headers/losses/losses.h"
#include "headers/layers/Activation.h"
#include "headers/layers/Activations.h"
#include "headers/CNN/CNN.h"
#include "headers/utilitaire/read_data.h"

// void* toto(){
//     int *a = calloc(3 , sizeof(int));
//     int i = 0;
//     for (i = 0; i < 3; i++)
//     {
//         a[i] = i;
//         printf("%d\n" , a[0]);
//     }
//     printf("----------------------------\n");
//     return a;
// }

void* generate_data(int nbr_sample , int nbr_feature , int nbr_target);

void* generate_data(int nbr_sample , int nbr_feature , int nbr_target){
    int i = 0;
    Array *X_train = calloc(nbr_sample , sizeof(ArrayStr));
    Array *Y_train = calloc(nbr_sample , sizeof(ArrayStr));
    void **data = calloc(2 , sizeof(void*));

    for (i = 0; i < nbr_sample; i++)
    {
        // X_train[i] = valArray(nbr_feature , 1 , 1 * i);
        // if(i%2 == 0){
        //     Y_train[i] = valArray(nbr_target , 1 , 1);
        // }else{
        //     Y_train[i] = valArray(nbr_target , 1 , 0);
        // }

        X_train[i] = randomArray(nbr_feature , 1 , 0 , 10);
        Y_train[i] = randomArray(nbr_target , 1 , 0 , 1);
    }
    data[0] = X_train;
    data[1] = Y_train;
    return data;
}

void free_data(void **data , int nbr_sample){
    if(data != NULL){
        int i = 0;
        Array *X_train = (Array*) data[0];
        Array *Y_train = (Array*) data[1];

        for (i = 0; i < nbr_sample; i++)
        {
            freeArray(X_train[i]);
            freeArray(Y_train[i]);
        }
    }
}



int main(){
    // printf()
    // int  i = 0;
    int nbr_sample = 5;
    int nbr_target = 2;
    int nbr_feature = 4;
    int output_layer = (nbr_target == 2) ? 1 : nbr_target;
    
    // void **data = generate_data(nbr_sample , nbr_feature , nbr_target);
    // Array *X_train = data[0];
    // Array *Y_train = data[1];
    int i = 0;
    void **data = read_csv("/home/dimitri/CNN_C/datasets/data.csv" , nbr_sample , nbr_feature + 1 , nbr_target);
    Array *X_train = data[0];
    Array *Y_train = data[1];
    // for (i = 0; i < 5; i++)
    // {
    //     printfArray(X_train[i] , True);
    //     printfArray(Y_train[i] , True);
    // }
    
    // free_data(data , 5);

    // Array inputs = randomArray(nbr_feature , 1 , 10 , 100);
    // // Array y = randomArray(3 , 1 , 0 , 1);
    int network_len = 4;
    
    Layer Network[] = {
        new_dense(nbr_feature , 2 , -100 , 100 , dense_forward , dense_backward)->layer,
        new_Activation(sigmoid , sigmoid_prime , activation_forward , activation_backward)->layer,
        new_dense(2 , output_layer , -100 , 100 , dense_forward , dense_backward)->layer,
        new_Activation(sigmoid , sigmoid_prime , activation_forward , activation_backward)->layer,
        // new_Softmax(softmax_forward , softmax_backward)->layer
    };


    train(Network , network_len , mse , mse_prime , 10 , X_train , Y_train ,0.1, nbr_sample);



    // Layer s = new_Softmax(softmax_forward , softmax_backward)->layer;
    // Array T = s->forward(s->child_layer , inputs);
    // printfArray(T , True);
    // Array prim = mse_prime(T , randomArray(2 , 1 , 0 , 1));

    // Array a = softmax_backward(s->child_layer , prim , 0.1);
    // printfArray(predict(Network , network_len , inputs) , True);
    // free_data(data , nbr_sample);
    // Array pred = predict(Network , network_len , inputs);
    // Array grad = mse_prime(pred , y);
    // for (i = network_len - 1 ; i <= 0; i--)
    // {
    //     grad = Network[i]->backward(Network[i] , grad , 0.1);
    // }
            
    
    // printfArray(pred , True);

    // printf("%f" , exp2(5));

    // srand(time(NULL));
    // int i = 0;
    // int *a = toto();
    // for (i = 0; i < 3; i++)
    // {
    //     printf("%d\n", a[i]);
    // }

    // Array array = valArray(2 , 2 , 7);
    // Array temp = constOpApplyArray(array , 2 , plus_Array);
    // // constOpApplyArray_r(array , array , 2 , plus_Array);
    // printfArray(temp , True);
    // printfArray(array , True);

    // printfArray(inputs , True);
    // printf("----------------------------------------\n");
    // Array vect = randomArray(3 , 1 , 3 , 7);
    // printfArray(vect , True);
    // printf("----------------------------------------\n");
    // Array temp = vectOpApplyArray(inputs , vect , plus_Array);
    // printfArray(temp , True);
    
    // Dense dense = new_dense(3 , 2 , 0 , 10 , dense_forward , dense_backward);
    // printfArray(dense->weights , True);
    
    // printfArray(dense->layer->forward(dense , inputs) , True);

    // Array temp = dense->layer->forward(dense , inputs);

    // Softmax softmax = new_Softmax(softmax_forward , softmax_backward);

    // Array temp2 = softmax->layer->forward(softmax , temp);

    // Array y_true = randomArray(2 , 1 , 0 , 1);
    // printfArray(temp , True);
    // Activation activation = new_Activation(sigmoid , sigmoid_prime , activation_forward , activation_backward);
    
    // printfArray(activation->layer->forward(activation , temp) ,True);
    // double e = mse(temp2 , y_true);
    // printfArray(temp2 , True);

    // printfArray(y_true , True);
    // printf("eeee %f\n" , e);
    // Array test1 = randomArray(5 , 3 , 0 , 10);
    // Array test2 = randomArray(3 , 2 , 0 , 10);

    // mulArray(test1 , test2);
    // freeArray(test1);
    // freeArray(test2);
    // freeArray(inputs);
    // free_dense_layer(dense);
    // printf("%f" , pow(2 , -1));

    return 0;
}