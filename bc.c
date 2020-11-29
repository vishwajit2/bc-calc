#include "bc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "Number.h"
#include <limits.h>
#include "trigo.h"

token gettoken(char *expr, int *reset)
{
    static int i = 0;
    static int preUnary = 1;
    Number *a;
    initNum(&a);
    char currchar;
    static enum state currstate = SPACE;
    enum state nextstate;
    token t;
    if (*reset == 1)
    {
        currstate = SPACE;
        preUnary = 1;
        *reset = 0;
        i = 0;
        //t.dec = 0;
    }
    while (1)
    {
        currchar = expr[i];
        // printf("%c", currchar);
        switch (currstate)
        {
        case NUMBER:
            switch (currchar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                nextstate = NUMBER;
                // printf("%c", currchar);
                addDigitInt(a, currchar);
                i++;
                break;

            case '.':
                currstate = DOT;
                i++;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
            case 'S':
            case 'C':
            case 'T':
                nextstate = OP;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                i++;
                return t;
                break;
            case '\0':
                nextstate = FINISH;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                return t;
                break;
            case ' ':
                nextstate = SPACE;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                i++;
                // printf("got space %d\n", a->int_part->d);
                return t;
                break;

            default: // anything else
                nextstate = ERROR;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                return t;
                break;
            }
            break;

        case DOT:
            switch (currchar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                addDigitDec(a, currchar);
                nextstate = DOT;
                currstate = nextstate;
                i++;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
            case 'S':
            case 'C':
            case 'T':
                nextstate = OP;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                i++;
                return t;
                break;
            case '\0':
                nextstate = FINISH;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                return t;
                break;
            case ' ':
                nextstate = SPACE;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                i++;
                return t;
                break;

            default:
                nextstate = ERROR;
                t.type = OPERAND;
                t.num = a;
                currstate = nextstate;
                return t;
                break;
            }
            break;

        case OP:
            switch (currchar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (preUnary)
                {
                    a->sign = (expr[i - 1] == '+');
                    currstate = NUMBER;
                    // printf("yes in  unary");
                    preUnary = 0;
                    break;
                }
                else
                {
                    t.type = OPERATOR;
                    t.op = expr[i - 1];
                    nextstate = NUMBER;
                    currstate = nextstate;
                    // printf("not in unary");
                    return t;
                    break;
                }
            case '+':
            case '-':
                preUnary = 1;
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
            case 'S':
            case 'C':
            case 'T':
                nextstate = OP;
                t.type = OPERATOR;
                t.op = expr[i - 1];
                currstate = nextstate;
                i++;
                return t;
                break;
            case '\0':
                nextstate = FINISH;
                t.type = OPERATOR;
                t.op = expr[i - 1];
                currstate = nextstate;
                return t;
                break;
            case ' ':
                preUnary = 1;
                nextstate = SPACE;
                t.type = OPERATOR;
                t.op = expr[i - 1];
                currstate = nextstate;
                i++;
                return t;
                break;

            case '.':
                nextstate = DOT;
                t.type = OPERATOR;
                t.op = expr[i - 1];
                currstate = nextstate;
                i++;
                return t;
                break;

            default: // anything else
                nextstate = ERROR;
                t.type = OPERATOR;
                t.op = expr[i - 1];
                currstate = nextstate;
                return t;
                break;
            }
            break;
        case FINISH:
            t.type = END;
            return t;
            break;
        case ERROR:
            t.type = ERR;
            return t;
            break;
        case SPACE:
            switch (currchar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                addDigitInt(a, currchar);
                nextstate = NUMBER;
                preUnary = 0;
                i++;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
            case 'S':
            case 'C':
            case 'T':
                nextstate = OP;
                i++;
                break;
            case '\0':
                nextstate = FINISH;
                break;
            case ' ':
                nextstate = SPACE;
                i++;
                break;

            case '.':
                nextstate = DOT;
                preUnary = 0;
                i++;
                break;

            default: // anything else
                nextstate = ERROR;
                break;
            }
            currstate = nextstate;
            break;
        }
    }
}

int precedance(char c)
{
    switch (c)
    {
    case 'S':
    case 'C':
    case 'T':
        return -1;
        break;
    case ')':
        return 0;
        break;
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '%':
        return 3;
        break;
    case '(':
        return 4;
        break;
    default:
        return 5;
        break;
    }
    return 5;
}
Number *evaluate(char *exp)
{
    token t;
    char curr_op, prev_op, ch;
    int cnt_ob = 0, cnt_cb = 0, reset = 1, curr, prev;
    Number *a, *b, *z;
    a = (Number *)malloc(sizeof(Number));
    b = (Number *)malloc(sizeof(Number));
    z = (Number *)malloc(sizeof(Number));
    initNum(&a);
    initNum(&b);
    initNum(&z);
    nstack ns;
    cstack cs;
    ninit(&ns);
    cinit(&cs);
    prev = ERR;
    while (1)
    {
        t = gettoken(exp, &reset);
        if (t.type == OPERAND)
        {
            to_string(t.num);
            // display(t.num);
        }
        curr = t.type;
        if (curr == prev && prev == OPERAND)
        {
            return NULL;
        }
        if (t.type == OPERAND)
        {
            // display(t.num);
            npush(&ns, t.num);
        }
        else if (t.type == OPERATOR)
        {
            curr_op = t.op;
            if (curr_op == '(')
                cnt_ob++;
            if (curr_op == ')')
                cnt_cb++;
            if (cnt_cb > cnt_ob)
                //return INT_MIN;
                return NULL;
            if (!cisempty(&cs))
            {
                prev_op = ctop(&cs);
                switch (prev_op)
                {
                case 'S':
                    cpop(&cs);
                    a = npop(&ns);
                    z = sine(a);
                    npush(&ns, z);
                    //cpush(&cs, curr_op);
                    break;
                case 'C':
                    cpop(&cs);
                    a = npop(&ns);
                    z = cosine(a);
                    npush(&ns, z);
                    //cpush(&cs, curr_op);
                    break;
                case 'T':
                    cpop(&cs);
                    a = npop(&ns);
                    z = tangent(a);
                    npush(&ns, z);
                    //cpush(&cs, curr_op);
                    break;
                default:
                    break;
                }
                while (precedance(prev_op) >= precedance(curr_op))
                {
                    prev_op = cpop(&cs);
                    if (!nisempty(&ns))
                    {
                        a = npop(&ns);
                    }
                    else
                    {
                        cpush(&cs, prev_op);
                        break;
                    }
                    if (!nisempty(&ns))
                    {
                        b = npop(&ns);
                    }
                    else
                    {
                        cpush(&cs, prev_op);
                        npush(&ns, a);
                        break;
                    }
                    if ((prev_op == '/' || prev_op == '%') && a == 0)
                    {
                        fprintf(stderr, "Mathematical error\n");
                        //return INT_MIN;
                        return NULL;
                    }
                    switch (prev_op)
                    {
                    case '+':
                        //z = b + a;
                        z = add(a, b);
                        npush(&ns, z);
                        break;
                    case '-':
                        //z = b - a;
                        z = subtract(b, a);
                        npush(&ns, z);
                        break;
                    case '*':
                        //z = b * a;
                        z = multiply(b, a);
                        npush(&ns, z);
                        break;
                    case '/':
                        //z = b / a;
                        z = divide(b, a, scale);
                        // display(z);
                        printf("yeagh");
                        npush(&ns, z);
                        break;
                    case '%':
                        //z = b % a;
                        z = modulo(b, a);
                        npush(&ns, z);
                        break;

                    case '(':
                        cpush(&cs, prev_op);
                        npush(&ns, b);
                        npush(&ns, a);
                        break;
                    default:
                        //return INT_MIN;
                        return NULL;
                    }
                    if (prev_op == '(')
                        break;
                    if (!cisempty(&cs))
                        prev_op = ctop(&cs);
                    else
                        break;
                }
            }
            cpush(&cs, t.op);
            if (curr_op == ')')
            {
                ch = cpop(&cs);
                cnt_cb--;
                ch = cpop(&cs);
                cnt_ob--;
            }
        }
        else if (t.type == END)
        {
            // printf("end");
            if (cnt_ob == cnt_cb)
            {
                while (!cisempty(&cs))
                {
                    if (!nisempty(&ns))
                    {
                        a = npop(&ns);
                    }
                    else
                    {
                        fprintf(stderr, "Less operands\n");
                        //return INT_MIN;
                        return NULL;
                    }
                    if (!nisempty(&ns))
                    {
                        b = npop(&ns);
                    }
                    else
                    {
                        fprintf(stderr, "Less operands\n");
                        //return INT_MIN;
                        return NULL;
                    }
                    ch = cpop(&cs);
                    if ((ch == '/' || ch == '%') && a == 0)
                    {
                        fprintf(stderr, "Mathematical error\n");
                        //return INT_MIN;
                        return NULL;
                    }
                    switch (ch)
                    {
                    case '+':
                        z = add(b, a);
                        npush(&ns, z);
                        break;
                    case '-':
                        z = subtract(b, a);
                        npush(&ns, z);
                        break;
                    case '*':
                        z = multiply(b, a);
                        npush(&ns, z);
                        break;
                    case '/':
                        z = divide(b, a, scale);
                        npush(&ns, z);
                        break;
                    case '%':
                        z = modulo(b, a);
                        npush(&ns, z);
                        break;
                    default:
                        //return INT_MIN;
                        return NULL;
                    }
                }
            }
            else
            {
                fprintf(stderr, "Error in Expression\n");
                //return INT_MIN;
                return NULL;
            }
            if (!nisempty(&ns))
            {
                z = npop(&ns);
                if (nisempty(&ns))
                    return z;
                else
                {
                    fprintf(stderr, "Less Operators\n");
                    //return INT_MIN;
                    return NULL;
                }
            }
            else
            {
                fprintf(stderr, "Less Operands\n");
                return NULL;
            }
        }
        else if (t.type == ERR)
        {
            return NULL;
        }
        prev = curr;
    }
}

int readline(char *line, int len)
{
    int i;
    char ch;
    i = 0;
    while (i < len - 1)
    {
        ch = getchar();
        if (ch == '\n')
        {
            line[i++] = '\0';
            return i - 1;
        }
        else
            line[i++] = ch;
    }
    line[len - 1] = '\0';
    return len - 1;
}
