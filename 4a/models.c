#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

int insert(Tree *tree, unsigned int key, unsigned int data){
	Node *tmp = tree->root;

	if(!tmp) {
		tree->root = initNode(key, initItem(data), NULL);
	}

	while(tmp){
		if(tmp->key <= key){
			if(tmp->right){
				tmp = tmp->right;
				continue;
			} else{
				tmp->right = initNode(key, initItem(data), tmp);
				break;
			}
		} else{
			if(tmp->left){
				tmp = tmp->left;
				continue;
			} else{
				tmp->left = initNode(key, initItem(data), tmp);
				break; 
			}
		}
	}

	threadTree(tree);
	return 1;
}

arrayOfNodes *search(Tree *tree, unsigned int key){
	if(!tree->root)
		return 0;

	arrayOfNodes *array = initArr();

	Node *ptr = tree->root;
	while(ptr){
		if(ptr->key == key){
			insBack(array, ptr);
			ptr = ptr->right;
		} else if(ptr->key < key){
			ptr = ptr->right;		
		} else{
			ptr = ptr->left;
		}
	}
	return array;
}

int delete(Tree *tree, Node *target) {
	int isLeft = -1;
	if (target->parent) {
		if (target->parent->right != target) {
			isLeft = 1;
		} else {
			isLeft = 0;
		}
	}

	Node *new = NULL;
	if (!target->left && !target->right) {
		if (isLeft > 0) {
			target->parent->left = NULL;
		} else if (!isLeft) {
			target->parent->right = NULL;
		} else {
			tree->root = NULL;
		}
		freeNode(target);
	} else if (target->left && target->right) {
		Node *new = getMaxNode(target->right);
		target->key = new->key;
		free(target->data);
		target->data = new->data;
		if (new->parent->right != new) {
			new->parent->left = new->right;
		} else {
			new->parent->right = new->right;
		}
		if (new->right) {
			new->right->parent = new->parent;
		}
		free(new);
	} else {
		Node *new = target->left ? target->left : target->right;
		new->parent = target->parent;
		if (isLeft > 0) {
			target->parent->left = new;
		} else if (!isLeft) {
			target->parent->right = new;
		} else {
			tree->root = new;
		}
		freeNode(target);
	}

	threadTree(tree);
	return 1;
}

int bypass(Tree *tree, int key){
	if(key == -1){
		/* int sps = 1; */
		printUntil(tree->root, NULL);
	} else{
		arrayOfNodes *array = search(tree, key);
		if (array->arrLen) {
			printUntil(tree->root, array->arr[0]);
			printUntil(array->arr[array->arrLen - 1]->right, NULL);
		}
		freeArr(array);
		/* for(int i = 0; i < array->arrLen; i++){
			int sps = 1;
			preOrderPrint(array->arr[i]->right, sps);	
			printf("\n");
		}
		freeArr(array); */
	}
	return 1;
}
