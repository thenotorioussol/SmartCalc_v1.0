#include "calc.h"

double do_calc(char *input, char *x_text, int *error) {
    t_stack* rpn = init_stack(NULL, NULL);
    *error = 0;
	rpn->nodes.head = rpn;
    double answer = 1;
    double x;
    if (x_text) {
        if (sscanf(x_text, "%lf", &x) == 1) {
            *error = pars_to_rpn(input, rpn);
            if (!*error) {
                *error = calc(rpn->nodes.head, &answer, x);
            }
        } else {
            *error = 1;
        }
    }
	free_stack(rpn);
    return answer;
}

double do_graph(char *str, double x, double scale) {
    int error;
    char x_text[256];
    sprintf(x_text, "%lf", x);
    return (scale * do_calc(str, x_text, &error));
}

int calc(t_stack *rpn, double* answer, double x) {
	t_stack* stack = init_stack(0, 0);
    stack->nodes.head = stack;
    int result = 0;
    while(rpn->nodes.next && result == 0) {
        if (rpn->type_value == STACK_NUM) {
            stack->value.num = rpn->value.num;
            stack->type_value = STACK_NUM;
        } else if (rpn->type_value == STACK_X) {
            stack->value.num = x;
            stack->type_value = STACK_NUM;
        } else if (rpn->type_value == STACK_OPERATOR) {
            if (stack->nodes.previous != NULL) {
                stack = stack->nodes.previous;
                destroy_stack(stack->nodes.next);
                double numOne = stack->value.num;
                if (func(rpn->value.op)) {
                    calc_func(numOne, stack, rpn->value.op);
                } else {
                    if (stack->nodes.previous != NULL) {
                        stack = stack->nodes.previous;
                        destroy_stack(stack->nodes.next);
                        double numTwo = stack->value.num;
                        calc_rpn(numTwo, numOne, stack, rpn->value.op);
                    } else {
                        result = 1;
                    }
                }
            } else {
                result = 1;
            }
        }
        stack = new_stack(stack);
        rpn = rpn->nodes.next;
    }
    *answer = stack->nodes.previous->value.num;
    free_stack(stack);
    return result;
}

void calc_rpn(double numTwo, double numOne, t_stack *stack, char c) {
    double num = 0.0;
    if (c == '+') {
        num = numTwo + numOne;
    } else if (c == '-') {
        num = numTwo - numOne;
    } else if (c == '*') {
        num = numTwo * numOne;
    } else if (c == '/') {
        num = numTwo / numOne;
    } else if (c == '^') {
        num = pow(numTwo, numOne);
    } else if (c == '%') {
        num = fmod(numTwo, numOne);
    }
    stack->value.num = num;
}

int func(char c) {
    int res = 0;
    if (strchr("sctSCTqnl", c) != NULL) {
        res = 1;
    }
    return res;
}

void calc_func(double numOne, t_stack *stack, char c) {
    double num = 0.0;
    if (c == 's') {
        num = sin(numOne);
    } else if (c == 'c') {
        num = cos(numOne);
    } else if (c == 't') {
        num = tan(numOne);
    } else if (c == 'S') {
        num = asin(numOne);
    } else if (c == 'C') {
        num = acos(numOne);
    } else if (c == 'T') {
        num = atan(numOne);
    } else if (c == 'q') {
        num = sqrt(numOne);
    } else if (c == 'n') {
        num = log10(numOne);
    } else if (c == 'l') {
        num = log(numOne);
    }
    stack->value.num = num;
}
