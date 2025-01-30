#include <stdio.h>
#include <time.h>

#include "structs.h"
#include "models.h"
#include "dialog.h"
#include "utils.h"

void fillWithRandom(Tree *tree, int size) {
	for (int i = 0; i < size; i++) {
		insert(tree, genUnsInteger(), genUnsInteger());
	}
}

int T_insert() {
	for (int i = 10000; i <= 100000; i += 10000) {
		Tree *tree = initTree();
		fillWithRandom(tree, i);

		int key[1000], data[1000];
		for (int j = 0; j < 1000; j++) {
			key[j] = genUnsInteger();
			data[j] = genUnsInteger();
		}

		clock_t time = clock();
		for (int j = 0; j < 1000; j++) {
			insert(tree, key[j], data[j]);
		}
		time = clock() - time;
		printf("number of nodes = %d, time = %f\n", i, ((double) time) / CLOCKS_PER_SEC);

		freeTree(tree);
	}

	return 1;
}

int T_delete() {
	for (int i = 10000; i <= 100000; i += 10000) {
		Tree *tree = initTree();
		fillWithRandom(tree, i);
		int key[1000];
		for (int j = 0; j < 1000; j++) {
			key[j] = genUnsInteger();
		}

		clock_t time = clock();
		for (int j = 0; j < 1000; j++) {
			arrayOfNodes *nodes = search(tree, key[j]);
			if (nodes->arrLen) {
				delete(tree, nodes->arr[0]);
			}
		}		
		time = clock() - time;
		printf("number of nodes = %d, time = %f\n", i, ((double) time) / CLOCKS_PER_SEC);

		freeTree(tree);
	}

	return 1;
}

int T_search() {
	for (int i = 10000; i <= 100000; i += 10000) {
		Tree *tree = initTree();
		fillWithRandom(tree, i);
        int key[1000];
        for (int j = 0; j < 1000; j++) {
            key[j] = genUnsInteger();
        }

        clock_t time = clock();
        for (int j = 0; j < 1000; j++) {
            arrayOfNodes *nodes = search(tree, key[j]);
        }
        time = clock() - time;
        printf("number of nodes = %d, time = %f\n", i, ((double) time) / CLOCKS_PER_SEC);

        freeTree(tree);
    }

    return 1;
}

int timing(Tree *tree) {
	const char *msgs[] = {"\033[033m\t0. quit\033[0m", "\033[033m\t1. insert\033[0m", "\033[033m\t2. delete\033[0m", "\033[033m\t3. search\033[0m"};
	int (*fptr[])() = {NULL, T_insert, T_delete, NULL};
	const int N = sizeof(msgs) / sizeof(msgs[0]);

	int option = dialog(msgs, N);
	while (option > 0) {
		if(!fptr[option](tree)) break;
		option = dialog(msgs, N);
	}

	return 1;
}
