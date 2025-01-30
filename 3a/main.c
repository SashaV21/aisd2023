#include <stdio.h>

#include "structs.h"
#include "dialog.h"
#include "views.h"

int main(){
	const char *msgs[] = {"0. QUIT", "1. ADD", "2. DELETE", "3. FIND",  "4. PRINT", "5. IMPORT", "6. EXPORT"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);

	Table table = initTable();
	if(table.msize == -1){
		return 1;
	}	
	int rc = dialog(msgs, N),
		(*fptr[])(Table *) = {NULL, D_add, D_delete, D_find, printTable, D_import, NULL};
	
	while(rc > 0 && rc != -1){
		if(!fptr[rc](&table)) break;
		rc = dialog(msgs, N);
	}

	deleteTable(&table);
	
	return 1;
}
