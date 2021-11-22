#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

int main(int argc, char **argv)
{
    printf("hello\n");

    union {
        int k;
        char x[4];
        char i[2];
    } *s, a;
    s = &a;

    printf("0x%d\n", s->k);

    s->i[0] = 0x39;
    s->i[1] = 0x38;

    printf("x[0] = 0x%x, x[1] = 0x%x\n", s->x[0], s->x[1]);
    printf("k = 0x%x\n", s->k);

    return 0;
}