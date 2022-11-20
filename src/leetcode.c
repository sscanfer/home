/*
 * LeetCode input and output of 2d array
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE_MAX 10000
#define SIZE_MIN 1

int **UserFunc(int **input, int inputSize, int *inputColSize, int *retSize, int **retColSize)
{
    return 0;
}

int main(int argc, char **argv)
{
    int inputSize;
    if (scanf("%d", &inputSize) != 1 || inputSize > SIZE_MAX || inputSize < SIZE_MIN) {
        return -1;
    }

    int *inputColSize = (int*)malloc(inputSize * sizeof(int));
    if (inputColSize == NULL) {
        return -2;
    }
    for (int i = 0; i < inputSize; i++) {
        if (scanf("%d", &inputColSize[i]) != 1) {
            free(inputColSize);
            return -1;
        }
    }

    int **input = (int**)malloc(inputSize * sizeof(int*));
    if (input == NULL) {
        return -2;
    }
    for (int i = 0; i < inputSize; i++) {
        input[i] = (int*)malloc(inputColSize[i] * sizeof(int));
        if (input[i] == NULL) {
            free(inputColSize);
            free(input);
            return -2;
        }
    }
    for (int i = 0; i < inputSize; i++) {
        for (int j = 0; j < inputColSize[i]; j++) {
            if (scanf("%d", &input[i][j]) != 1) {
                for (int k = 0; k < inputSize; k++) {
                    free(input[k]);
                }
                free(input);
                free(inputColSize);
                return -1;
            }
        }
    }

    // call user function
    int   retSize;
    int  *retColSize;
    int **ret = UserFunc(input, inputSize, inputColSize, &retSize, &retColSize);
    if (ret != NULL && retSize > 0) {
        // do something and free return memory
        for (int i = 0; i < retSize; i++) {
            free(ret[i]);
        }
        free(ret);
        free(retColSize);
    }

    // free input memory
    for(int i = 0; i < inputSize; i++) {
        free(input[i]);
    }
    free(input);
    free(inputColSize);

    return 0;
}