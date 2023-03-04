#ifndef LAYER_H
#define LAYER_H


typedef struct Layer
{
    void *inputs;
    void *output;

    void *child_layer;

    void* (*forward)(void *layer , void *inputs);
    void* (*backward)(void *layer , void* output_gradient, double learning_rate);
}Layer_s , *Layer;


Layer new_Layer(void* (*forward)(void *layer ,void *inputs),
                void* (*backward)(void *layer , void* output_gradient, double learning_rate));

#endif