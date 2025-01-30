#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>

#include "structs.h"
#include "utils.h"
#include "models.h"

int D_insert(Tree *tree) {
	unsigned int key, data;

	if (!readUnsInteger("enter key: ", &key) || 
			!readUnsInteger("enter data: ", &data)) {
		return 0;
	}
	
	insert(tree, key, data);
	return 1;
}

int D_search(Tree *tree){
	unsigned int key;

	if (!readUnsInteger("enter key: ", &key)) {
		return 0;
	}

	arrayOfNodes *foundNodes = search(tree, key);
	if(foundNodes->arrLen > 0){
		printArr(foundNodes);
		freeArr(foundNodes);	
	}
	return 1;	
}

int D_spsearch(Tree *tree){
	unsigned int key, index;

	if (!readUnsInteger("enter key: ", &key)) {
		return 0;
	}
	arrayOfNodes *foundNodes = search(tree, key);
	if(foundNodes->arrLen > 0){
		printArr(foundNodes);
		unsigned int index;
		if (!readUnsInteger("\033[31menter index\033[0m", &index)) {
			return 0;
		}
		Node *minNode = NULL;
		if(foundNodes->arr[index]->right)
			minNode = getMinNode(foundNodes->arr[index]->right);
		else{
			if(foundNodes->arr[index] == foundNodes->arr[index]->parent->right){
				Node *ptr = foundNodes->arr[index]->parent;
				ptr = ptr->parent;
				minNode = ptr;
			} else{
				minNode = foundNodes->arr[index]->parent;
			}
		}
		arrayOfNodes *minNodes = search(tree, minNode->key);
		printArr(minNodes);
		freeArr(foundNodes);	
		freeArr(minNodes);	
	}
	return 1;	
}


int D_delete(Tree *tree){
	unsigned int key, all, index;

	if (!readUnsInteger("enter key: ", &key)) {
		return 0;
	}
	arrayOfNodes *foundNodes = search(tree, key);
	if(foundNodes->arrLen > 0){
		printArr(foundNodes);
		if (!readUnsInteger("\033[31mif you want to delete all enter 1, else enter 0\033[0m", &all)) {
			return 0;
		}
		if(!all){
			if (!readUnsInteger("\033[31menter index\033[0m", &index)) {
				return 0;
			}
			delete(tree, foundNodes->arr[index]);
		} else{
			for(int i = 0; i < foundNodes->arrLen; i++){
				delete(tree, foundNodes->arr[i]);	
			}
		}
		freeArr(foundNodes);
	}
	return 1;	
}

int D_bypass(Tree *tree){
	unsigned int all, key;

	if (!readUnsInteger("\033[31mif you want to bypass all tree enter 1, else enter 0\033[0m", &all)) {
		return 0;
	}
	if(!all){
		if (!readUnsInteger("\033[31menter key\033[0m", &key)) {
			return 0;
		}
		bypass(tree, key);
	} else{
		bypass(tree, -1);
	}

	return 1;	
}

int D_import(Tree *tree){
	char *fpath = readline("enter path to file: ");
	FILE *file = fopen(fpath, "r");
	free(fpath);
	unsigned int key, data;
	while(!feof(file)){
		fscanf(file, "%d", &key);
		fscanf(file, "%d", &data);
		insert(tree, key, data);		
	}			
	return 1;
}
