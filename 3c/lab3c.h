#ifndef LAB3C_H
#define LAB3C_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
	int rel;
	unsigned int info;
	struct Item* next;
}Item;

typedef struct KeySpace{
	char* key;
	Item *info;
	struct KeySpace* next;
}KeySpace;

typedef struct Table{
	int size;
	int msize;
	KeySpace** ks;
}Table;

Table *make_tab();
int tab_add(Table *,char*, int);
int tab_add_rel(KeySpace* , int);
int tab_print(Table *);
int tab_remove(Table *,char*);
int tab_import(Table *, FILE *);
KeySpace* tab_find(Table *, char*);
int hash(char*, int);
void tab_del(Table*);
void tab_clean(Table*);
int get_int(int*);
int fget_int(FILE *, int*);
char *get_str();
char *fget_str(FILE*);

#endif
