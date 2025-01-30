#ifndef VIEWS_H
#define VIEWS_H
#include "structs.h"

char *get_str();
int D_add(Table *table);
int D_find(Table *table);
int D_delete(Table *table);
int D_import(Table *table);
int D_export(Table *table);

#endif
