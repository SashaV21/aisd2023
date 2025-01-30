#ifndef STACK_LIST_H
#define STACK_LIST_H

typedef struct Item{
	int value;
	struct Item *next;
} Item;

typedef struct Stack{
	int size;
	Item *head;
} Stack;

Stack *init();
void delete(Stack *stack);

int push(Stack *stack, int value);
Item *pop(Stack *stack);

//void print(Stack *stack);

#endif
