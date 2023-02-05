#include "tests.h"

START_TEST(deposit_cap) {
    t_deposit res;
    int error = 1;
    res = do_deposit("100000", "24", "15", "0", "1", 1, &error);
    ck_assert_int_eq(res.percentSum, 34735);
    ck_assert_int_eq(res.taxSum, 0);
    ck_assert_int_eq(res.totalSum, 134735);

    error = 1;
    res = do_deposit("1200000", "24", "17", "0", "3", 1, &error);
    ck_assert_int_eq(res.percentSum, 474132);
    ck_assert_int_eq(res.taxSum, 0);
    ck_assert_int_eq(res.totalSum, 1674132);

    error = 1;
    res = do_deposit("1101001", "12", "13", "13", "6", 1, &error);
    ck_assert_int_eq(res.percentSum, 147782);
    ck_assert_int_eq(res.taxSum, 19212);
    ck_assert_int_eq(res.totalSum, 1248783);

    error = 1;
    res = do_deposit("13131313", "12", "15", "13", "12", 1, &error);
    ck_assert_int_eq(res.percentSum, 1969697);
    ck_assert_int_eq(res.taxSum, 256061);
    ck_assert_int_eq(res.totalSum, 15101010);
}
END_TEST

START_TEST(deposit_nocap) {
    t_deposit res;
    int error = 1;
    res = do_deposit("100000", "24", "15", "0", "1", 0, &error);
    ck_assert_int_eq(res.percentSum, 30000);
    ck_assert_int_eq(res.taxSum, 0);
    ck_assert_int_eq(res.totalSum, 100000);

    error = 1;
    res = do_deposit("1200000", "24", "17", "0", "3", 0, &error);
    ck_assert_int_eq(res.percentSum, 408000);
    ck_assert_int_eq(res.taxSum, 0);
    ck_assert_int_eq(res.totalSum, 1200000);

    error = 1;
    res = do_deposit("1101001", "12", "13", "13", "6", 0, &error);
    ck_assert_int_eq(res.percentSum, 143130);
    ck_assert_int_eq(res.taxSum, 18607);
    ck_assert_int_eq(res.totalSum, 1101001);

    error = 1;
    res = do_deposit("13131313", "12", "15", "13", "12", 0, &error);
    ck_assert_int_eq(res.percentSum, 1969697);
    ck_assert_int_eq(res.taxSum, 256061);
    ck_assert_int_eq(res.totalSum, 13131313);
}
END_TEST

START_TEST(deposit_error) {
    int error = 0;
    do_deposit("-12", "12", "12", "12", "12", 0, &error);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_deposit("12", "-12", "12", "12", "12", 0, &error);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_deposit("12", "12", "-12", "12", "12", 0, &error);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_deposit("12", "12", "12", "-12", "12", 0, &error);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_deposit("12", "12", "12", "12", "-12", 0, &error);
    ck_assert_int_eq(error, 1);

    error = 1;
    do_deposit("0", "12", "12", "12", "12", 0, &error);
    ck_assert_int_eq(error, 0);
}
END_TEST



Suite *s21_deposit_suite(void) {
    Suite *suite;

    suite = suite_create("s21_deposit");
    TCase *tcase_core = tcase_create("Core");

    tcase_add_test(tcase_core, deposit_cap);
    tcase_add_test(tcase_core, deposit_nocap);
    tcase_add_test(tcase_core, deposit_error);

    suite_add_tcase(suite, tcase_core);

    return suite;
}
