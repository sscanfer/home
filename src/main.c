#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

typedef struct {
    int i;
    int j;
    int k;
} TestType;

int main(int argc, char **argv)
{
    TestType temp;
    printf("&temp = 0x%p\n", &temp);
    printf("&(temp.k) = 0x%p\n", &(temp.k));
    printf("&(((TestType *)0)->k) = %d\n", (int)&(((TestType *)0)->k));

    return 0;
}