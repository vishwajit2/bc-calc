#include <stdio.h>
#include "Number.h"
#include "bc.h"

int main(int argc, char *argv[])
{
    Number *r;
    char line[4000];
    // char *line = "5.6 + 6.2";
    printf("hello bc \n");
    while (readline(line, 4000))
    {
        // modify(line);
        r = infix(line);
        if (r != NULL)
            display(r);
        else
            fprintf(stderr, "Error in expression\n");
    }
    return 0;
}

// int main(int argc, char const *argv[])
// {
//     printf("Enter two numbers \n");
//     char a[50] = "66", b[50] = "2";
//     // char a[50], b[50];
//     // scanf("%s %s", a, b);
//     Number *n = createNum(a);
//     Number *m = createNum(b);
//     // Number *c = multiply(n, m);
//     // Number *c = divide(*n, *m, 0);
//     Number *c = divide(n, m, 2);
//     // Number *c = LeftShift(*m, 6);
//     // Digit *t, *p;
//     // combined_int_dec(n, &t, &p);
//     // printList(t);
//     display(c);
//     return 0;
// }
