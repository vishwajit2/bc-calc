#include <stdio.h>
#include "Number.h"
int main(int argc, char const *argv[])
{
    printf("Enter two numbers \n");
    char a[50], b[50];
    scanf("%s %s", a, b);
    Number *n = createNum(a);
    Number *m = createNum(b);
    Number *c = add(*n, *m);
    display(*c);
    return 0;
}
