#include <math.h>
#include "parser.h"

double do_calc(char *input, char *x_text, int *error);
double do_graph(char *str, double x, double scale);
int calc(t_stack *rpn, double* answer, double x);
void calc_rpn(double numTwo, double numOne, t_stack *stack, char c);
int func(char c);
void calc_func(double numOne, t_stack *stack, char c);
