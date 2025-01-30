#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3c.h"
#include "dialog.h"

int dialog(const char *msgs[]){
	char *errmsg = "";
	int rc;
	int i, n;
	int count = 8;
	do{
		puts(errmsg);
	    errmsg = "You are wrong. Repeate, please!";
	    for(i = 0; i < count; ++i){
	    	puts(msgs[i]);
	    }
	        puts("Make your choice:");
	        n = get_int(&rc);
	        if(n == 0) rc = 0;
	} while(rc < 0 || rc >= count);
	    scanf("%*c");
	    return rc;
}

int D_Add(Table *tab){
	int info,n;
	puts("Enter key:");
	char* key = get_str();
	
	puts("Enter info:");
	get_int(&info);
	KeySpace* j = tab_find(tab,key);
	if (j == NULL){
		n = tab_add(tab,key,info);
		if (n==1) puts("Wow, done!");
		else puts("Sorry,boy((");
	}
	else{
		free(key);
		tab_add_rel(j,info);
		puts("Wow, done!");
	}
}

int D_Delete(Table *tab){
	puts("Enter key:");
	char* key = get_str();
	tab_remove(tab,key);
	free(key);
}

int D_Clean(Table *tab){
	tab_clean(tab);
	puts("Tab cleaned!");
}
	
int D_Find(Table *tab){
	puts("Enter key:");
	char* key = get_str();
	puts("Result ->");
	int j = hash(key, tab->msize);
	KeySpace* res = tab_find(tab,key);
	if (res != NULL){
		printf("Index:%d Key:%s", j, res->key);
		Item* ptr = res->info;
		while(ptr){
			printf(" Release:%d Info:%d", ptr->rel ,ptr->info);
			ptr = ptr->next;
		}
		printf("\n");
	}
	else puts("Nothing found.");
	free(key);
}

int D_Find_Rel(Table *tab){
	puts("Enter key:");
	char* key = get_str();
	int rel; 
	puts("Enter release:");
	get_int(&rel);
	puts("Result ->");
	int j = hash(key, tab->msize);
	KeySpace* res = tab_find(tab,key);
	if (res != NULL){
		Item* ptr = res->info;
		while(ptr){
			if (ptr->rel == rel){
				printf("Index:%d Key:%s Release:%d Info:%d\n", j, res->key, ptr->rel, ptr->info);
				free(key);
				return 1;
			}
			ptr = ptr->next;
		}
		
	}
	puts("Nothing found.");
	free(key);
	return 0;
}

int D_Import(Table *tab){
	FILE *my_file;
	puts("Enter file name:");
	char *name=get_str();
	my_file = fopen(name, "r+");
	if (my_file == NULL){
		printf("Error\n");
		free(name);
	    return 0;
	}
	tab_import(tab,my_file);
	fclose(my_file);
	free(name);
}

int D_Show(Table *tab){
	if (tab_print(tab)==0){
		puts("Empty");
	}
}







