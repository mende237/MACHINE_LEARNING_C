#include <stdlib.h>
#include "../../headers/utilitaire/Shapes.h"
#include "../../headers/layers/Convolution_Layer.h"
#include "../../headers/arrays/base.h"
#include "../../headers/arrays/Arrayc.h"


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
    Convolution_Layer conv_layer = (Convolution_Layer) layer;
    Array *input_tabs = (Array*) inputs;
    Array *output_tab = calloc(conv_layer->depth , sizeof(Array));
    int i = 0 , j = 0;

    for (j = 0; j < conv_layer->depth; j++)
    {
        Array array_result = calloc(1 , sizeof(ArrayStr));
        array_result->data = create_matrix_double(conv_layer->output_shapes.height , conv_layer->output_shapes.width);
        array_result->nRow = conv_layer->output_shapes.height;
        array_result->nCol = conv_layer->output_shapes.width;
        for (i = 0; i < conv_layer->input_shapes.depth; i++)
        {   
            Array temp = cross_corolation(input_tabs[i] , conv_layer->kernels[i][j]);
            // printfArray(temp , True);
            // printf("enter\n");
            plusArray_r(array_result , temp , array_result);
            freeArray(temp);
        }
        output_tab[j] = array_result;
    }

    return output_tab;
}

void* convolution_backward(void *layer , void *output_gradient , double learning_rate){

}


Array rotate_kernel_180(Array kernel){
    double **result = create_matrix_double(kernel->nRow, kernel->nCol);
    int i, j;

    for (i = 0; i < kernel->nRow; i++)
        for (j = 0; j < kernel->nCol; j++)
            result[i][j] = kernel->data[kernel->nRow - i - 1][kernel->nCol - j - 1];

    Array array = calloc(1 , sizeof(ArrayStr));
    array->nRow = kernel->nRow;
    array->nCol = kernel->nCol;
    array->data = result;
    return array;
}

//convolution sans rotation de filtre
Array cross_corolation(Array input , Array kernel){

    int height_output = input->nRow - kernel->nRow + 1; 
    int width_output = input->nCol - kernel->nCol + 1;

    double **result = create_matrix_double(height_output, width_output);
    int i, j, u, v;

    for (i = 0; i < height_output; i++)
    {
        for (j = 0; j < width_output; j++)
        {
            result[i][j] = 0;
            for (u = 0; u < kernel->nRow; u++)
                for (v = 0; v < kernel->nCol; v++)
                    result[i][j] += input->data[i + u][j + v] * kernel->data[u][v];
        }
    }
    Array array_result = malloc(sizeof(ArrayStr));
    array_result->nRow = height_output;
    array_result->nCol = width_output;
    array_result->data = result;
    // printf("h %d  w %d" , array->nRow , array->nCol);
    return array_result;
}

Array valid_convolution(Array input , Array kernel){
    
}

//
Array full_convolotion_180(Array  input , Array kernel , boolean rotate){

    Array kernel_180 = rotate_kernel_180(kernel);

    freeArray(kernel_180);
   
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