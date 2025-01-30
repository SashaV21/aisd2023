#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"

#define SUCCESS 1
#define FAILURE 0

/*int getInt(char *prompt){
	printf("%s\n", prompt);
	int result = 0;
	while(scanf("%d", &result) < 1){
		printf("WRONG VALUE\n");
		scanf("%*[^\n]");
	}
	return result;
}*/

int getInt(int *value, char *messageToUser) {
    printf("%s", messageToUser);
    int res, clearBuffer;
    do {
        res = scanf("%d", value);
           while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF) {}
        if (res == 0) {
        	printf("WRONG VALUE\n");
        } else if (res == EOF) {
            return 0;
        }
    } while (res <= 0);
    return res;
}

int isTableOverflow(Table *table){
	if(table->msize == table->csize){
		printf("TABLE IS OVERLOW\n");
		return SUCCESS;
	}
	return FAILURE;
}

int isTableEmpty(Table *table){
	if(table->csize == 0){
		printf("TABLE IS EMPTY\n");
		return SUCCESS;
	}
	return FAILURE;
}

int getRecord(Table *table, char *string){
	if(isTableOverflow(table))
		return FAILURE;
	char *f_word = strtok(string, "|->");
	KeySpace *newKeySpace = doNewKeySpace(f_word);
	char *word = strtok(NULL, "-->");
	while(word){
		pushNewItem(newKeySpace, doNewItem(atoi(word)));
		word = strtok(NULL, "-->");
	}
	pushNewKeySpace(table, newKeySpace, NULL);
	table->csize++;
	return SUCCESS;
}
