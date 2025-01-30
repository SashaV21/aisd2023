#include "lab3b.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Table* load(char *fname)
{
	Table *tab=malloc(sizeof(Table));
	tab->ks = NULL;
	tab->file = NULL;
	tab->name = strdup(fname);
	tab->file = fopen(fname, "r+b");
	if (tab->file == NULL) return 0;
		
	int len, info, busy;
	while(fread(&busy,sizeof(int),1,tab->file)==1){
		fread(&len,sizeof(int),1,tab->file);
		Node *ptr = malloc(sizeof(Node));
		ptr->busy = busy;
		ptr->key = malloc(sizeof(char)*(len+1));
		ptr->key[len] = '\0';
		fread(ptr->key,sizeof(char),len,tab->file);
		fread(&ptr->edition, sizeof(int), 1, tab->file);
		fread(&info, sizeof(unsigned int), 1, tab->file);
		if (tab->ks == NULL){
			ptr->ofset = 0;
		}
		else{
			ptr->ofset = tab->ks->ofset + 4 * sizeof(int) + strlen(tab->ks->key) * sizeof(char);
		}
		ptr->next = tab->ks;
		tab->ks = ptr;
	}
	return tab;
}

int tab_add(Table *tab, char* key, int info){
	int len = strlen(key);
	Node *ptr = malloc(sizeof(Node));
	ptr->key = key;
	ptr->busy = 1;
	ptr->edition += 1;
	if (tab->ks == NULL){
		ptr->ofset = 0;
	}
	else{
		ptr->ofset = tab->ks->ofset + 4*sizeof(int) + strlen(tab->ks->key) * sizeof(char);
	}
	ptr->next = NULL;
	Node* check = tab->ks;
	while(check){
		if (strcmp(check->key, key) == 0){
			ptr->edition = check->edition + 1;
		}
		check = check->next;
	}
	ptr->next = tab->ks;
	tab->ks = ptr;
	fseek(tab->file, 0, SEEK_END);
	int busy = 1;
	fwrite(&busy,sizeof(int), 1, tab->file);
	fwrite(&len,sizeof(int), 1, tab->file);
	fwrite(ptr->key,sizeof(char), len, tab->file);
	fwrite(&ptr->edition, sizeof(int), 1, tab->file);
	fwrite(&info, sizeof(int), 1, tab->file);
}

int tab_remove(Table *tab, char* key) {
	Node *ptr = tab->ks;
	int busy = 0;
	while(ptr){
		if (ptr->busy == 1 && strcmp(key, ptr->key) == 0){
			fseek(tab->file, ptr->ofset, SEEK_SET);
			fwrite(&busy, sizeof(int), 1, tab->file);
			ptr->busy = 0;
		}
		ptr = ptr->next;
	}
}

int tab_remove_ed(Table *tab, char* key, int edition) {
	Node *ptr = tab->ks;
	int busy = 0;
	while(ptr){
		if (ptr->busy == 1 && strcmp(key, ptr->key) == 0 && edition == ptr->edition){
			fseek(tab->file, ptr->ofset, SEEK_SET);
			fwrite(&busy,sizeof(int), 1, tab->file);
			ptr->busy= 0;
		}
		ptr = ptr->next;
	}
}

int tab_find_ed(Table* tab, char* find, int edition){
	Node *ptr = tab->ks;
	int busy,len, ed, info;
	while(ptr){
		if (ptr->busy == 1 && strcmp(find, ptr->key) == 0 && edition == ptr->edition){
			fseek(tab->file, ptr->ofset, SEEK_SET);
				if(fread(&busy,sizeof(int),1,tab->file)==1){
				fread(&len,sizeof(int),1,tab->file);
				printf("%d!!!", len);
				char* key = malloc(sizeof(char)*(len+1));
				fread(key,sizeof(char), len, tab->file);
				key[len] = '\0';
				fread(&ed,sizeof(int),1,tab->file);
				fread(&info,sizeof(unsigned int),1,tab->file);
				printf("Key: %s Edition: %d Info: %d\n", key, ed, info);
				free(key);
			}
		}
		ptr = ptr->next;
	}
	
}

int tab_find(Table* tab, char* find) {
	Node *ptr = tab->ks;
	while(ptr){
		if (ptr->busy == 1 && strcmp(find, ptr->key) == 0){
				int ed = ptr->edition;
				tab_find_ed(tab,find,ed);
		}
		ptr = ptr->next;
	}
}

void tab_print(Table *tab) {
	int edition;
	unsigned int info;
	int len, busy;
	int stop = 1;
	fclose(tab->file);
	tab->file = fopen(tab->name, "rb+");
	while(stop){
		stop = fread(&busy, sizeof(int), 1, tab->file);
		if(stop == 1){
			fread(&len,sizeof(int),1,tab->file);
			char* key = malloc(sizeof(char) * len+1);
			if(fread(key,sizeof(char),len,tab->file)!=0){
			key[len]='\0';
			fread(&edition,sizeof(int),1,tab->file);
			fread(&info,sizeof(unsigned int),1,tab->file);
			if (busy == 1) printf("Key=%s Edition=%d Info=%d\n",key,edition,info);
			free(key);
			}
		}
	}
}

void free_tab(Table* tab){
	Node* ptr = tab->ks, *prev;
	while(ptr){
		prev = ptr;
		ptr = ptr->next;
		free(prev->key);
		free(prev);
	}
}

int get_int(int* n){
	int flag;
	do{
		flag=scanf("%d",n);
	    if(flag<0) return 0;
	    if (flag==0) scanf("%*c");
	}while(flag==0);
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
			continue;
		}
		else if (n == 0){
			scanf("%*c");
			if (len == 0) return NULL;
	    }
	    else {
	    	len += strlen(buf);
	     	ptr = (char *)realloc(ptr, (len+1)*sizeof(char));
	     	strcat(ptr, buf);
	   	}
	} while (n > 0);
	return ptr;
}
