
#include "tests.h"

START_TEST(calc_errors) {
    int error = 0;
    do_calc("ln(x-1", "0", &error);
    ck_assert_int_eq(error, 1);

    error = 1;
    do_calc("sin(x)", "0", &error);
    ck_assert_int_eq(error, 0);

    error = 0;
    do_calc("sin(x)", "x", &error);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_calc("sin(x)", "sin(", &error);
    ck_assert_int_eq(error, 1);

    error = 1;
    do_calc("100*sin(x)", "12.12", &error);
    ck_assert_int_eq(error, 0);

    error = 0;
    do_calc("sin()", "0", &error);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_calc("qweqdqd", "0", &error);
    ck_assert_int_eq(error, 1);

    error = 0;
    do_calc("sin(x)", "x", &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(calc_1) {
    int error = 0;
    double a = do_calc("1.25+3.45", "0", &error);
    ck_assert_double_eq_tol(a, 4.7, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 0;
    a = do_calc("0.003-15.34", "0", &error);
    ck_assert_double_eq_tol(a, -15.3370000, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 0;
    a = do_calc("    1+5    ", "0", &error);
    ck_assert_double_eq_tol(a, 6.0, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 0;
    a = do_calc("0.25*5", "0", &error);
    ck_assert_double_eq_tol(a, 1.25, 1e-7);
    ck_assert_int_eq(error, 0);
    
    error = 0;
    a = do_calc("0.2/5", "12.12", &error);
    ck_assert_double_eq_tol(a, 0.04, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 0;
    a = do_calc("5*3^2", "0", &error);
    ck_assert_double_eq_tol(a, 5 * pow(3, 2), 1e-7);
    ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc_2) {
    int error = 0;
    double a = do_calc("sin(x)", "12.3", &error);
    ck_assert_double_eq_tol(a, sin(12.3), 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("ln(x)/5", "0.1", &error);
    ck_assert_double_eq_tol(a, log10(0.1)/5, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("log(x)/5", "0.1", &error);
    ck_assert_double_eq_tol(a, log(0.1)/5, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("5^3.45", "0", &error);
    ck_assert_double_eq_tol(a, 257.8971335, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("sqrt(-10-2+15)", "12.3", &error);
    ck_assert_double_eq_tol(a, sqrt(3), 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("sqrt(x)", "-12.3", &error);
    ck_assert_double_nan(a);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("60mod3.5", "0", &error);
    ck_assert_double_eq_tol(a, 0.5, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("(5.23+1.25)*(0.25+0.001)", "0", &error);
    ck_assert_double_eq_tol(a, 1.6264800, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("cos(0.6-x+0.2/0.5)", "0.1", &error);
    ck_assert_double_eq_tol(a, 0.6216100, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("tan(x/2)", "0.8", &error);
    ck_assert_double_eq_tol(a, 0.4227932, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("asin(x)", "0.34", &error);
    ck_assert_double_eq_tol(a, asin(0.34), 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("acos(x)", "-0.83", &error);
    ck_assert_double_eq_tol(a, 2.5499040, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("atan(-0.669)", "0", &error);
    ck_assert_double_eq_tol(a, -0.5896162, 1e-7);
    ck_assert_int_eq(error, 0);

    error = 1;
    a = do_calc("cos(sin(tan(-0.005)))", "0", &error);
    ck_assert_double_eq_tol(a, 0.9999875, 1e-7);
    ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(graph_1) {
    double scale = 5.0;
    double a = do_graph("(x+5)/10", 7, scale);
    ck_assert_double_eq_tol(a, ((7.0+5.0)/10.0) * scale, 1e-7);
    
}
END_TEST


Suite *s21_calc_suite(void) {
    Suite *suite;

    suite = suite_create("s21_calc");
    TCase *tcase_core = tcase_create("Core");

    tcase_add_test(tcase_core, calc_errors);
    tcase_add_test(tcase_core, calc_1);
    tcase_add_test(tcase_core, calc_2);
    tcase_add_test(tcase_core, graph_1);

    suite_add_tcase(suite, tcase_core);

    return suite;
}
