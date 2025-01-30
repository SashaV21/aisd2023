#include "stdio.h"
#include "stdlib.h"
#include "stack.h"

StackArr * CreateStack(int size) {
    StackArr* stack = (StackArr*)malloc(sizeof(StackArr));
    stack->array = (int*)malloc(size * sizeof(int));
    stack->top = 0;
    stack->size = size;
    return stack;
}

int Get(StackArr * stack) {
    if (stack->top == 0) {
        return -1;
    }
    return stack->array[stack->top - 1];
}

int Push(StackArr * stack, int elem) {
    if (stack->top == stack->size) {
        return 1;
    }
    stack->array[stack->top] = elem;
    stack->top++;
    return 0;
}

void StackDelete(StackArr * stack) {
    free(stack->array);
    free(stack);
}

int Pop(StackArr * stack) {
    if (stack->top == 0) {
        return 1;
    }
    stack->top--;
    return 0;
}
