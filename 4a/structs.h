#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Item{
	unsigned int value; //информация в узле
} Item;

typedef struct Node{
	unsigned int key; //ключ в узле
	Item *data; //указатель на информацию
	struct Node *left, *right, *parent, *thread; //ук-ли на левый и на правый узел + указатель на родительский узел + прошивка
} Node;


typedef struct arrayOfNodes{
	int arrLen; //длина массива узлов
	Node **arr; //массив указателей
} arrayOfNodes;

typedef struct Tree{
	Node *root; // указатель на корень дерева
} Tree;

Item *initItem(unsigned int value); // инициализация информационного поля
void freeItem(Item *target); // очистка памяти из-под инф-ого поля

Node *initNode(unsigned int key, Item *data, Node *parent); // инициализация узла дерева
void freeNode(Node *target); // очистка памяти из-под данного узла
Node *getMaxNode(Node *target);
Node *getMinNode(Node *target);

void preOrderPrint(Node *node, int key);

/*
	вспомогательная структура, нужна для поиска и удаления
*/
arrayOfNodes *initArr(); //иницилизация массива
void insBack(arrayOfNodes *array, Node *target); //вставка в конец массив
void del(arrayOfNodes *array, Node *target); //удаление из конца массива
void freeArr(arrayOfNodes *target); //зачистка памяти из-под массива
void printArr(arrayOfNodes *target); //печать массива

void printUntil(Node *node, Node *until);
void threadTree(Tree *tree);

Tree *initTree(); // инициазлиция дерева
void freeTree(Tree *target); // очистка памяти из-под дерева
int printTree(Tree *target);

#endif
