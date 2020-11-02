#include "Number.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

void display(Number a)
{
    if (a.sign == positive)
        printf("%s\n", a.str);
    else
        printf("-%s\n", a.str);
}

void to_string(Number *a)
{
    int num_size = a->int_len + a->dec_len + 2; // +2 for decimal point and /0
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

int compare(Number a, Number b)
{
    // return 1 if a>b , -1 if a<b, 0 if a==b
    if (a.sign > b.sign)
        return 1;
    if (a.sign < b.sign)
        return -1;
    // now both signs are equal

    int cmp = 0;
    if (a.int_len > b.int_len)
        cmp = 1;
    else if (a.int_len < b.int_len)
        cmp = -1;
    else
    {
        int i = 0;
        while (a.str[i] != '\0' && b.str[i] != '\0')
        {
            if (a.str[i] > b.str[i])
            {
                cmp = 1;
                break;
            }
            if (a.str[i] < b.str[i])
            {
                cmp = -1;
                break;
            }
            i++;
        }
        if (cmp == 0)
        {
            int j = i;
            if (a.str[i] == '\0')
            {
                while (b.str[i] != '\0')
                {
                    if (b.str[i] != 0)
                    {
                        cmp = -1;
                        break;
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
                        cmp = 1;
                        break;
                    }
                    j++;
                }
            }
        }
    }

    if (a.sign == positive)
    {
        return cmp;
    }
    else
    {
        if (cmp == -1)
            return 1;
        else if (cmp == 1)
            return -1;
        else
            return 0;
    }
}

Number *abs_add(Number a, Number b)
{
    Number *c;
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
    else
    {
        c->dec_len = b.dec_len;
        c->dec_part = createDigit(b_cur->d);
        a_cur = a_cur->next;
        digit = c->dec_part;
        for (i = 1; i < -t; i++)
        {
            digit->next = createDigit(b_cur->d);
            digit = digit->next;
            b_cur = b_cur->next;
        }
    }

    for (i = t; i < c->dec_len; i++)
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
    c->int_len = t > 0 ? a.int_len : b.int_len;
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
    return c;
}