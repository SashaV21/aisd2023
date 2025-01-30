#ifndef DIALOG_H
#define DIALOG_H
#include "lab3c.h"
#include <stdio.h>

void talk(Table *tab);
int dialog(const char *msgs[]);
int D_Add(Table *),
D_Find(Table *),
D_Find_Rel(Table *),
D_Delete(Table *),
D_Show(Table *),
D_Clean(Table *),
D_Import(Table *);

#endif
