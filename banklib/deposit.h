#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct t_deposit {
    int percentSum;
    int taxSum;
    int totalSum;
} t_deposit;

t_deposit do_deposit(char* sum, char* month, char* percent, char* tax, char* regularity, int cap, int* error);
t_deposit calc_deposit(double sum, double month, double percent, double tax, double regularity, int cap);
