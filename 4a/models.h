#ifndef MODELS_H
#define MODELS_H
#include "structs.h"

int insert(Tree *tree, unsigned int key, unsigned int data);
int bypass(Tree *tree, unsigned int key);
int delete(Tree *tree, Node *target);
arrayOfNodes *search(Tree *tree, unsigned int key);

#endif
