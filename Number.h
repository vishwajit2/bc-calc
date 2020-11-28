#ifndef LARGE_NUMBER

#define LARGE_NUMBER

// structure to store a digit
// short is used instead of int as number can range from 0 to 9 only .
typedef struct Digit
{
    int d;
    struct Digit *next;
} Digit;

typedef struct Number
{
    int sign;
    char *str; // store string of number without sign
    int int_len, dec_len;
    struct Digit *int_part, *dec_part;
} Number;

#define positive 1
#define negative 0

void addDigitInt(Number *a, char ch);
void addDigitDec(Number *a, char ch);
int compare(Number *a, Number *b);
int abs_compare(Number *a, Number *b);
Number *abs_add(Number *a, Number *b);
Number *abs_subtract(Number *a, Number *b);
Number *add(Number *a, Number *b);
Number *subtract(Number *a, Number *b);
Number *LeftShift(Number *n, int t);
Number *multiply(Number *a, Number *b);
Number *divide(Number *a, Number *b, int scale);
Number *power(Number *a, Number *b, int scale);
void display(Number *a);
void to_string(Number *a);
void initNum(Number **n);
Number *createNum(char *s); // create a number from given string and return pointer to that number
Digit *createDigit(int t);  // create a Digit from given int and return pointer to that Digit
void removeIntZeros(Number *a);
Number *num_zero();
Number *modulo(Number *a, Number *b);
void printList(Digit *t);
void combined_int_dec(Number *a, Digit **combined, Digit **decLast);
Number *NumCopy(Number *n);
double toReal(Number *a);
Number *realToNumber(double a);
void printDebug(Number *a);
#endif