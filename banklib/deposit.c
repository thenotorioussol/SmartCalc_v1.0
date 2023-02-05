#include "deposit.h"

t_deposit do_deposit(char* sumC, char* monthC, char* percentC, char* taxC, char* regularityC, int cap, int* error) {
    t_deposit result;
    *error = 0;
    double sum;
    if (sscanf(sumC, "%lf", &sum) != 1) *error = 1;
    double percent;
    if (sscanf(percentC, "%lf", &percent) != 1) *error = 1;
    double month;
    if (sscanf(monthC, "%lf", &month) != 1) *error = 1;
    double tax;
    if (sscanf(taxC, "%lf", &tax) != 1) *error = 1;
    double regularity;
    if (sscanf(regularityC, "%lf", &regularity) != 1) *error = 1;
    if (*error == 1 || sum < 0 || percent < 0 || month <= 0 || regularity <= 0 || tax < 0) {
        *error = 1;
    } else {
        result = calc_deposit(sum, month, percent, tax, regularity, cap);
    }
    return result;
}

t_deposit calc_deposit(double sum, double month, double percent, double tax, double regularity, int cap) {
    t_deposit deposit;
    double numMonth = regularity;
    double percentSum = 0.0;
    double percentNow = 0.0;
    while (numMonth <= month) {
        percentNow = sum * percent / (12.0 / regularity) / 100.0;
        percentSum += percentNow;
        if (cap) {
            sum += percentNow;
        }
        numMonth += regularity;
    }
    deposit.percentSum = (int)round(percentSum);
    deposit.totalSum = (int)round(sum);
    deposit.taxSum = (int)round(percentSum * tax / 100.0);
    return deposit;
}