#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "utils.h"

#define SUCCESS 1
#define FAILURE 0

Table doNewTable(int msize){
	int csize = 0;
	Table newTable = {msize, csize, NULL};
	return newTable;
}

Table initTable(){
	int msize = 0;
	int res = getInt(&msize ,"ENTER TABLE SIZE -->");
	if(res == -1){
		Table newTable = doNewTable(-1);
		return newTable;	
	} 
	Table newTable = doNewTable(msize);
	return newTable;	
}

KeySpace *doNewKeySpace(char *key){
	KeySpace *newKeySpace = calloc(1, sizeof(KeySpace));
	newKeySpace->key = key;
	return newKeySpace;
}

Item *doNewItem(int data){
	Item *newItem = calloc(1, sizeof(Item));
	newItem->data = data;
	newItem->release = 0;
	return newItem;
}

int pushNewItem(KeySpace *ks, Item *newItem){
	if(!ks){
		printf("KEYSPACE WAS NOT FOUND FOR PUSH\n");
		return FAILURE;
	}
	if(!newItem){
		printf("NEW ITEM WAS NOT FOUND FOR PUSH\n");
		return FAILURE;
	}
	if(!ks->item){
		ks->item = newItem;

		return SUCCESS;
	}
	Item *tmp = ks->item;
	newItem->release = ks->item->release + 1;
	ks->item = newItem;
	ks->item->next = tmp;
	return SUCCESS;	

}

int pushNewKeySpace(Table *table, KeySpace *newKeySpace, Item *newItem){
	if(!table){
		printf("TABLE WAS NOT FOUND FOR PUSH\n");
		return FAILURE;
	}
	if(!newKeySpace){
		printf("NEW KEYSPACE WAS NOT FOUND FOR PUSH\n");
		return FAILURE;
	}	
	if(!table->ks){
		if(newItem)
			newKeySpace->item = newItem;
		table->ks = newKeySpace;
		return SUCCESS;
	}
	KeySpace *tmp = table->ks;
	if(newItem)
		newKeySpace->item = newItem;
	table->ks = newKeySpace;
	table->ks->next = tmp;
	return SUCCESS;	
}

int deleteItem(KeySpace *ks, Item *item){
	if(!ks){
		printf("KEYSPACE WAS NOT FOUND FOR DELETE\n");
		return FAILURE;
	}
	if(!item){
		printf("ITEM WAS NOT FOUND FOR DELETE\n");
		return FAILURE;
	}
	Item *ptr = ks->item, *ptr_prev = NULL;

	if(ptr->data == item->data){
		ks->item = ptr->next;
		free(ptr);
		return SUCCESS;	
	}
	
	while(ptr){
		if(ptr->data == item->data){
			ptr_prev->next = ptr->next;
			free(ptr);
			return SUCCESS;
		}
		ptr->release--;
		ptr_prev = ptr;
		ptr = ptr->next;
	}

	printf("ITEM WAS NOT FOUND FOR DELETE\n");
	return FAILURE;
}

int deleteAllItems(KeySpace *ks){
	if(!ks){
		printf("KEYSPACE WAS NOT FOUND FOR DELETE\n");
		return FAILURE;
	}
	Item *ptr = ks->item;
	while(ptr){
		deleteItem(ks, ptr);
		ptr = ptr->next;
	}
	return SUCCESS;
}

int deleteKeySpace(Table *table, KeySpace *ks){
	if(!table){
		printf("TABLE WAS NOT FOUND FOR DELETE\n");
		return FAILURE;
	}
	if(!ks){
		printf("KEYSPACE WAS NOT FOUND FOR DELETE\n");
		return FAILURE;
	}
	KeySpace *ptr = table->ks, *ptr_prev = NULL;

	if(strcmp(ptr->key, ks->key) == 0){
		table->ks = ptr->next;
		free(ptr->key);

		free(ptr->item);
		free(ptr);

		return SUCCESS;	
	}
	
	while(ptr){
		if(strcmp(ptr->key, ks->key) == 0){
			ptr_prev->next = ptr->next;
			free(ptr->key);
			deleteAllItems(ptr);
			free(ptr);
			return SUCCESS;
		}
		ptr_prev = ptr;
		ptr = ptr->next;
	}

	printf("KEYSPACE WAS NOT FOUND FOR DELETE\n");
	return FAILURE;
}

int deleteAllKeySpaces(Table *table){
	if(!table){
		printf("TABLE WAS NOT FOUND FOR DELETE\n");
		return FAILURE;
	}
	KeySpace *ptr = table->ks, *ptr_prev = NULL;
	while(ptr){
		ptr_prev = ptr;
		ptr = ptr->next;
		deleteKeySpace(table, ptr_prev);
		//ptr = ptr->next;
	}
	
	return SUCCESS;
}

int deleteTable(Table *table){
	if(!table){
		printf("TABLE WAS NOT FOUND FOR DELETE\n");
		return FAILURE;
	}
	deleteAllKeySpaces(table);	
}

int printAllItems(KeySpace *ks){
	if(!ks){
		printf("KEYSPACE WAS NOT FOUND FOR PRINT\n");
		return FAILURE;
	}
	Item *ptr = ks->item;
	while(ptr){
		printf("{%d, %d}-->", ptr->data, ptr->release);
		ptr = ptr->next;
	}
	printf("NULL\n");
	return SUCCESS;
}

int printAllKeySpaces(Table *table){
	if(!table){
		printf("TABLE WAS NOT FOUND FOR PRINT\n");
		return FAILURE;
	}
	KeySpace *ptr = table->ks;
	while(ptr){
		printf("%s|->", ptr->key);
		printAllItems(ptr);
		ptr = ptr->next;
	}
	return SUCCESS;
}

int printTable(Table *table){
	if(!table){
		printf("TABLE WAS NOT FOUND FOR PRINT\n");
		return FAILURE;
	}
	printf("TABLE MSIZE: %d\nTABLE CSIZE: %d\n", table->msize, table->csize);
	printAllKeySpaces(table);
	return SUCCESS;
}

KeySpace *findKeySpace(Table *table, char *key){
	KeySpace *ks = table->ks;
	while(ks){
		if(strcmp(ks->key, key) == 0){
			printf("KEYSPACE WAS FOUND\n");
			return ks;
		}
		ks = ks->next;
	}
	printf("KEYSPACE WAS NOT FOUND\n");
	return NULL;
}

Item *findItem(KeySpace *ks, int release){
	Item *ptr = ks->item;
	while(ptr){
		if(ptr->release == release){
			printf("ITEM WAS FOUND\n");
			return ptr;
		}
		ptr = ptr->next;
	}
	printf("ITEM WAS NOT FOUND\n");
	return NULL;
}

Item *copyItem(Item *sourse){
	Item *copiedItem = calloc(1, sizeof(Item));
	copiedItem->data = sourse->data;
	copiedItem->release = sourse->release;
	return copiedItem;	
}

KeySpace *copyKeySpace(KeySpace *sourse){
	KeySpace *copiedKeySpace = calloc(1, sizeof(KeySpace));
	copiedKeySpace->key = strdup(sourse->key);
	Item *ptr = sourse->item;
	while(ptr){
		pushNewItem(copiedKeySpace, copyItem(ptr));
		ptr = ptr->next;
	}
	return copiedKeySpace;
}
