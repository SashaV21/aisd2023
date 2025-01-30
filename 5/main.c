#include "lab5.h"
#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"

int main(){
	Graph *graph = make_graph();
	int (*act[])(Graph *) = {NULL, D_Show, D_Add_Top, D_Add_Edge, D_Del_Top, D_Del_Edge, D_Search, D_Min_Way, D_Special, D_Change_Top, D_Change_Edge};
    const char *msgs[] = {"0.Quit", "1.Show","2.Add computer", "3.Add connect", "4.Delete computer",
     						"5.Delete connect", "6.Search", "7.Min way", "8.Special func", "9.Change name and port", "10.Change ports"};
    int rc = dialog(msgs);
    while(rc){
    	act[rc](graph);
        rc = dialog(msgs);
    }
	printf("That's all. Bye!\n");
	free_graph(graph);
	free(graph);
	return 0;	
}






