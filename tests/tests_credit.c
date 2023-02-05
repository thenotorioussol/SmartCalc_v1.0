
#include "tests.h"

START_TEST(credit_auf) {
    t_credit res;
    int error = 1;
    res = do_credit("100000", "15", "24", &error, 0);
    ck_assert_int_eq(res.paymentOne, 4849);
    ck_assert_int_eq(res.overpayment, 16368);
    ck_assert_int_eq(res.total, 116368);

    error = 1;
    res = do_credit("12000000", "6", "12", &error, 0);
    ck_assert_int_eq(res.paymentOne, 1032797);
    ck_assert_int_eq(res.overpayment, 393566);
    ck_assert_int_eq(res.total, 12393566);

    error = 1;
    res = do_credit("880000", "8.5", "9", &error, 0);
    ck_assert_int_eq(res.paymentOne, 101273);
    ck_assert_int_eq(res.overpayment, 31460);
    ck_assert_int_eq(res.total, 911460);

    error = 1;
    res = do_credit("900900", "17", "120", &error, 0);
    ck_assert_int_eq(res.paymentOne, 15657);
    ck_assert_int_eq(res.overpayment, 977992);
    ck_assert_int_eq(res.total, 1878892);
}
END_TEST

START_TEST(credit_dif) {
    t_credit res;
    int error = 1;
    res = do_credit("1000000", "12", "12", &error, 1);
    ck_assert_int_eq(res.paymentOne, 93333);
    ck_assert_int_eq(res.paymentLast, 84167);
    ck_assert_int_eq(res.overpayment, 65000);
    ck_assert_int_eq(res.total, 1065000);

    error = 1;
    res = do_credit("13131313", "13.13", "13", &error, 1);
    ck_assert_int_eq(res.paymentOne, 1153779);
    ck_assert_int_eq(res.paymentLast, 1021153);
    ck_assert_int_eq(res.total, 14137062);
    ck_assert_int_eq(res.overpayment, 1005749);

    error = 1;
    res = do_credit("750000", "1", "4", &error, 1);
    ck_assert_int_eq(res.paymentOne, 188125);
    ck_assert_int_eq(res.paymentLast, 187656);
    ck_assert_int_eq(res.overpayment, 1563);
    ck_assert_int_eq(res.total, 751563);

    error = 1;
    res = do_credit("5555000", "3.9", "108", &error, 1);
    ck_assert_int_eq(res.paymentOne, 69489);
    ck_assert_int_eq(res.paymentLast, 51602);
    ck_assert_int_eq(res.overpayment, 983929);
    ck_assert_int_eq(res.total, 6538929);
}
END_TEST

START_TEST(credit_error) {
    int error = 0;
    do_credit("-12", "12", "12", &error, 1);
    ck_assert_int_eq(error, 1);
    
    error = 0;
    do_credit("12", "-12", "12", &error, 1);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_credit("12", "11", "-12", &error, 1);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_credit("", "0", "0", &error, 1);
    ck_assert_int_eq(error, 1);
    error = 0;
}
END_TEST



Suite *s21_credit_suite(void) {
    Suite *suite;

    suite = suite_create("s21_credit");
    TCase *tcase_core = tcase_create("Core");

    tcase_add_test(tcase_core, credit_auf);
    tcase_add_test(tcase_core, credit_dif);
    tcase_add_test(tcase_core, credit_error);

    suite_add_tcase(suite, tcase_core);

    return suite;
}
