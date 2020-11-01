#include <stdio.h>
#include "Number.h"
int main(int argc, char const *argv[])
{
    printf("hello \n");
    Number *n = createNum("-12164.467");
    Number *m = createNum("1234.56");
    display(*n);
    printf("%d", compare(*n, *m));
    return 0;
}
