#include <stdio.h>
#include <stdlib.h>


typedef struct Stack{
    int top;
    int* data;
    int size;
} Stack;

#define ERROR 1


Stack *init(int size){
    Stack *stack = malloc(sizeof(Stack));
    stack->top = 0;
    stack->size = size;
    stack->data = malloc(sizeof(int) * size);
    return stack;
}

int pop(Stack *stack, int num){
    int n = 0;
    if(stack->top == 0){
        return ERROR;
    }
    stack->top = stack->top - 1;
    num = stack->data[stack->top];
    return num;
}

int push(Stack *stack, int num){
    if(stack->top == stack->size) return ERROR;
    stack->data[stack->top] = num;
    stack->top++;
    return 0;
}

void printStack(Stack *stack){
    for(int i = 0; i < stack->size; i++){
        printf("%d ", stack->data[i]);
    }
}

void freeStack(Stack *stack){
    free(stack->data);
    free(stack);
}


int main(){
    Stack *stack = init(10);
    for(int i = 0; i < stack->size; i++){
        push(stack, i);
    }
    int num = 0;
    pop(stack, num);
    push(stack, 23);
    printStack(stack);
    freeStack(stack);
    return 0;
}
