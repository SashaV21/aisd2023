#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3c.h"

Table *make_tab(){
	Table *tab=(Table *)malloc(sizeof(Table));
	tab->size=0;
	puts("Enter size of table:");
	get_int(&tab->msize);
	tab->ks=(KeySpace**)malloc(sizeof(KeySpace*)*tab->msize);
	for (int i=0;i<(tab->msize);i++){
		tab->ks[i] = NULL;
	}
	return tab;
}

void del_info(Item* ptr){
	Item* prev;
	while(ptr){
		prev = ptr;
		ptr = ptr->next;
		free(prev);
	}
}

void tab_del(Table *tab){
	for (int i=0;i<(tab->msize);i++){
		KeySpace* ptr = tab->ks[i], *prev;
		while(ptr){
			prev = ptr;
			ptr = ptr->next;
			if(prev->key) free(prev->key);
			del_info(prev->info);
			free(prev);
		}
	}
	free(tab->ks);
	free(tab);
}

void tab_clean(Table *tab){
	for (int i=0;i<(tab->msize);i++){
		KeySpace* ptr = tab->ks[i];
		while(ptr){
			del_info(ptr->info->next);
			ptr->info->rel = 1;      //меняем номер последней версии на 1
			ptr->info->next = NULL;
			ptr = ptr->next;
		}
	}
}

// int hash(char* str, int size){
	// return strlen(str)%size;
// }

 int hash(char* str, int size)
{
    unsigned long hash = 5381;
    int c;

    while (0 != (c = *str++)){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   	}
	hash = hash%size;
    return hash;
}

int mix(int j,int size){
	int step = 1;
	return (j + step) % size; 
}

KeySpace* tab_find(Table *tab, char* key){
	int j = hash(key,tab->msize);
	KeySpace* ptr = tab->ks[j];
	while(ptr){
		if (strcmp(ptr->key,key)==0)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

int tab_remove(Table *tab, char* key){
	int j = hash(key, tab->msize);
	KeySpace* ptr = tab->ks[j], *ptr_prev = NULL;
	while (ptr && strcmp(ptr->key,key) != 0) {
		ptr_prev = ptr;
	    ptr = ptr->next;
	}
	if (!ptr) return 0;
	if (ptr == tab->ks[j]) {
		tab->ks[j] = ptr->next;
	}
	if (ptr_prev) {
		ptr_prev->next = ptr->next;
	}
	del_info(ptr->info);
	free(ptr->key);
	free(ptr);
	return 1;
}

int tab_import(Table *tab, FILE *file){
	int n,size;
	fget_int(file,&size);
	for (int i=0;i < (size);i++){
		char* key = fget_str(file);
	    fget_int(file, &n);
		KeySpace* j = tab_find(tab,key);
		if (j != NULL){
	  		tab_add_rel(j,n);
	  		free(key);
		}
		else{
	  		int res = tab_add(tab,key,n);
			if (res == 1) tab->size +=1;
			else free(key);
		}
	}
}

int tab_add(Table *tab,char* key, int info){
	int j = hash(key,tab->msize);
	if (tab->size < tab->msize){
		KeySpace* new = malloc(sizeof(KeySpace));
		new->key = key;
		new->info = malloc(sizeof(Item));
		new->info->info = info;
		new->info->rel = 1;
		new->info->next = NULL;
		new->next = tab->ks[j];
		tab->ks[j] = new;
		tab->size+=1;
		return 1;
	}
	return 0;
}

int tab_add_rel(KeySpace* j, int info){
	Item* new = malloc(sizeof(Item));
	new->info = info;
	new->rel = j->info->rel + 1;
	new->next = j->info;
	j->info = new;
	return 1;
}

int tab_print(Table *tab){
	int n=0;
	for (int i=0;i<tab->msize;i++){
		KeySpace* p = tab->ks[i];
		while(p){
			printf("Index:%d Key:%s", i,p->key);
			Item* ptr = p->info;
			while(ptr){
				printf(" Release:%d Info:%d", ptr->rel ,ptr->info);
				ptr = ptr->next;
			}
			printf("\n");
			n=1;
			p = p->next;
		}
	}
	return n;
}

int get_int(int* n){
	int flag;
	do{
		flag=scanf("%d",n);
	    if(flag<0) return 0;
	    if (flag==0){
	    	printf("Baby, repeat please!\n");
	    	scanf("%*c");
		}
	}while(flag==0);
}

int fget_int(FILE *my_file, int* n){
        if(fscanf(my_file,"%d",n)!=EOF){
                fscanf(my_file,"%*c");
                return 1;
        }
        return 0;
}

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
	    }
	    else if (n == 0){
	     scanf("%*c");
	    	if (len == 0) return NULL;
	    }
	    else {
	   		len += strlen(buf);
	    	ptr = (char*) realloc(ptr, (len+1)*sizeof(char));
	    	strcat(ptr, buf);
	 	}
	} while (n > 0);
	return ptr;
}

char *fget_str(FILE* file){
	char *ptr = (char*)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = fscanf(file, "%80[^\n]", buf);
	    if (n < 0) {
	    	free(ptr);
	        ptr = NULL;
	    }
	    else if (n == 0){
	     fscanf(file, "%*c");
	    	if (len == 0) return NULL;
	    }
	    else {
	   		len += strlen(buf);
	    	ptr = (char*) realloc(ptr, (len+1)*sizeof(char));
	    	strcat(ptr, buf);
	 	}
	} while (n > 0);
	return ptr;
}
