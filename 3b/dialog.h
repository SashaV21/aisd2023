#ifndef DIALOG_H
#define DIALOG_H
#include "lab3b.h"
#include <stdio.h>

int dialog(const char *msgs[]);
int D_Add(Table *),
D_Delete(Table *),
D_Delete_Edition(Table *),
D_Find(Table *),
D_Find_Edition(Table *),
D_Show(Table *);

#endif
