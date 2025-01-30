#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "dialog.h"
#include "structs.h"
#include "views.h"
#include "timing.h"

int main(){
	const char *msgs[] = {"0. exit", "1. insert", "2. print", "3. search", "4. delete", "5. bypass", "6. special search", "7. import", "8. timing"};
	int (*fptr[])(Tree *) = {NULL, D_insert, printTree, D_search, D_delete, D_bypass, D_spsearch, D_import, timing};
	const int N = sizeof(msgs) / sizeof(msgs[0]);

	srand(time(0));

	Tree *tree = initTree();

	int option = dialog(msgs, N);
	while (option > 0) {
		if(!fptr[option](tree)) break;
		option = dialog(msgs, N);
	}

	freeTree(tree);

	return 0;
}
