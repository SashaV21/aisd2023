#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

Item *initItem(unsigned int value){
	Item *newItem = malloc(sizeof(Item));
	newItem->value = value;
	return newItem;
}

void freeItem(Item *target){
	free(target);
	return;
}

Node *initNode(unsigned int key, Item *data, Node *parent){
	Node *newNode = malloc(sizeof(Node));
	newNode->key = key;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->thread = NULL;
	newNode->parent = parent;
	return newNode;
}

void freeNode(Node *target){
	freeItem(target->data);
	free(target);
	return;
}

Tree *initTree(){
	Tree *newTree = malloc(sizeof(Tree));
	newTree->root = NULL;
	return newTree;
}

void postOrderDelete(Node *root){
	if(root){
		postOrderDelete(root->left);
		postOrderDelete(root->right);
		freeNode(root);
	}
} 

void printUntil(Node *node, Node *until) {
	while (node && node != until) {
		printf("\033[32;1m(k:%d d:%d)\033[0m\n", node->key, node->data->value);
		node = node->thread;
	}
}

void preOrderPrint(Node *node, int /*sps*/) {
	while(node) {
		printf("\033[32;1m(k:%d d:%d)\033[0m\n", node->key, node->data->value);
		node = node->thread;
	}
/*	if(node){
		printf("\033[32;1m(k:%d d:%d)\033[0m\n", node->key, node->data->value);
		if(node->left){
			printf("|");
			for(int i = 0; i < sps - 1; i++){
				printf("-");
			}
			printf("L:");
			preOrderPrint(node->left, sps + 3);
		}
		if(node->right){
			printf("|");
			for(int i = 0; i < sps - 1; i++){
				printf("-");
			}
			printf("R:");
			preOrderPrint(node->right, sps + 3);			
		}
	} */
}

int printTree(Tree *target){
	int sps = 1;
	preOrderPrint(target->root, sps);
	return 1;
}

void freeTree(Tree *target){
	postOrderDelete(target->root);
	free(target);
	return;
}

Node *getMaxNode(Node *target){
	while(target->right){
		target = target->right;
	}
	return target;
}

Node *getMinNode(Node *target){
	while(target->left){
		target = target->left;
	}
	return target;
}

arrayOfNodes *initArr(){
	arrayOfNodes *newArr = malloc(1 * sizeof(arrayOfNodes));
	newArr->arrLen = 0;
	newArr->arr = NULL;
	return newArr;	
}

void freeArr(arrayOfNodes *target){
	free(target->arr);
	free(target);
	return;
}

void printArr(arrayOfNodes *target){
	printf("\033[33mindex\tkey\tdata\033[0m\n");
	for(int i = 0; i < target->arrLen; i++)
		printf("\033[33m%d\t%d\t%d\033[0m\n", i, target->arr[i]->key, target->arr[i]->data->value);
	return;
}

void insBack(arrayOfNodes *array, Node *target){
	array->arrLen++;
	array->arr = realloc(array->arr, array->arrLen * sizeof(Node *));
	array->arr[array->arrLen - 1] = target;
	return;
}

void del(arrayOfNodes *array, Node *target){
	for(int i = 0; i < array->arrLen; i++){
		if(array->arr[i] == target){
			array->arr[i] = array->arr[array->arrLen - 1];
			array->arrLen--;
			array->arr = realloc(array->arr, array->arrLen * sizeof(Node *));
			return;
		}
	}
}

void threadNode(Node *cur, Node **prev) {
    if (!cur) return;
	if (*prev) (*prev)->thread = cur;
	*prev = cur;
    threadNode(cur->left, prev);
    threadNode(cur->right, prev);
}

void threadTree(Tree *tree) {
	Node *prev = NULL;
	threadNode(tree->root, &prev);
}
