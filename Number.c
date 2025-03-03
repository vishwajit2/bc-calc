#include "Number.h"
#include <stdlib.h>
#include <stdio.h>

void combined_int_dec(Number *a, Digit **combined, Digit **decLast);
Digit *emptyList(int n);

void printList(Digit *t)
{
    printf("list : ");
    while (t)
    {
        printf("%d ", t->d);
        t = t->next;
    }
    printf("\n");
}

void printDebug(Number *a)
{
    Digit *t = a->int_part;
    printf("int part : ");
    while (t)
    {
        printf("%d", t->d);
        t = t->next;
    }
    printf("\n");
    printf("dec part : ");
    t = a->dec_part;
    while (t)
    {
        printf("%d", t->d);
        t = t->next;
    }
    printf("\n");
    printf("int len :%d  ", a->int_len);
    printf("dec len :%d  \n", a->dec_len);
    printf("%s\n\n", a->str);
}

Number *NumCopy(Number *n)
{
    Number *a = (Number *)malloc(sizeof(Number));
    a->int_part = n->int_part;
    a->dec_part = n->dec_part;
    a->str = n->str;
    a->sign = n->sign;
    a->int_len = n->int_len;
    a->dec_len = n->dec_len;
    return a;
}
void display(Number *a)
{

    if (a->sign == positive)
        printf("%s\n", a->str);
    else
        printf("-%s\n", a->str);
}

void addDigitInt(Number *a, char ch)
{
    if (ch < '0' || ch > '9')
        return;
    Digit *tmp = createDigit(ch - '0');
    tmp->next = a->int_part;
    a->int_part = tmp;
    a->int_len = a->int_len + 1;
    return;
}

void addDigitDec(Number *a, char ch)
{
    if (ch < '0' || ch > '9')
        return;
    Digit *tmp = createDigit(ch - '0');
    tmp->next = a->dec_part;
    a->dec_part = tmp;
    a->dec_len = a->dec_len + 1;
    return;
}

void to_string(Number *a)
{
    int num_size = a->int_len + a->dec_len + 2; // +2 for decimal point and /0
    if (a->str != NULL)
    {
        free(a->str);
        a->str = NULL;
    }

    char *s = (char *)malloc(num_size * sizeof(char));

    Digit *current = a->int_part;
    int i = 0;
    int int_len = a->int_len;
    for (i = int_len - 1; i >= 0; i--)
    {
        s[i] = current->d + '0'; // convert int to char eg 5 to '5'
        current = current->next;
    }
    if (a->dec_len == 0)
    {
        s[int_len] = '\0';
        a->str = s;
        return;
    }
    // now a.dec_lec is not 0
    s[int_len] = '.'; // decimal point
    current = a->dec_part;
    for (i = num_size - 2; i > int_len; i--)
    {
        s[i] = current->d + '0'; // convert int to char eg 5 to '5'
        current = current->next;
    }
    s[num_size - 1] = '\0';

    a->str = s;
}

Digit *createDigit(int t)
{
    Digit *a = (Digit *)malloc(sizeof(Digit));
    while (a == NULL)
    {
        return NULL;
    }
    a->d = t;
    a->next = NULL;
    return a;
}

void initNum(Number **n)
{
    *n = (Number *)malloc(sizeof(Number));
    Number *a = *n;
    a->int_part = NULL;
    a->dec_part = NULL;
    a->str = NULL;
    a->sign = positive;
    a->int_len = 0;
    a->dec_len = 0;
}

Number *createNum(char *s)
{
    Number *a;
    initNum(&a);
    int i = 0, count = 0;
    int d;
    Digit *digit;
    a->str = s;
    if (s[0] == '-')
    {
        i = 1;
        a->sign = negative;
        a->str = s + 1;
    }
    count = i;
    while (s[i] != '\0' && s[i] != '.')
    {
        d = s[i] - '0';
        i++;
        digit = createDigit(d);
        digit->next = a->int_part;
        a->int_part = digit;
    }
    a->int_len = i - count;
    count = i;

    if (s[i] == '.')
    {
        i++;
        count = i;
        while (s[i] != '\0')
        {
            d = s[i] - '0';
            i++;
            digit = createDigit(d);
            digit->next = a->dec_part;
            a->dec_part = digit;
        }
    }
    a->dec_len = i - count;
    return a;
}

int compare(Number *a, Number *b)
{
    // return 1 if a>b , -1 if a<b, 0 if a==b
    if (a->sign > b->sign)
        return 1;
    if (a->sign < b->sign)
        return -1;

    if (a->sign == positive)
    {
        return abs_compare(a, b);
    }
    else
    {
        // as sign is negative , we return 1 if a is smaller by magnitude
        return abs_compare(b, a);
    }
}

// considers magnitude only
int abs_compare(Number *m, Number *n)
{
    Number a = *m, b = *n;
    if (a.int_len > b.int_len)
        return 1;
    if (a.int_len < b.int_len)
        return -1;
    int i = 0;
    while (a.str[i] != '\0' && b.str[i] != '\0')
    {
        if (a.str[i] > b.str[i])
        {
            return 1;
        }
        if (a.str[i] < b.str[i])
        {
            return -1;
        }
        i++;
    }
    int j = i;

    // one of the digits have extra digits after decimal point,
    //number having more digits is greater if at least one of those digits is not 0

    if (a.str[i] == '\0')
    {
        while (b.str[i] != '\0')
        {
            if (b.str[i] != 0)
            {
                return -1;
            }
            i++;
        }
    }

    else if (b.str[j] == '\0')
    {
        while (a.str[j] != '\0')
        {
            if (a.str[j] != 0)
            {
                return 1;
            }
            j++;
        }
    }
    return 0;
}

Number *add(Number *a, Number *b)
{
    Number *c;
    if (a->sign == b->sign)
    {
        c = abs_add(a, b);
        c->sign = a->sign;
        return c;
    }
    else
    {
        int t = abs_compare(a, b);
        if (t == 0)
        {
            // result is 0;
            initNum(&c);
            c->int_len = 1;
            c->int_part = createDigit(0);
            c->str = "0";
            return c;
        }
        if (t == 1)
        {
            c = abs_subtract(a, b);
            c->sign = a->sign;
        }
        else
        {
            c = abs_subtract(b, a);
            c->sign = b->sign;
        }
        return c;
    }
}

Number *subtract(Number *a, Number *b)
{
    // change sign of b and do addition
    Number *t = NumCopy(b);
    t->sign = !b->sign;
    return add(a, t);
}

Number *abs_add(Number *m, Number *n)
{
    Number *c;
    Number a = *m, b = *n;
    initNum(&c);
    Digit *digit;
    Digit *a_cur = a.dec_part, *b_cur = b.dec_part;
    int i = 0, sum = 0, s = 0, cr = 0;
    int t = a.dec_len - b.dec_len;
    if (t > 0)
    {
        c->dec_len = a.dec_len;
        c->dec_part = createDigit(a_cur->d);
        a_cur = a_cur->next;
        digit = c->dec_part;
        for (i = 1; i < t; i++)
        {
            digit->next = createDigit(a_cur->d);
            digit = digit->next;
            a_cur = a_cur->next;
        }
    }
    else if (t < 0)
    {
        c->dec_len = b.dec_len;
        c->dec_part = createDigit(b_cur->d);
        b_cur = b_cur->next;
        digit = c->dec_part;
        for (i = 1; i < -t; i++)
        {
            digit->next = createDigit(b_cur->d);
            digit = digit->next;
            b_cur = b_cur->next;
        }
    }
    else if (a.dec_len != 0)
    {
        c->dec_len = a.dec_len + 1;
        i = 1;
        c->dec_part = createDigit(0);
        digit = c->dec_part;
    }

    for (i = i; i < c->dec_len; i++)
    {
        sum = a_cur->d + b_cur->d + cr;
        s = sum % 10;
        cr = sum / 10;
        digit->next = createDigit(s);
        digit = digit->next;
        a_cur = a_cur->next;
        b_cur = b_cur->next;
    }

    t = a.int_len - b.int_len;
    int min;
    if (t > 0)
    {
        c->int_len = a.int_len;
        min = b.int_len;
    }
    else
    {
        c->int_len = b.int_len;
        min = a.int_len;
    }

    b_cur = b.int_part;
    a_cur = a.int_part;
    sum = a_cur->d + b_cur->d + cr;
    s = sum % 10;
    cr = sum / 10;
    c->int_part = createDigit(s);
    digit = c->int_part;
    a_cur = a_cur->next;
    b_cur = b_cur->next;

    for (i = 1; i < min; i++)
    {
        sum = a_cur->d + b_cur->d + cr;
        s = sum % 10;
        cr = sum / 10;
        digit->next = createDigit(s);
        digit = digit->next;
        a_cur = a_cur->next;
        b_cur = b_cur->next;
    }
    if (t > 0)
    {
        for (i = 0; i < t; i++)
        {
            sum = a_cur->d + cr;
            s = sum % 10;
            cr = sum / 10;
            digit->next = createDigit(s);
            digit = digit->next;
            a_cur = a_cur->next;
        }
    }
    else
    {
        for (i = 0; i < -t; i++)
        {
            sum = b_cur->d + cr;
            s = sum % 10;
            cr = sum / 10;
            digit->next = createDigit(s);
            digit = digit->next;
            b_cur = b_cur->next;
        }
    }
    if (cr > 0)
    {
        c->int_len += 1;
        digit->next = createDigit(cr);
    }
    to_string(c);
    removeIntZeros(c);
    return c;
}

Number *abs_subtract(Number *m, Number *n)
{
    Number *c;
    Number a = *m, b = *n;
    initNum(&c);
    Digit *digit;
    Digit *a_cur = a.dec_part, *b_cur = b.dec_part;
    int i = 0, temp = 0, diff = 0, cr = 0;
    int t = a.dec_len - b.dec_len;
    if (t > 0)
    {
        c->dec_len = a.dec_len;
        c->dec_part = createDigit(a_cur->d);
        a_cur = a_cur->next;
        digit = c->dec_part;
        for (i = 1; i < t; i++)
        {
            digit->next = createDigit(a_cur->d);
            digit = digit->next;
            a_cur = a_cur->next;
        }
    }
    else if (t < 0) // b has more number of digits after decimal point
    {
        c->dec_len = b.dec_len;
        temp = -b_cur->d - cr;
        if (temp < 0)
        {
            cr = 1;
            diff = 10 + temp;
        }
        else
        {
            cr = 0;
            diff = temp;
        }
        c->dec_part = createDigit(diff);
        b_cur = b_cur->next;
        digit = c->dec_part;
        for (i = 1; i < -t; i++)
        {
            temp = -b_cur->d - cr;
            if (temp < 0)
            {
                cr = 1;
                diff = 10 + temp;
            }
            else
            {
                cr = 0;
                diff = temp;
            }
            digit->next = createDigit(diff);
            digit = digit->next;
            b_cur = b_cur->next;
        }
    }
    else if (a.dec_len != 0)
    {
        c->dec_len = a.dec_len + 1;
        i = 1;
        c->dec_part = createDigit(0);
        digit = c->dec_part;
        for (i = i; i < c->dec_len; i++)
        {
            temp = a_cur->d - b_cur->d - cr;
            if (temp < 0)
            {
                cr = 1;
                diff = 10 + temp;
            }
            else
            {
                cr = 0;
                diff = temp;
            }
            digit->next = createDigit(diff);
            digit = digit->next;
            a_cur = a_cur->next;
            b_cur = b_cur->next;
        }
    }

    t = a.int_len - b.int_len;
    int min;
    if (t > 0)
    {
        c->int_len = a.int_len;
        min = b.int_len;
    }
    else
    {
        c->int_len = b.int_len;
        min = a.int_len;
    }

    b_cur = b.int_part;
    a_cur = a.int_part;
    temp = a_cur->d - b_cur->d - cr;
    if (temp < 0)
    {
        cr = 1;
        diff = 10 + temp;
    }
    else
    {
        cr = 0;
        diff = temp;
    }
    c->int_part = createDigit(diff);
    digit = c->int_part;
    a_cur = a_cur->next;
    b_cur = b_cur->next;

    for (i = 1; i < min; i++)
    {

        temp = a_cur->d - b_cur->d - cr;
        if (temp < 0)
        {
            cr = 1;
            diff = 10 + temp;
        }
        else
        {
            cr = 0;
            diff = temp;
        }
        digit->next = createDigit(diff);
        digit = digit->next;
        a_cur = a_cur->next;
        b_cur = b_cur->next;
    }
    if (t >= 0)
    {
        for (i = 0; i < t; i++)
        {
            temp = a_cur->d - cr;
            // printf("%d %d \n", a_cur->d, cr);
            // printf("in sub...temp %d \n", temp);
            // display(a);
            // display(b);
            if (temp < 0)
            {
                cr = 1;
                diff = 10 + temp;
            }
            else
            {
                cr = 0;
                diff = temp;
            }
            digit->next = createDigit(diff);
            digit = digit->next;
            a_cur = a_cur->next;
        }
    }
    else
    {
        printf("expected a > b\0");
    }
    if (cr > 0)
    {
        printf("expected a > b\0");
    }
    to_string(c);
    removeIntZeros(c);
    return c;
}

void combined_int_dec(Number *a, Digit **combined, Digit **decLast)
{
    if (a->dec_part == NULL)
    {
        *combined = a->int_part;
        *decLast = NULL;
    }
    else
    {
        *combined = a->dec_part;
        Digit *a_cur = *combined;
        while (a_cur->next)
        {
            a_cur = a_cur->next;
        }
        a_cur->next = a->int_part;
        *decLast = a_cur;
    }
}

Digit *emptyList(int n)
{
    Digit *res = createDigit(0);
    Digit *t = res;
    for (int i = 1; i < n; i++)
    {
        t->next = createDigit(0);
        t = t->next;
    }
    return res;
}

Number *multiply(Number *m, Number *n)
{
    // we can ignore position of decimal point and multipply and consider it at end
    Number *zero = num_zero();
    Number *one = createNum("1");
    if (abs_compare(m, one) == 0)
    {
        return createNum(n->str);
    }
    else if (abs_compare(n, one) == 0)
    {
        return createNum(m->str);
    }

    if (abs_compare(m, zero) == 0 || abs_compare(n, zero) == 0)
    {
        return zero;
    }
    removeIntZeros(m);
    removeIntZeros(n);
    Number *c;
    Number a = *m, b = *n;
    initNum(&c);
    Digit *a1, *a_decLast, *b1, *b_decLast;
    int mul, carry;
    combined_int_dec(m, &a1, &a_decLast);
    combined_int_dec(n, &b1, &b_decLast);
    int max_size = a.int_len + b.int_len + a.dec_len + b.dec_len;
    Digit *result = emptyList(max_size);
    Digit *res1 = result, *res2, *a2 = a1;
    while (b1)
    {

        carry = 0;
        res2 = res1;
        a1 = a2;
        while (a1)
        {
            mul = a1->d * b1->d + carry;
            res2->d += mul % 10;
            // resultant Node  can be greater than 9
            carry = mul / 10 + res2->d / 10;
            res2->d = res2->d % 10;
            a1 = a1->next;
            res2 = res2->next;
        }

        // if carry is remaining from last multiplication
        if (carry > 0)
        {
            res2->d += carry;
        }

        res1 = res1->next;
        b1 = b1->next;
    }
    // now res2 is at end and if res2.d == 0 we need to remove pointer to that
    if (res2->d == 0)
    {
        c->int_len = a.int_len + b.int_len - 1;
        if (res1->next)
        {
            while (res1->next->next)
            {
                res1 = res1->next;
            }
            res1->next = NULL;
            free(res2);
        }
    }
    else
    {
        c->int_len = a.int_len + b.int_len;
    }
    c->dec_len = a.dec_len + b.dec_len;
    c->sign = (a.sign == b.sign); // sign of c is positive(1) if a.sign == b.sign
    if (c->dec_len == 0)
    {
        c->int_part = result;
    }
    else
    {
        c->dec_part = result;
        for (int i = 0; i < c->dec_len - 1; i++)
        {
            result = result->next;
        }
        c->int_part = result->next;
        result->next = NULL;
    }
    // seperate int and dec part of original nums
    if (a_decLast)
    {
        a_decLast->next = NULL;
    }
    if (b_decLast)
    {
        b_decLast->next = NULL;
    }
    to_string(c);
    removeIntZeros(c);
    return c;
}
// multipy by 10^t
Number *LeftShift(Number *n, int t)
{
    if (n->dec_len == 0)
    {
        int size = n->int_len + t;
        char *s = (char *)malloc(size * sizeof(char));
        int i = 0;
        for (i = 0; i < n->int_len; i++)
        {
            s[i] = n->str[i];
        }
        while (i < size)
        {
            s[i] = '0';
            i++;
        }
        s[i] = '\0';
        Number *a = createNum(s);
        a->sign = n->sign;
        return a;
    }
    int size = n->int_len;
    if (t >= n->dec_len)
    {
        size = n->int_len + t + 1; // 1 for \0
        char *s = (char *)malloc(size * sizeof(char));
        int i = 0;
        for (i = 0; i < n->int_len; i++)
        {
            s[i] = n->str[i];
        }
        // i+1 to compensate for '.'

        while (n->str[i + 1] != '\0')
        {
            s[i] = n->str[i + 1];
            i++;
        }
        while (i < size - 1)
        {
            s[i] = '0';
            i++;
        }
        s[i] = '\0';
        Number *a = createNum(s);
        a->sign = n->sign;
        return a;
    }
    else
    {
        size = size + n->dec_len + 2; // \0 and '.'
        char *s = (char *)malloc(size * sizeof(char));
        int i = 0;
        for (i = 0; i < n->int_len; i++)
        {
            s[i] = n->str[i];
        }
        while (t--)
        {
            s[i] = n->str[i + 1];
            i++;
        }
        s[i++] = '.';
        while (n->str[i] != '\0')
        {
            s[i] = n->str[i];
            i++;
        }
        s[i] = '\0';
        Number *a = createNum(s);
        a->sign = n->sign;
        return a;
    }
}

Number *divide(Number *a, Number *b, int scale)
{
    if (compare(b, num_zero()) == 0)
    {
        printf(".....divide by 0.....\n");
        return NULL;
    }

    // first let's convert both into int by muliplying by common factor .
    if (abs_compare(LeftShift(a, scale), b) == -1)
    {
        return num_zero();
    }
    int len = 0;
    int mult = a->dec_len > b->dec_len ? a->dec_len : b->dec_len;
    Number *a1, *b1, *divisor, *temp = NULL;
    // printDebug(a);
    // printDebug(b);
    a1 = LeftShift(a, mult + scale);
    b1 = LeftShift(b, mult);
    Digit *c1 = NULL, *digit, *tempDigit;
    divisor = LeftShift(b1, a1->int_len - b1->int_len);
    int t = 0;
    while (compare(a1, b1) >= 0)
    {
        // printf("a ");
        // display(a1);
        // printf("b ");
        // display(b1);
        // printf("divisor ");
        // display(divisor);
        len++;
        temp = NULL;
        temp = subtract(a1, divisor);
        t = 0;
        while (compare(temp, num_zero()) >= 0)
        {
            a1 = temp;
            temp = subtract(a1, divisor);
            t++;
        }
        digit = createDigit(t);
        digit->next = c1;
        c1 = digit;
        // divide divisor by 10
        tempDigit = divisor->int_part;
        divisor->int_part = tempDigit->next;
        free(tempDigit);
        divisor->int_len -= 1;
        to_string(divisor);
        free(temp);
    }
    int gap = divisor->int_len - b1->int_len + 1;
    while (gap != 0)
    {
        digit = createDigit(0);
        digit->next = c1;
        c1 = digit;
        len++;
        gap--;
    }

    Number *result;
    initNum(&result);
    result->sign = (a->sign == b->sign);
    if (scale == 0)
    {
        result->int_part = c1;
        result->int_len = len;
        result->dec_len = 0;
        result->dec_part = NULL;
    }
    else
    {
        result->dec_part = c1;
        if (len <= scale)
        {
            for (int i = 1; i < len; i++)
            {
                c1 = c1->next;
            }
            while (len != scale)
            {
                len++;
                c1->next = createDigit(0);
                c1 = c1->next;
            }
            c1->next = NULL;
            result->dec_len = scale;
            result->int_len = 0;
            result->int_part = NULL;
        }
        else
        {
            for (int i = 0; i < scale - 1; i++)
            {
                c1 = c1->next;
            }
            result->dec_len = scale;
            result->int_len = len - scale;
            result->int_part = c1->next;
            c1->next = NULL;
        }
    }
    to_string(result);
    removeIntZeros(result);
    return result;
}

void removeIntZeros(Number *a)
{
    if (a->str == NULL || a->int_len == 0)
        return;
    Digit *t = a->int_part, *temp;
    int i = 0;
    while (a->str[i] == '0')
    {
        i++;
    }
    int k = a->int_len - i;
    a->int_len -= i;
    a->str += i;
    while (k > 1)
    {
        t = t->next;
        k--;
    }
    temp = t;
    t = t->next;
    temp->next = NULL;
    while (t)
    {
        temp = t;
        t = temp->next;
        free(temp);
    }
}

Number *num_zero()
{
    return createNum("0");
}

Number *modulo(Number *a, Number *b)
{
    Number *t = divide(a, b, 0);
    Number *m = multiply(b, t);
    Number *res = subtract(a, m);
    free(t);
    free(m);
    return res;
}

Number *removeFractionalPart(Number *n)
{
    Number *a = (Number *)malloc(sizeof(Number));
    a->int_part = n->int_part;
    a->int_len = n->int_len;
    a->dec_part = NULL;
    a->dec_len = 0;
    a->sign = n->sign;
    a->str = NULL;
    to_string(a);
    return a;
}
Number *power(Number *a, Number *pow, int scale)
{
    // we dot support fractional powers, let's remove it
    Number *p;
    Number *temp, *a_cp;
    Number *result = createNum("1");
    if (pow->dec_len != 0)
    {
        printf("...fractional powers are not supported...\n");
        printf("...fractional part will be ignored...\n");
    }
    p = removeFractionalPart(pow);
    Number *zero = num_zero();
    Number *one = createNum("1");
    Number *two = createNum("2");
    int cmp_zero = compare(p, zero);
    if (cmp_zero == 0)
    {
        return createNum("0");
    }
    if (cmp_zero == -1)
    {
        p->sign = positive;
        // we'll take inverse of result at end
    }
    int isOdd = 0;
    int cmp = cmp_zero;
    while (cmp > 0)
    {
        // printf("res ");
        // display(result);
        // printf("p ");
        // display(p);
        // printf("a ");
        // display(a);
        isOdd = p->int_part->d % 2;
        if (isOdd)
        {
            temp = result;
            result = multiply(result, a);
            free(temp);
            temp = p;
            p = subtract(p, one);
            free(temp);
        }
        else
        {
            temp = a;
            a_cp = createNum(a->str); // copy of a
            a = multiply(a, a_cp);
            free(a_cp);
            free(temp);
            temp = p;
            p = divide(p, two, 0);
            free(temp);
        }
        cmp = compare(p, zero);
    }
    if (cmp_zero == -1)
    {
        temp = result;
        result = divide(createNum("1"), result, scale);
        free(temp);
    }
    return result;
}

double toReal(Number *a)
{
    double ans;
    sscanf(a->str, "%lf", &ans);
    if (a->sign == negative)
    {
        ans = -1 * ans;
    }
    return ans;
}
//converts double data type in number list.
Number *realToNumber(double a)
{
    char str[128];
    sprintf(str, "%lf", a);
    Number *ans = createNum(str);
    return ans;
}