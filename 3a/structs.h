#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Item{
	int data;
	int release;
	struct Item *next;
} Item;

typedef struct KeySpace{
	char *key;
	Item *item;
	struct KeySpace *next;
} KeySpace;

typedef struct Table{
	int msize;
	int csize;
	KeySpace *ks;
} Table;

Table doNewTable(int msize);

Table initTable();

int deleteItem(KeySpace *ks, Item *item);

int deleteKeySpace(Table *table, KeySpace *ks);

int deleteTable(Table *table);

KeySpace *doNewKeySpace(char *key);

Item *doNewItem(int data);

int pushNewItem(KeySpace *ks, Item *item);

int pushNewKeySpace(Table *table, KeySpace *ks, Item *newItem);

int printTable(Table *table);

KeySpace *findKeySpace(Table *table, char *key);

Item *findItem(KeySpace *ks, int release);

KeySpace *copyKeySpace(KeySpace *sourse);

Item *copyItem(Item *sourse);


#endif
