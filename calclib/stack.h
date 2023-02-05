#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    STACK_NO,
    STACK_OPERATOR,
    STACK_NUM,
    STACK_X,
} t_type_value;

enum {
    priorityNone,
    priorityOne,
    priorityTwo,
    priorityThree,
    priorityFour,
    priorityFive,
    prioritySix,
};

typedef struct t_node {
	struct t_stack *previous;
	struct t_stack *next;
	struct t_stack *head;
} t_node;

typedef struct t_stack {
    union value {
        double num;
        char op;
        char x;
    } value;
    t_type_value type_value;
	t_node nodes;
} t_stack;


t_stack* init_stack(t_stack *prev, t_stack *head);
t_stack* new_stack(t_stack* stack);
void free_stack(t_stack* stack);
void destroy_stack(t_stack* stack);
int is_num(char c);
void print_stack(t_stack* stack);