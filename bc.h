#include "Number.h"
#ifndef BC_DEF

#define BC_DEF
#define scale 2
#define OPERAND 100
#define OPERATOR 200
#define END 300
#define ERR 400

typedef struct token
{
    int type;
    Number *num;
    char op;
} token;
enum state
{
    NUMBER,
    DOT,
    OP,
    FINISH,
    ERROR,
    SPACE
};

int readline(char *line, int len);
Number *evaluate(char *exp);
int precedance(char c);
token gettoken(char *expr, int *reset);

#endif