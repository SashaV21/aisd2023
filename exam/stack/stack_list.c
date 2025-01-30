#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct Stack{
    Node *head;
} Stack;


Node *initNode(int data){
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Stack *initStack(){
    Stack *stack = malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

int pop(Stack *stack, int data){
    if(stack->head == NULL) return 1;
    data = stack->head->data;
    Node *x = q->head;
    q->head = q->head->next;
    free(x);
    return data;
}

int push(Stack *stack, int data){
    Node* node = initNode(data);
    if(stack->head == NULL){
        stack_head = node;
        return 0;
    }
    Node *x = stack->head;
    stack->head = node;
    stack->head->next = x;
    return 0;

}
