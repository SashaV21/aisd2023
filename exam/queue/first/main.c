#include <stdio.h>
#include <stdlib.h>


typedef struct Queue{
    unsigned int tail, head, size;
    unsigned int *data;
} Queue;



Queue *makeQueue(unsigned int size){
    //printf("!!\n");
    Queue *newQueue = malloc(sizeof(Queue));
    newQueue->head = newQueue->tail = 0;
    newQueue->size = size;
    newQueue->data = malloc(size * sizeof(unsigned int));
    return newQueue;
}

void freeQueue(Queue *target){
    free(target->data);
    free(target);
}

void printQueue(Queue *target){
    printf("%d\n", target->size);
    for(unsigned int i = 0; i < target->size; i++){
        printf("%d ", target->data[i]);
    }
    printf("\n");
}

unsigned int* pop(Queue *target){
    if(!target) return NULL;
    if(!target->data) return NULL;
    unsigned int *result = NULL;
    unsigned int size_of_pop = 0;
    size_of_pop = target->data[target->head];
    result = calloc(size_of_pop * 2 + 1, sizeof(unsigned int));
    result[0] = size_of_pop;
    target->head = (target->head + 1) % target->size;
    unsigned int i = 1;
    for(i = 1; i < size_of_pop * 2; i++){
        result[i] = target->data[target->head];
        target->head = (target->head + 1) % target->size;
   
    }
    target->head = (target->head + 1) % target->size;
    return result;
}

void push(Queue *target, unsigned int *data){
    //printf("!!\n");
    unsigned int dist = target->size - target->tail + target->head;
    /*if(target->size < data[0]){
        printf("Ti tupoy\n");
        return 1;
    }*/
    while(dist < data[0]){
        free(pop(target));
        dist = target->size - target->tail + target->head;
    }
    unsigned int size_of_push = data[0];
    target->data[target->tail] = size_of_push;
    target->tail = (target->tail + 1) % target->size;
    unsigned int start_of_push = target->tail;
    int count = 1;
    for(int i = start_of_push; i < start_of_push + size_of_push * 2; i++){
        target->data[target->tail] = data[count];
        target->tail = (target->tail + 1) % target->size;
        count++;
    }

}


int main(){
    //printf("!!\n");
    Queue *q = makeQueue(10);
    unsigned int *data1 = malloc(sizeof(unsigned int) * 7);
    data1[0] = 3;
    for(int i = 1; i < 7; i++){
        data1[i] = 1;
    }
    //printf("11");
    push(q, data1);
    printQueue(q);
       unsigned int *data = malloc(sizeof(unsigned int) * 9);
    data[0] = 4;
    for(int i = 1; i < 9; i++){
        data[i] = 2;
    }
    push(q, data); 
   
    printQueue(q);
    unsigned int* arr = calloc(10, sizeof(unsigned int));
    arr = pop(q);
    for(int i = 0; i < 9; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    
    
    return 0;
}
