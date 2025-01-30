#include <stdio.h>
#include <stdlib.h>
#include "lab3b.h"
#include "dialog.h"

int main(){
	char *file_name;
    int stop = 0;
    do{
    	puts("Enter file name:");
        file_name = get_str();
        FILE *file = fopen(file_name,"rb");
        if (file == NULL){
        	free(file_name);
       	}
        else{ 
        	stop = 1;
        	fclose(file);
        }
    }while(stop == 0);
    
	Table *tab = load(file_name);
	int (*act[])(Table *) = {NULL, D_Add, D_Delete, D_Delete_Edition, D_Find, D_Find_Edition, D_Show};
    const char *msgs[] = {"0.Quit", "1.Add", "2.Delete", "3.Delete edition", "4.Find", "5.Find edition","6.Show"};
    int rc = dialog(msgs);
    while(rc){
    	act[rc](tab);
        rc = dialog(msgs);
    }
	printf("That's all. Bye!\n");
	fclose(tab->file);
	free(tab->name);
	free_tab(tab);
	free(tab);
	free(file_name);
	return 0;	
}
