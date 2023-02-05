#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct t_credit {
    int paymentOne;
    int paymentLast;
    int overpayment;
    int total;
    int type;
} t_credit;

t_credit do_credit(const char *sumC, const char *percentC, const char *monthC, int *error, int type);
t_credit credit_calc(double sum, double month, double percent, int type);
double calc_total(double sum, double month, double percent);
