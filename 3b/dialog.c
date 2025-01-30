#include <stdio.h>
#include <stdlib.h>
#include "lab3b.h"
#include "dialog.h"
	
int D_Add(Table * tab){
	printf("Key:\n");
	char *key = get_str();
	printf("Info:\n");
	int info;
	get_int(&info);
	tab_add(tab, key, info);
}

int D_Delete(Table *tab){
	printf("Key:\n");
	char *key = get_str();
	tab_remove(tab, key);
	free(key);
}

int D_Delete_Edition(Table *tab){
	printf("Key:\n");
	char *key = get_str();
	printf("Edition:\n");
	int edition;
	get_int(&edition);
	tab_remove_ed(tab, key, edition);
	free(key);
}				

int D_Find(Table *tab){
	printf("Key:\n");
	char *key = get_str();	
	tab_find(tab, key);
	free(key);
}
int D_Find_Edition(Table *tab){
	printf("Key:\n");
	char *key = get_str();
	printf("Edition:\n");
	int edition;
	get_int(&edition);
	tab_find_ed(tab, key, edition);
	free(key);
}
				
int D_Show(Table *tab){
	tab_print(tab);
}

int dialog(const char *msgs[]){
	char *errmsg = "";
	int rc;
	int i, n;
	do{
		puts(errmsg);
		errmsg = "You are wrong. Repeate, please!";
		for(i = 0; i < 7; ++i)
		puts(msgs[i]);
		puts("Make your choice:");
		n = get_int(&rc);
		if(n == 0)
		rc = 0;
	} while(rc < 0 || rc >= 7);
	scanf("%*c");
	return rc;
}
