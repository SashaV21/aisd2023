#ifndef QUEUE_H
#define QUEUE_H

typedef struct Item {
    int data;
    struct Item *next;
} Item;

typedef struct Queue {
    Item *head;
    Item *tail;
} Queue;

typedef struct {
    int* visit;
}Vector;

Queue *queue_new();

void queue_delete(Queue *queue);

int queue_put(Queue *queue, int data);

int queue_get(Queue *queue, int *output);

void queue_print(const Queue *queue);

#endif
