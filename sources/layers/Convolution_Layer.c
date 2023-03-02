#include <stdlib.h>
#include "../../headers/utilitaire/Shapes.h"
#include "../../headers/layers/Convolution_Layer.h"


Convolution_Layer new_Convolution_Layer(Shapes input_shapes , Shapes kernel_shapes , int depth , 
                                        void* (*forward)(void *layer ,void *inputs),
                                        void* (*backward)(void *layer , void* output_gradient, double learning_rate)){
    
    //contruction de la structure layer 
    //super                
    Layer layer = new_Layer(forward , backward);
    Convolution_Layer convolution = calloc(1 , sizeof(Convolution_Layer_s));
    convolution->layer = layer;
    convolution->layer->child_layer = convolution;

    convolution->input_shapes = input_shapes;
    convolution->kernel_shapes = kernel_shapes;
    convolution->depth = depth;
    int output_height = input_shapes.height - kernel_shapes.height + 1;
    int output_width = input_shapes.width - kernel_shapes.width + 1;
    convolution->output_shapes = (Shapes){input_shapes.depth , output_height, output_width};

    int i = 0 , j = 0;
    convolution->biases = (Array*) calloc(depth , sizeof(Array));

    for (i = 0; i < depth; i++)
    {
        convolution->biases[i] = randomArray(output_height , output_width , 0 , 255);
    }

    convolution->kernels = (Array**) calloc(input_shapes.depth , sizeof(Array*));
    for (j = 0; j < input_shapes.depth; j++)
    {
        convolution->kernels[j] = (Array*) calloc(depth , sizeof(Array));
    }
    
    for (i = 0; i < input_shapes.depth; i++)
    {
        for (j = 0; j < depth; j++)
        {
            convolution->kernels[i][j] = randomArray(kernel_shapes.height , kernel_shapes.width , 0 , 255);
        }
    }
    
    return convolution;
}

void* convolution_forward(void *layer , void *inputs){

}

void* convolution_backward(void *layer , void *output_gradient , double learning_rate){

}


Array rotate_kernel(Array kernel){

}

Array cross_corolation(Array input , Array kernel){

}

Array valid_convolution(Array input , Array kernel){

}


Array full_convolotion(Array  input , Array kernel){

}

void free_convolution_layer(Convolution_Layer convolition_layer){
    int i = 0 , j = 0;
    for (i = 0; i < convolition_layer->depth; i++)
    {
        freeArray(convolition_layer->biases[i]);
    }

    for (i = 0; i < convolition_layer->input_shapes.depth; i++)
    {
        for (j = 0; j < convolition_layer->depth; j++)
        {
            freeArray(convolition_layer->kernels[i][j]);
        }
        
    }

    free(convolition_layer->layer);
    free(convolition_layer);
}