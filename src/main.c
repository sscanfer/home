#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

int main(int argc, char **argv)
{
    printf("hello\n");

    printf("%u\n", strlen("这是一个中文字符串"));

    return 0;
}