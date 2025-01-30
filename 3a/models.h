#ifndef MODELS_H
#define MODELS_H
#include <stdio.h>
#include "structs.h"

int add(Table *table, char* key, int data);
int delete(Table *table, char* key, int release);
KeySpace *find(Table *table, char* key, int release);
int import(Table *table, FILE *file);
int fget_int(FILE*, int*);
char* fget_str();

#endif
