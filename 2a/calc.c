#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack_list.h"
#include "utils.h"

#define FAILURE 0 
#define SUCCESS 1 
#define DELIM " \t"
#define PLUS 1
#define MINUS 2
#define MULT 3
#define DIV 4

int is_oper(const char *str){
	if(strcmp(str, "+") ==  0)
		return PLUS;
	if(strcmp(str, "-") ==  0)
		return MINUS;
	if(strcmp(str, "*") ==  0)
		return MULT;
	if(strcmp(str, "/") ==  0)
		return DIV;
	return FAILURE;
}

int is_operd(const char *str, int *operand){
	int str_len = strlen(str);
	const char val[11] = "0123456789";
	for(int i  = 0; i < str_len; i++){
		if(!strchr(val, str[i])){
			return FAILURE;
		}
	}
	*operand = atoi(str);
	return SUCCESS;
}

int calc(Stack *stack, char *str){
	char *copy = strdup(str), *word = strtok(copy, DELIM);
	int (*fptr[])(int f_oper, int s_oper, int *res) = {NULL, to_summ, to_dif, to_mult, to_div};	

	int operation = 0,
		operand = 0;
	int res = 0;
	while(word != NULL){
		if((operation = is_oper(word)) > 0){
			if(stack->size < 2){
				free(copy);
				return FAILURE;
			}
			Item* f_oper = pop(stack);
			Item* s_oper = pop(stack);
			if(fptr[operation](f_oper->value, s_oper->value, &res))
				push(stack, res);
			else{
				free(f_oper);
				free(s_oper);
				free(copy);
				return FAILURE;
			}
			free(f_oper);
			free(s_oper);

		} else if(is_operd(word, &operand)){
			push(stack, operand);
		} else{
			printf("ILLEGAL STRING\n");
			free(copy);
			return FAILURE;
		}
		word = strtok(NULL, DELIM);
	}

	free(copy);
	if(stack->size != 1)
		return FAILURE;
	Item* res1;
	res1 = pop(stack);

	printf("RESULT: %d\n", res1->value);
	free(res1);
	free(word);
	
	return SUCCESS;
}
