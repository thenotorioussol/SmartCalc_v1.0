#ifndef SRC_C_TESTS_TESTS_H_
#define SRC_C_TESTS_TESTS_H_

#include <check.h>

#include "../calclib/calc.h"
#include "../banklib/credit.h"
#include "../banklib/deposit.h"

Suite *s21_credit_suite(void);
Suite *s21_calc_suite(void);
Suite *s21_deposit_suite(void);

#endif  // SRC_C_TESTS_TESTS_H_
