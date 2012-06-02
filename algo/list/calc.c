#include <stdio.h>
#include <assert.h>

#define BUF_SIZE 4096

typedef int Element;
typedef int Bool;

#define TRUE 1;
#define FALSE 0;

/*
 * Stack Implement.
 */
struct Stack {
	Element storage[BUF_SIZE];
	int top;
};

struct Stack *stack_init(int size) {
	struct Stack *n = (struct Stack *)malloc(sizeof(struct Stack));
	n->top = -1;
	return n;
}

void stack_finalize(struct Stack *stack) {
	assert(stack != NULL);
	free(stack);
}

Bool stack_push(struct Stack *stack, Element data) {
	assert(stack != NULL);

	if (stack->top >= BUF_SIZE) {
		return FALSE;
	}

	stack->top++;
	stack->storage[stack->top] = data;

	return TRUE;
}

Bool stack_is_empty(struct Stack *stack) {
	return stack->top == -1;
}

Bool stack_pop(struct Stack *stack) {
	assert(stack != NULL);

	if (stack->top <= -1) {
		return FALSE;
	}

	stack->top--;
	return TRUE;
}

Element stack_top(struct Stack *stack) {
	assert(stack->top != -1);
	return stack->storage[stack->top];
}


/*
 * operator priority level table.
 */
int operator_table[][7] = 
{
 ' ', '+', '-', '*', '/', '(', ')',
 '+',  0 ,  0 , -1 , -1 ,  1 , -1 ,
 '-',  0 ,  0 , -1 , -1 ,  1 , -1 ,
 '*',  1 ,  1 ,  0 ,  0 ,  1 , -1 ,
 '/',  1 ,  1 ,  0 ,  0 ,  1 , -1 ,
 '(',  1 ,  1 ,  1 ,  1 ,  0 , -1 ,
 ')', -1 , -1 , -1 , -1 , -1 ,  0 
};

/*
 * cast operator to table index for search priority
 */
enum Operator {
	add = 1,
	sub = 2,
	mult = 3,
	div = 4,
	left = 5,
	right = 6	
};

void init_op_table(int *table) {
	table['+'] = 1;
	table['-'] = 2;
	table['*'] = 3;
	table['/'] = 4;
	table['('] = 5;
	table[')'] = 6;
}

int op_data[256];

int compare_operator(char op1, char op2) {
	
	return operator_table[op_data[op1]][op_data[op2]];
}

int execute_calc(int left, int right, char sign) {
	switch (sign) {
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		return left / right;
	default:
		
		assert("unknown operator!");
	}
}

/*
 * the logic is not very clear.
 */
void mid_cast_last_expr(const char *mid_expr, char *last_expr) {
	assert((mid_expr != NULL) && (last_expr));
	int i = 0;
	int j = 0;
	struct Stack *op = stack_init(BUF_SIZE);
	char tmp_op = '\0';

	for (i = 0; i < strlen(mid_expr); ) {
		if (isdigit(mid_expr[i])) {
			last_expr[j] = mid_expr[i];
			j++;
			i++;
		}
		else {
			if (stack_is_empty(op)) { // if stack is empty, just push op to stack.
				if (mid_expr[i] != ')') {
					stack_push(op, mid_expr[i]);
				}

				i++;
				continue;
			}

			if ((mid_expr[i] == ')') && (stack_top(op) == '(')) { //if ')' compare with '('. just pop '('
				stack_pop(op);
				i++;
				continue;
			}

			if (compare_operator(mid_expr[i], stack_top(op)) < 0) {
				tmp_op = stack_top(op);
				last_expr[j] = stack_top(op);
				j++;
				stack_pop(op);
			}
			else {
				if (mid_expr[i] != ')') { // ')' never push in stack.
					stack_push(op, mid_expr[i]);
				}

				i++;
			}
		}
	}


	// pop all operator to output.
	while (!stack_is_empty(op)) {
		tmp_op = stack_top(op);

		if (tmp_op != '(') {
			last_expr[j] = stack_top(op);
			j++;
		}

		stack_pop(op);
	}
	
	stack_finalize(op);
}

int calc_last_expr(const char *last_expr) {
	assert(last_expr != NULL);
	int i = 0;
	struct Stack *data = stack_init(BUF_SIZE);
	char num[2] = {0};
	int right = 0;
	int left = 0;
	int ret = 0;

	for (i = 0; i < strlen(last_expr); i++) {
		if (isdigit(last_expr[i])) {
			num[0] = last_expr[i];
			stack_push(data, atoi(num));
		}
		else {
			right = stack_top(data);
			stack_pop(data);
			left = stack_top(data);
			stack_pop(data);
			
			stack_push(data, execute_calc(left, right, last_expr[i]));
		}
	}
	
	ret = stack_top(data);	
	stack_finalize(data);
	return ret;
}

int main(int argc, char **argv) {
	char mid_expr[BUF_SIZE] = {'\0'};
	char last_expr[BUF_SIZE] = {'\0'};
	int ret = 0;

	init_op_table(op_data);

	scanf("%s", mid_expr);

	mid_cast_last_expr(mid_expr, last_expr);

	printf("%s\n", last_expr);

	ret = calc_last_expr(last_expr);

	printf("final result: %d\n", ret);	
	return 0;
}
