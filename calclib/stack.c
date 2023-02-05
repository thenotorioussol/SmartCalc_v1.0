#include "stack.h"

t_stack* init_stack(t_stack *prev, t_stack *head) {
    t_stack* stack = (t_stack*) malloc(sizeof(t_stack));
    stack->nodes.head = head;
    stack->nodes.previous = prev;
    stack->nodes.next = NULL;
    stack->type_value = STACK_NO;
    return stack;
}

t_stack* new_stack(t_stack* stack) {
    t_stack* new_stack = init_stack(stack, stack->nodes.head);
    stack->nodes.next = new_stack;
    return new_stack;
}

void free_stack(t_stack* stack) {
    t_stack* tmp = stack->nodes.head;
    stack = stack->nodes.head;
    while (stack) {
        tmp = stack->nodes.next;
        free(stack);
        stack = tmp;
    }
}

void destroy_stack(t_stack* stack) {
    stack->nodes.previous->nodes.next = NULL;
    free(stack);
}

int is_num(char c) {
    int result = 0;
    if (('0' <= c && c <= '9') || c == '.') {
        result = 1;
    }
    return result;
}

void print_stack(t_stack* stack) {
    t_stack *tmp = stack->nodes.head;
    while (tmp != NULL) {
        if (tmp->type_value == STACK_NUM) {
            printf("%lf ", tmp->value.num);
        } else if (tmp->type_value == STACK_OPERATOR) {
            printf("%c ", tmp->value.op);
        } else if (tmp->type_value == STACK_X) {
            printf("%c ", tmp->value.x);
        }
        tmp = tmp->nodes.next;
    }
    printf("\n");
}
