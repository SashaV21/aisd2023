#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Queue{
    unsigned int head, tail, size;
    unsigned char* data;
} Queue;

typedef struct Pack{
    unsigned char* mac_p;
    unsigned char* mac_s;
    unsigned char* data_len;
    unsigned char* data;
    unsigned char* control_summ;
} Pack;

#define MAC 6
#define DATA_LEN 2
#define MIN_DATA 64
#define MAX_DATA 1500
#define CONTROL_S 4
#define SUCCES 0
#define ERROR INT_MAX
#define NO_SPACE 1

Pack* makepack(){
    Pack* new = malloc(sizeof(Pack));
    new->mac_p = new->mac_s = NULL;
    new->data_len = new->data = NULL;
    new->control_summ - NULL;
    return new;
}

unsigned char *getMac(Queue *source){
    unsigned char* res = malloc(sizeof(unsigned char) * MAC);
    for(int i = 0; i < MAC; i++){
        res[i] = source->data[source->head];
        surce->head = (source->head + 1) % source->size;
    }
    return res;
}

int getDataLen(Queue *q, unsigned char** data_len){
    int lenght = 0;
    unsigned char* local = malloc(sizeof(unsigned char) * DATA_LEN);
    for(int i = 0; i < DATA_LEN; i++){
        local[i] = q->data[q->head];
        q->head = (q->head + 1) % q->size;
    }
    *data_len = local;
    lenght = atoi((const char*)local);
    if(lenght < MIN_DATA || lenght > MAX_DATA) return ERROR;
    return lenght;

}

unsigned char *data(Queue* q, int lenght){
    unsigned char *res = malloc(lenght * sizeof(unsigned char));
    for(int i = 0; i < lenght; i++){
        res[i] = q->data[q->head];
        q->head = (q->head + 1) % q->size;
    }
    return res;
}

unsigned char *getCS(Queue* q){
    unsigned char *res = malloc(CONTROL_S * sizeof(unsigned char));
    for(int i = 0; i < CONTROL_S; i++){
        res[i] = q->data[q->head];
        q->head = (q->head + 1) % q->size;
    }
    return res;
}

Pack *pop(Queue *q){
    Pack* result_pack = makepack();
    result_pack->mac_p = getMac(q);
    result_pack->mac_s = getMac(q);
    unsigned char *data_len = NULL;
    int leigth = getDataLen(q, &data_len);
    result_pack->data_len = data_len;
    if(leight = ERROR) return 1;
    result_pack->data = getData(q, lenght);
    result_pack->control_summ = getCS(q);
    return result_pack;
}


void pushByte(Queue *q, unsigned char byte){
    q->data[q->tail] = byte;
    q->tail = (q->tail + 1) % q->size;
}


void push(Queue *q, Pack* pack){
    unsigned int dist = q->size - q->tail + q->head;
    unsigned int pack_len = MAC * 2 + DATA_LEN + atoi((const char*)pack->data_len) + CONTROL_S;
    if(dist < pack_len) return NO_SPACE;
    for(int i = 0; i < MAC; i++){
        pushByte(q, pack->mac_s[i]);
    }

}
