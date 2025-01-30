#include <stdio.h>
#include <stdlib.h>

#include "stack_list.h"

#define SUCCESS 1
#define FAILURE 0

Stack *init(){
	return (Stack *) calloc(1, sizeof(Stack));
}

void delete(Stack *stack){
	Item *ptr = stack->head, *ptr_prev = NULL;
	stack->size = 0;
	while(ptr){
		ptr_prev = ptr;
		ptr = ptr->next;
		free(ptr_prev);
	}
	free(stack);
}

int push(Stack *stack, int value){
	Item *ptr = calloc(1, sizeof(Item)), //Item value
		 *tmp = NULL;

	ptr->value = value;

	if(!stack->head){
		stack->head = ptr;
		stack->size++;
		return SUCCESS;
	}

	tmp = stack->head;
	stack->head = ptr;
	ptr->next = tmp;
	stack->size++;
	return SUCCESS;
}

Item *pop(Stack *stack){
	if(!stack)
		return NULL;

	Item *ptr = stack->head;
	//Item *buf = ptr;
	stack->head = stack->head->next;
	ptr->next = NULL;
	stack->size--;
	//free(buf);
	return ptr;
}

/*void print(Stack *stack){
	Item *ptr = stack->head;
	printf("STACK SIZE: %d\n", stack->size);
	while(ptr){
		printf("{%d}-->", ptr->value);
		ptr = ptr->next;
	}
	printf("NULL\n");
}*/
