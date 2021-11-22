#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char a;
    char b;
} char_st;

typedef struct {
    int a;
    int b;
} int_st;

void func1(char_st *p)
{
    p->a = 'a';
    p->b = 'b';
    printf("a = %c, b = %c\n", p->a, p->b);
}

void func2(int_st *p)
{
    p->a = 'a';
    p->b = 'b';
    printf("a + b = %d\n", p->a + p->b);
}

int main(int argc, char **argv)
{
    char_st st1;
    int_st st2;

    _Generic(&st1, char_st* : func1, int_st* : func2)(&st1);
    _Generic(&st2, char_st* : func1, int_st* : func2)(&st2);

    return 0;
}