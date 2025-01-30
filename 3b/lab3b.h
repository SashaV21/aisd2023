#ifndef LAB3B_H
#define LAB3B_H
#include <stdio.h>

typedef struct Node{
	int ofset;
	int busy;
	char *key;
	int edition;
	struct Node *next;
}Node;

typedef struct Table{
	FILE *file;
	char* name;
	Node *ks;
}Table;

Table* load(char*);
int tab_add(Table *, char*, int);
int tab_remove(Table *, char*);
int tab_remove_ed(Table *, char*, int);
int tab_find(Table *, char*);
int tab_find_ed(Table *, char*, int);
void tab_print(Table *tab);
void free_tab(Table*);
int get_int(int*);
char* get_str();
#endif
