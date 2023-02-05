#include "credit.h"

t_credit do_credit(const char *sumC, const char *percentC, const char *monthC, int *error, int type) {
    t_credit result;
    *error = 0;
    double sum;
    if (sscanf(sumC, "%lf", &sum) != 1) *error = 1;
    double percent;
    if (sscanf(percentC, "%lf", &percent) != 1) *error = 1;
    double month;
    if (sscanf(monthC, "%lf", &month) != 1) *error = 1;
    if (*error == 1 || sum <= 0 || percent <= 0 || month <= 0) {
        *error = 1;
    } else {
        result = credit_calc(sum, month, percent, type);
    }
    return result;
}

t_credit credit_calc(double sum, double month, double percent, int type) {
    t_credit credit;
    if (type == 0) {
        double monthPercent = percent/12/100;
        double k = monthPercent * pow(1 + monthPercent, month) / (pow(1 + monthPercent, month) - 1);
        credit.paymentOne = (int)round(k * sum);
        credit.total = (int)round(k * sum * month);
        credit.overpayment = (int)round(credit.total - sum);
    } else if (type == 1) {
        double mainPayment = sum / month;
        credit.paymentOne = (int)round(sum * percent / 12 / 100 + mainPayment);
        credit.paymentLast = (int)round((sum - mainPayment * (month - 1)) * percent / 12 / 100 + mainPayment);
        credit.total = (int)round(calc_total(sum, month, percent));
        credit.overpayment = credit.total - (int)round(sum);
    }
    return credit;
}

double calc_total(double sum, double month, double percent) {
    double total = 0.0;
    double i = 0.0;
    while (i != month ) {
        total += (sum - sum / month * i) * percent / 12 / 100 + sum / month;
        i++;
    }
    return total;
}
