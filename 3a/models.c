#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "utils.h"

#define SUCCESS 1
#define FAILURE 0

int add(Table *table, char *key, int data){
	if(isTableOverflow(table))
		return FAILURE;
	KeySpace *foundKeySpace = findKeySpace(table, key);
	//Item* p = doNewItem(data);
	//KeySpace* q = doNewKeySpace(key);
	if(!foundKeySpace){
		pushNewKeySpace(table, doNewKeySpace(key), doNewItem(data));
		table->csize++;
		//free(p);
		//free(q);
		return SUCCESS;
	}
	pushNewItem(foundKeySpace, doNewItem(data));
	//free(p);
	//free(q);
	return SUCCESS;
}

KeySpace *find(Table *table, char *key, int release){
	if(isTableEmpty(table))
		return NULL;
	KeySpace *foundKeySpace = findKeySpace(table, key);
	if(!foundKeySpace)
		return NULL;
	if(release == -1)
		return foundKeySpace;
	Item *foundItem = findItem(foundKeySpace, release);
	if(!foundItem)
		return NULL;

	KeySpace *result = doNewKeySpace(key);
	pushNewItem(result, copyItem(foundItem));
	return result;			
}

int delete(Table *table, char *key, int release){
	if(isTableEmpty(table))
		return FAILURE;
	KeySpace *foundKeySpace = findKeySpace(table, key);
	if(!foundKeySpace)
		return FAILURE;
	if(release == -1){
		deleteKeySpace(table, foundKeySpace);
		table->csize--;
		return SUCCESS;
	}
		
	Item *foundItem = findItem(foundKeySpace, release);
	if(!foundItem)
		return FAILURE;
	deleteItem(foundKeySpace, foundItem);
	
	return SUCCESS;
}

char  *fget_str(FILE *my_file){
        char* ptr = (char*)malloc(1);
    char buf[81];
    int n=0, len = 0;
    *ptr = '\0';
    do {
        n = fscanf(my_file,"%80[^\n]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        else if (n == 0){
            fscanf(my_file,"%*c");
            if (len == 0)
                return NULL;
        }
        else {
            len += strlen(buf);
            ptr = (char*)realloc(ptr, (len + 1)*sizeof(char));
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

int fget_int(FILE *my_file, int* n){
        if(fscanf(my_file,"%d",n)!=EOF){
                fscanf(my_file,"%*c");
                return 1;
        }
        return 0;
}

int import(Table *table, FILE *file){
//	char key[100];
	int data, size;
	fget_int(file, &size);
//	while(!feof(file)){
	for (int i=0; i<size; i++){
		char* key1 = fget_str(file);
	//	if(fgets(key, 100, file) == NULL)
	//		return FAILURE;
		//fgetc(file);
		fget_int(file, &data);
		//if(fscanf(file, "%d", &data) < 1)
		//	return FAILURE;
		//fgetc(file);
		//fscanf(file, "%d", &data);
		
	//	key[strlen(key) - 1] = '\0';
	//	char *addingKey = strdup(key);
		if(!add(table, key1, data)){
		//	free(addingKey);
			free(key1);
		}
	}
	return SUCCESS;
}
