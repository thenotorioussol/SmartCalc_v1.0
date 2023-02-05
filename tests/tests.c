
#include "tests.h"

int main(void) {
    Suite *calc = s21_calc_suite();
    SRunner *calc_runner = srunner_create(calc);
    srunner_run_all(calc_runner, CK_VERBOSE);

    Suite *credit = s21_credit_suite();
    SRunner *credit_runner = srunner_create(credit);
    srunner_run_all(credit_runner, CK_VERBOSE);

    Suite *deposit = s21_deposit_suite();
    SRunner *deposit_runner = srunner_create(deposit);
    srunner_run_all(deposit_runner, CK_VERBOSE);

    srunner_free(calc_runner);
    srunner_free(credit_runner);
    srunner_free(deposit_runner);

    return 0;
}
