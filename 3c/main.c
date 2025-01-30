#include <stdio.h>
#include <stdlib.h>
#include "lab3c.h"
#include "dialog.h"

int main(){
	Table *tab=make_tab();
	int (*act[])(Table *) = {NULL, D_Add, D_Find, D_Find_Rel, D_Delete, D_Show, D_Import, D_Clean};
	const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Find Release", "4. Delete", "5. Show", "6. Import", "7. Clean"};
	int rc = dialog(msgs);
	while(rc){
		act[rc](tab);
	   	rc = dialog(msgs);
	}
	printf("That's all. Bye!\n");
	tab_del(tab);
	return 0;
}
