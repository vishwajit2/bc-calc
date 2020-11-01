#include "Number.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

void display(Number a)
{
    if (a.sign == 1)
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

Number *createNum(char *s)
{
    Number *a = (Number *)malloc(sizeof(Number));
    a->int_part = NULL;
    a->dec_part = NULL;
    int i = 0, count = 0;
    int d;
    Digit *digit;
    a->sign = 1; // sign is 1 for positive number and 0 for negative number
    a->str = s;
    if (s[0] == '-')
    {
        i = 1;
        a->sign = 0;
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

    if (a.sign == 1)
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