#include "parser.h"

int pars_to_rpn(char* input, t_stack *rpn) {
	t_stack* stack = init_stack(0, 0);
    stack->nodes.head = stack;
    char firstChar = *input;
    int result = 0;
    int bracket = 0;
    int countNum = 0;
    int countX = 0;
    int countFunc = 0;
    int countOp = 0;
    while (*input) {
        if (is_num(*input) || is_uOperator(input, firstChar)) {
            countNum++;
            sscanf(input, "%lf", &rpn->value.num);
            while (is_num(*(input + 1))) {
                input++;
            }
            rpn->type_value = STACK_NUM;
            rpn = new_stack(rpn);
        } else if (is_x(*input)) {
            countX++;
            rpn->type_value = STACK_X;
            rpn->value.x = *input;
            rpn = new_stack(rpn);
        } else if (is_operator(*input) || is_mod(input) || is_func(input)) {
            char op;
            if (is_mod(input)) {
                countOp++;
                op = '%';
            } else if (is_func(input)) {
                countFunc++;
                op = func_name(input);
                input++;
            } else {
                countOp++;
                op = *input;
            }
            while (stack->nodes.previous != NULL && check_piority(stack->nodes.previous->value.op) >= check_piority(op)) {
                stack = stack->nodes.previous;
                destroy_stack(stack->nodes.next);
                transfer_stack(stack, rpn);
                rpn = new_stack(rpn);
            }
            stack->value.op = op;
            stack->type_value = STACK_OPERATOR;
            stack = new_stack(stack);
        } else if (*input == '(') {
            bracket++;
            stack->value.op = *input;
            stack->type_value = STACK_OPERATOR;
            stack = new_stack(stack);
        } else if (*input == ')') {
            bracket--;
            stack = stack->nodes.previous;
            stack->type_value = STACK_NO;
            destroy_stack(stack->nodes.next);
            while (stack->value.op != '(') {
                transfer_stack(stack, rpn);
                rpn = new_stack(rpn);
                stack = stack->nodes.previous;
                destroy_stack(stack->nodes.next);
            }
            stack->value.op = '\0';
            stack->type_value = STACK_NO;
            
        }
        input++;
    }
    while (stack->nodes.previous != NULL) {
        stack = stack->nodes.previous;
        destroy_stack(stack->nodes.next);
        transfer_stack(stack, rpn);
        rpn = new_stack(rpn);
    }
    free_stack(stack);
    if (bracket != 0) {
        result = 1;
    } else if ((countOp + countNum  + countX + countFunc) == 0) {
        result = 1;
    } else if(countNum == 0 && countX == 0) {
        result = 1;
    }
    return result;
}

void transfer_stack(t_stack* stack, t_stack* rpn) {
    rpn->value.op = stack->value.op;
    rpn->type_value = STACK_OPERATOR;

}

int check_piority(char op) {
    int resultPriority = priorityNone;
    if (op == '+') {
        resultPriority = priorityTwo;
    } else if (op == '(' || op == ')') {
        resultPriority = priorityOne;
    }else if (op == '-') {
        resultPriority = priorityTwo;
    } else if (op == '*') {
        resultPriority = priorityFour;
    } else if (op == '/') {
        resultPriority = priorityFour;
    } else if (op == '%') {
        resultPriority = priorityThree;
    } else if (op == '^') {
        resultPriority = priorityFive;
    } else if (strchr("sctSCTqnl", op) != NULL) {
        resultPriority = prioritySix;
    }
    return resultPriority;
}

int is_uOperator(char *input, char firstChar) {
    int result = 0;
    if (*input == '-' || *input == '+') {
        if (*input == firstChar || (!is_num(*(input - 1)) && !is_num(*(input - 2)) && !is_x(*(input - 1)) && !is_x(*(input - 1)))) {
            result = 1;
        }
    }
    return result;
}

int is_x(char c) {
    return c == 'x';
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int is_mod(char* input) {
    return !strncmp(input, "mod", 3);
}

int is_func(char* input) {
    return (!strncmp(input, "sin", 3) || !strncmp(input, "cos", 3)|| !strncmp(input, "tan", 3)|| !strncmp(input, "asin", 4)|| !strncmp(input, "acos", 4)|| !strncmp(input, "atan", 4)|| !strncmp(input, "sqrt", 3)|| !strncmp(input, "ln", 2)|| !strncmp(input, "log", 3));
}

char func_name(char* input) {
    char c;
    if (!strncmp(input, "sin", 3)) {
        c = 's';
    } else if (!strncmp(input, "cos", 3)) {
        c = 'c';
    } else if (!strncmp(input, "tan", 3)) {
        c = 't';
    } else if (!strncmp(input, "asin", 4)) {
        c = 'S';
    } else if (!strncmp(input, "acos", 4)) {
        c = 'C';
    } else if (!strncmp(input, "atan", 4)) {
        c = 'T';
    } else if (!strncmp(input, "sqrt", 4)) {
        c = 'q';
    } else if (!strncmp(input, "ln", 2)) {
        c = 'n';
    } else if (!strncmp(input, "log", 3)) {
        c = 'l';
    }
    return c;
}
