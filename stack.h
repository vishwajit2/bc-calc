#include "Number.h"

//  Stack for storing Number
typedef struct numNode
{
    Number *a;
    struct numNode *p;
} numNode;
typedef numNode *nstack;
void ninit(nstack *s);

void npush(nstack *s, Number *a);

Number *npop(nstack *s);

int nisempty(nstack *s);

// Stack for storing character Operators.
typedef struct cnode
{
    char a;
    struct cnode *p;
} cnode;
typedef cnode *cstack;
void cinit(cstack *s);

void cpush(cstack *s, char t);

char cpop(cstack *s);

char ctop(cstack *s);

int cisempty(cstack *s);