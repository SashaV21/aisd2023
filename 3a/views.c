#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"

#include "structs.h"
#include "utils.h"
#include "models.h"

#define SUCCESS 1
#define FAILURE 0
#define EXIT 0

char *get_str(){
        char *ptr = (char*)malloc(1);
        char buf[81];
        int n, len = 0;
        *ptr = '\0';
        do {
                n = scanf("%80[^\n]", buf);
            if (n < 0) {
                free(ptr);
                ptr = NULL;
                continue;
                }
            else if (n == 0){
                scanf("%*c");
                if (len == 0) return NULL;
                }
            else {
                        len += strlen(buf);
            ptr = (char *)realloc(ptr, (len + 1)*sizeof(char));
            strcat(ptr, buf);
        }
     } while (n > 0);
     return ptr;
}

int D_add(Table *table){
	const char *err_msgs[] = {"FAILURE ADD", "SUCCESS ADD"};
	printf("ENTER KEY -->");
	char *key = get_str();
	//printf("\n");
	if(!key)
		return FAILURE;
	int data = 0;
	int res = getInt(&data ,"ENTER DATA -->");
	if(res == -1){
		return EXIT;
	}
	printf("\n");
	int rc = add(table, key, data);
	printf("%s\n\n", err_msgs[rc]);
	return SUCCESS;
}

int D_find(Table *table){
	const char *err_msgs[] = {"FAILURE FIND", "SUCCESS FIND"};
	printf("ENTER KEY -->");
	char *key = get_str();
	//printf("\n");
	if(!key)
		return FAILURE;
	int rc = FAILURE,
		release = 0;
	int res = getInt(&release, "ENTER RELEASE -->");
	if(res == -1) return EXIT;
	printf("\n");
	KeySpace *foundKeySpace = find(table, key, release);
	if(foundKeySpace) rc = SUCCESS;
	Table answer = doNewTable(1);
	pushNewKeySpace(&answer, copyKeySpace(foundKeySpace), NULL);
	printTable(&answer);
	deleteTable(&answer);
	printf("%s\n\n", err_msgs[rc]);
	return SUCCESS;
}

int D_delete(Table *table){
	const char *err_msgs[] = {"FAILURE DELETE", "SUCCESS DELETE"};
	printf("ENTER KEY -->");
	char *key = get_str();
	//printf("\n");
	if(!key)
		return FAILURE;
	int release = 0;
	int res = getInt(&release,"ENTER RELEASE -->");
	if(res == -1) return EXIT;
	printf("\n");
	int rc = delete(table, key, release);
	free(key);
	printf("%s\n\n", err_msgs[rc]);
	return SUCCESS;
}
// создадим файд, где на первой строке указано количество элементов, а в каждой последующей
// строке записаны ключ и значение очередного элемента
int D_import(Table *table){
	char *fpath = readline("ENTER PATH -->");
	
	if(!fpath)
		return FAILURE;
	FILE *file = fopen(fpath, "rb+");
	free(fpath);
	if(file) {
		import(table, file);
		fclose(file);
	} else{
		printf("FILE DOES NOT EXIST\n");
	}

	return SUCCESS;
}
