#include "../../headers/layers/Activation.h"
#include "../../headers/arrays/Arrayc.h"

#include <stdlib.h>

Activation new_Activation(void* (*activation_function)(void *inputs),
                    void* (*activation_prime)(void *input),
                    void* (*forward)(void *layer ,void *inputs),
                    void* (*backward)(void *layer , void* output_gradient, double learning_rate)){

    //on fait appele au contruction de la structure layer 
    //super                
    Layer layer = new_Layer(forward , backward);
    Activation activation = (Activation) calloc(1 , sizeof(Activation_s));
    activation->layer = layer;
    activation->layer->child_layer = activation;
    activation->activation_function = activation_function;
    activation->activation_prime = activation_prime;

    return activation;
}

void* activation_forward(void *activation_layer , void *inputs){
    Activation act_layer = (Activation) activation_layer;
    act_layer->layer->inputs = inputs;
    return act_layer->activation_function(act_layer->layer->inputs);
}


void* activation_backward(void *activation_layer , void *output_gradient , double learning_rate){
    // printf("enter sdhjgjhskdfsd\n");
    Activation act_layer = (Activation) activation_layer;
    // printfArray((Array) act_layer->layer->inputs , True);
    // printf("enter back activation\n");
    Array prime = (Array) act_layer->activation_prime(act_layer->layer->inputs);
    Array result = mulArray(output_gradient , prime);
    freeArray(prime);
    freeArray(output_gradient);
    return result;
}





