//#include "../include/swap.h"

void inline swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}