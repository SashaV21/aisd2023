#ifndef _dialog_
#define _dialog_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"
#include "workfile.h"
#include <stdbool.h>


int dialog (const char *msgs[], int N);
int D_load(Node_t **root);
int D_Add(Node_t **root);
int D_Delete(Node_t **root);
int D_Find(Node_t **root);
int D_SpecialFind(Node_t **root);
int D_Show(Node_t **root);
int D_Timing();
int D_PrintTree(Node_t **root);

#endif
