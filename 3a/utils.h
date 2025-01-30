#ifndef UTILS_H
#define UTILS_H
#include "structs.h"
#include <stdio.h>

int getInt(int* value, char *prompt);
int getRecord(Table *table, char *string);
int setRecord(FILE *file, Table *table);
int isTableOverflow(Table *table);
int isTableEmpty(Table *table);

#endif
