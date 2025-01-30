
#include <stdio.h>
#include <stdlib.h>

#define NUM 2

typedef struct Queue{
    int *data;
    int size;
    int csize;
    int head;
    int tail;
} Queue;


Queue* MakeQueue(int size){
	Queue *new = malloc(sizeof(Queue));
	new->size = size;
	new->data = calloc(size, sizeof(int));
	new->tail = new->head = new->csize = 0;
}

Queue *makeQueue(int size){
    //printf("!!\n");
    Queue *newQueue = malloc(sizeof(Queue));
    newQueue->head = newQueue->tail = 0;
    newQueue->size = size;
    newQueue->data = malloc(size * sizeof(int));
    return newQueue;
}

int* pop(Queue *target){
    if(!target) return NULL;
    if(!target->data) return NULL;
    int *result = NULL;
    int size_of_pop = 0;
    size_of_pop = target->data[target->head];
    result = calloc(size_of_pop * 2 + 1, sizeof(int));
    result[0] = size_of_pop;
    target->head = (target->head + 1) % target->size;
    int i = 1;
    for(i = 1; i < size_of_pop * 2; i++){
        result[i] = target->data[target->head];
        target->head = (target->head + 1) % target->size;
   
    }
    target->head = (target->head + 1) % target->size;
    return result;
}

void push(Queue *target, int *data){
    //printf("!!\n");
    int dist = target->size - target->tail + target->head;
    /*(if(target->size < data[0]){
        printf("Ti tupoy\n");
        return 1;
    }*/
    while(dist < data[0]){
        free(pop(target));
        dist = target->size - target->tail + target->head;
    }
    int size_of_push = data[0];
    target->data[target->tail] = size_of_push;
    target->tail = (target->tail + 1) % target->size;
    int start_of_push = target->tail;
    int count = 1;
    for(int i = start_of_push; i < start_of_push + size_of_push * 2; i++){
        target->data[target->tail] = data[count];
        target->tail = (target->tail + 1) % target->size;
        count++;
    }

}



/*int *pop(Queue *q){
    int* res = NULL;
    if(!q) return NULL;
    if(!q->data) return NULL;
    if(q->csize == 0) return NULL;
    int num_of_cords = q->data[q->head];
    res = malloc(sizeof(int) * (num_of_cords * 2 + 1));
    res[0] = num_of_cords;
    q->head = (q->head + 1) % q->size;
    for(int i = 1; i < num_of_cords * 2; i++){
        res[i] = q->data[q->head];
        q->head = (q->head + 1) % q->size;
    }
    q->head = (q->head + 1) % q->size;
    q->csize = q->csize +  num_of_cords * 2 + 1;
    return res;
}


void push(Queue *q, int* data){
    int dist = q->size - q->tail + q->head;
    int size_of_push = data[0] * 2 + 1;
    while(size_of_push > dist){
        if(size_of_push > q->size){
            printf("FATAL ERROR");
            break;
        }
        free(pop(q));
        dist = q->size - q->tail + q->head;
    }
    q->data[q->tail] = data[0];
    q->tail = (q->tail + 1) % q->size;
    for(int i = 1; i < size_of_push; i++){
        q->data[q->tail] = data[i];
        q->tail = (q->tail + 1) % q->size;
    }

}
*/


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

int main(){
    //printf("!!\n");
    Queue *q = makeQueue(10);
    int *data1 = malloc(sizeof(int) * 7);
    data1[0] = 3;
    for(int i = 1; i < 7; i++){
        data1[i] = 1;
    }
    //printf("11");
    push(q, data1);
    printQueue(q);
       int *data = malloc(sizeof(int) * 9);
    data[0] = 4;
    for(int i = 1; i < 9; i++){
        data[i] = 2;
    }
    push(q, data); 
   
    printQueue(q);
    int* arr = calloc(10, sizeof(int));
    arr = pop(q);
    for(int i = 0; i < 9; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    
    
    return 0;
}

/*int main(){
    Queue *q = MakeQueue(10);
    int *data1 = malloc(7 * sizeof(int));
    data1[0] = 3;
    for(int i = 1; i < 7; i++){
        data1[i] = 1;
    }
    push(q, data1);
    printQueue(q);
    int* data2 = malloc(9 * sizeof(int));
    for(int i = 1; i < 9; i++){
        data2[i] = 2;
    }
    push(q, data2);
    printQueue(q);
    free(data1);
    free(data2);
    freeQueue(q);
    return 0;
}#include <stdio.h>
#include <stdlib.h>


typedef struct Queue{
    unsigned int tail, head, size;
    unsigned int *data;
} Queue;



*/

