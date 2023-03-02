CC = gcc
#	+ parametres du compilateur
CFLAGS = -W -Wall -lm
BASE_DIR_HEADER=../headers
BASE_DIR_SOURCE=../sources
BASE_DIR=..
COMPILED_LIST=test.o base.o Arrayc.o Dense.o Layer.o utilitaire.o Softmax.o losses.o Activations.o Activation.o CNN.o read_data.o Convolution_Layer.o


test: $(COMPILED_LIST)
	$(CC) -c $(BASE_DIR)/test.c -o test.o $(CFLAGS)
	$(CC)  $(COMPILED_LIST) -lm -o $(BASE_DIR)/test $(CFLAGS)

Convolution_Layer.o:$(BASE_DIR_SOURCE)/layers/Convolution_Layer.c
	$(CC) -c $(BASE_DIR_SOURCE)/layers/Convolution_Layer.c Convolution_Layer.o $(CFLAGS)

read_data.o: $(BASE_DIR_SOURCE)/utilitaire/read_data.c Arrayc.o
	$(CC) -c $(BASE_DIR_SOURCE)/utilitaire/read_data.c read_data.o $(CFLAGS)

CNN.o: $(BASE_DIR_SOURCE)/CNN/CNN.c Arrayc.o
	$(CC) -c $(BASE_DIR_SOURCE)/CNN/CNN.c CNN.o $(CFLAGS)

Activations.o: $(BASE_DIR_SOURCE)/layers/Activations.c Arrayc.o utilitaire.o
	$(CC) -c $(BASE_DIR_SOURCE)/layers/Activations.c Activations.o $(CFLAGS)

Activation.o: $(BASE_DIR_SOURCE)/layers/Activation.c 
	$(CC) -c $(BASE_DIR_SOURCE)/layers/Activation.c Activation.o $(CFLAGS)

losses.o: $(BASE_DIR_SOURCE)/losses/losses.c utilitaire.o
	$(CC) -c $(BASE_DIR_SOURCE)/losses/losses.c losses.o $(CFLAGS)

Softmax.o: $(BASE_DIR_SOURCE)/layers/Softmax.c Arrayc.o utilitaire.o
	$(CC) -c $(BASE_DIR_SOURCE)/layers/Softmax.c Softmax.o $(CFLAGS)

utilitaire.o: $(BASE_DIR_SOURCE)/utilitaire/utilitaire.c 
	$(CC) -c $(BASE_DIR_SOURCE)/utilitaire/utilitaire.c utilitaire.o $(CFLAGS)


Arrayc.o: $(BASE_DIR_SOURCE)/arrays/Arrayc.c  $(BASE_DIR_HEADER)/layers/Dense.h base.o 
	$(CC) -c $(BASE_DIR_SOURCE)/arrays/Arrayc.c -o Arrayc.o $(CFLAGS)

base.o: $(BASE_DIR_SOURCE)/arrays/base.c
	$(CC) -c $(BASE_DIR_SOURCE)/arrays/base.c -o base.o $(CFLAGS)

Dense.o: $(BASE_DIR_SOURCE)/layers/Dense.c  Arrayc.o Layer.o
	$(CC) -c $(BASE_DIR_SOURCE)/layers/Dense.c -o Dense.o $(CFLAGS)

Layer.o: $(BASE_DIR_SOURCE)/layers/Layer.c $(BASE_DIR_HEADER)/layers/Layer.h
	$(CC) -c $(BASE_DIR_SOURCE)/layers/Layer.c -o Layer.o $(CFLAGS)


run:test
	$(BASE_DIR)/./test
