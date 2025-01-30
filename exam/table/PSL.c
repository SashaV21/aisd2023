#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define SUCCES 0

typedef struct Node{
    int key;
    int PSL;
    int info;
} Node;

typedef struct Table{
    int sPSL;
    Node *ks;
    int size;
    int csize;

} Table;


int hash(int key, int size){
    return key % size;
}

Table *init(int size){
    Table *table = malloc(sizeof(Table));
    table->size = size;
    //table->csize = 0;
    table->ks = calloc(size, sizeof(Node));
    for(int i = 0; i < size; i++){
        table->ks[i].PSL = -1;
    }
    return table;
}


int addElem(Table *table, int key){
    if(table->size == table->csize) return ERROR;
    Node node;
    node.key = key;
    node.PSL = 0;
    int count = 0;
    int index = hash(key, table->size);
    for(int i = index; count < table->size; i = (i + 1) % table->size){
        if(table->ks[i].PSL == -1){
            table->ks[i].key = node.key;
            table->ks[i].PSL = node.psl;
            table->csize++;
            int s = 0;
            for(int j = 0; j < table->size; j++){
                if(table->ks[j].PSL != -1){
                    s += table->ks[j].PSL;
                }
            }
            table->sPSL = s / table->csize;
        }
        if(elem.PSL > table->ks[i].PSL){
            int bPSL = 0;
            int bkey = 0;
            bkey = table->ks[i].key;
            bPSL = table->ks[i].PSL;
            table->ks[i].key = elem.key;
            table->ks[i].PSL = elem.PSL;
            elem.PSL = bPSL;
            elem.key = bkey
        }
        elem.PSL++;
        count++;
    }
    return ERROR;
}


int find(Table *table, int key){
    int index = hash(key, table->size);
    if(table->ks[index].PSL != -1 && table->ks[index].key == key) return index;
    int n = 0, i = 0, ind = index;
    while(n < table->size){
        index = ind;
        index += (table->sPSL + i);
        if(table->ks[index].PSL != -1 && table->ks[index].key == key){
            return index;
        }
        index = ind;
        index += (table->sPSL - i);
        if(table->ks[index].PSL != -1 && table->ks[index].key == key) return index;
        n++;
        i++;
    }
    return ERROR;




}

