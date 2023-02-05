#include <ctype.h>
#include "stack.h"

int pars_to_rpn(char* input, t_stack* rpn);
void transfer_stack(t_stack* stack, t_stack* rpn);
int check_piority(char op);
int is_uOperator(char *input, char firstChar);
int is_operator(char c);
int is_x(char c);
int is_mod(char* input);
int is_func(char* input);
char func_name(char* input);
