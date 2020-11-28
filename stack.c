#include <stdlib.h>
#include "stack.h"

void cinit(cstack *s)
{
    *s = NULL;
}
void cpush(cstack *s, char t)
{
    cstack temp;
    temp = (cnode *)malloc(sizeof(cnode));
    temp->a = t;
    temp->p = (*s);
    *s = temp;
}
char cpop(cstack *s)
{
    char t;
    cstack temp;
    temp = (*s);
    t = (*s)->a;
    *s = (*s)->p;
    free(temp);
    return t;
}

char ctop(cstack *s)
{
    char t;
    t = (*s)->a;
    return t;
}
int cisempty(cstack *s)
{
    return *s == NULL;
}

// Stack implementation to store Number list.
void ninit(nstack *s)
{
    *s = NULL;
}
void npush(nstack *s, Number *t)
{
    nstack temp;
    temp = (numNode *)malloc(sizeof(numNode));
    temp->a = t;
    temp->p = *s;
    *s = temp;
}
Number *npop(nstack *s)
{
    Number *t;
    nstack temp;
    t = (*s)->a;
    temp = *s;
    *s = (*s)->p;
    free(temp);
    return t;
}
int nisempty(nstack *s)
{
    return *s == NULL;
}