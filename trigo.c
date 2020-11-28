//Sine Operation.
#include "Number.h"
#include "Trigo.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
Number *sine(Number *a)
{
    double no, val;
    Number *pi = createNum("3.14159265359");
    Number *ans = (Number *)malloc(sizeof(Number));
    Number *temp = (Number *)malloc(sizeof(Number));
    temp = modulo(a, pi);
    no = toReal(temp);
    val = sin(no);
    ans = realToNumber(val);
    return ans;
}
//Cosine Operation.
Number *cosine(Number *a)
{
    double no, val;
    Number *pi = createNum("3.14159265359");
    Number *ans = (Number *)malloc(sizeof(Number));
    Number *temp = (Number *)malloc(sizeof(Number));
    temp = modulo(a, pi);
    no = toReal(temp);
    val = cos(no);
    ans = realToNumber(val);
    return ans;
}
//Tangent Operation.
Number *tangent(Number *a)
{
    double no, val;
    Number *pi = createNum("3.14159265359");
    Number *ans = (Number *)malloc(sizeof(Number));
    Number *temp = (Number *)malloc(sizeof(Number));
    temp = modulo(a, pi);
    no = toReal(temp);
    val = tan(no);
    ans = realToNumber(val);
    return ans;
}