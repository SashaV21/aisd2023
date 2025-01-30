#include <stdio.h>
#include <stdlib.h>
#include "lab5.h"
#include "dialog.h"
	
int D_Add_Top(Graph *graph){
	printf("Enter name:\n");
	char *name = get_str();
	printf("Enter port:\n");
	int port;
	get_int(&port);
	if (find_top(graph, name) == -1) add_top(graph, name, port);
	else{
		puts("Exist!");
		free(name);
		return 1;
	}
	return 0;
}

int D_Change_Top(Graph *graph){
	printf("Enter old name:\n");
	char *old = get_str();
	printf("Enter new port:\n");
	int port;
	get_int(&port);
	int index = find_top(graph, old);
	free(old);
	if (index != -1){
		printf("Enter new name:\n");
		char *new = get_str();
		change_name(graph, index, new, port);
	}
	else{
		puts("No such computer!");
		return 1;
	}
	return 0;
}

int D_Search(Graph *graph){
	printf("Enter name:\n");
	char *name = get_str();
	int index = find_top(graph, name);
	if (index!=-1){
		int res = search(graph, index);
		if (res==-1) puts("nothing");
		else printf("Name: %s\n", graph->network[res]->name);
	}
	else{
		puts("No such key!");
		free(name);
		return 1;
	}
	free(name);
	return 0;
}

int D_Min_Way(Graph *graph){
	printf("Enter first name:\n");
	char *name1 = get_str();
	printf("Enter second name:\n");
	char *name2 = get_str();
	int index1 = find_top(graph, name1);
	int index2 = find_top(graph, name2);
	free(name1);
	free(name2);
	if (index1 == -1 || index2 == -1){
		puts("No such computer!");
		return 1;
	}
	int* res = min_way(graph, index1, index2);
	if (res==NULL) puts("no way!");
	else{
		int i = res[index2];
		printf("%s", graph->network[index2]->name);
		while(i != index1){
			printf("<-%s", graph->network[i]->name);
			i = res[i];
		}
		printf("<-%s\n", graph->network[index1]->name);
		free(res);
	}
	return 0;
}

int D_Del_Top(Graph *graph){
	printf("Enter name:\n");
	char *name = get_str();
	int index = find_top(graph, name);
	if (index != -1) del_top(graph, index);
	else{
		puts("No such computer!");
		free(name);
		return 1;
	}
	free(name);
	return 0;
}

int D_Del_Edge(Graph *graph){
	printf("Enter first name:\n");
	char *name1 = get_str();
	printf("Enter second name:\n");
	char *name2 = get_str();
	int start = find_top(graph, name1);
	int end = find_top(graph, name2);
	if (start != -1 && end != -1){
		del_edge(graph, start, end);
		del_edge(graph, end, start);
	}
	else{
		puts("No such edge!");
	}
	free(name1);
	free(name2);
	return 0;
}

int D_Add_Edge(Graph *graph){
	printf("Enter first name:\n");
	char *name1 = get_str();
	printf("Enter second name:\n");
	char *name2 = get_str();
	int start = find_top(graph, name1);
	int end = find_top(graph, name2);
	free(name1);
	free(name2);
	if (start == -1 || end == -1){
		puts("No such computers!");
		return 1;
	}
	if (start == end){
		puts("No!");
		return 1;
	}
	printf("Enter count of port:\n");
	int n;
	get_int(&n);
	unsigned int* port1 = malloc(n * sizeof(int));
	unsigned int* port2 = malloc(n * sizeof(int));
	for (int i = 0; i<n; i++){
		printf("Enter #%d port:\n", i+1);
		int port;
		get_int(&port);
		port1[i] = port;
		port2[i] = port;
	}
	add_edge(graph, start, end, port1, n);
	add_edge(graph, end, start, port2, n);
	return 0;
}

int D_Change_Edge(Graph *graph){
	printf("Enter first name:\n");
	char *name1 = get_str();
	printf("Enter second name:\n");
	char *name2 = get_str();
	int start = find_top(graph, name1);
	int end = find_top(graph, name2);
	free(name1);
	free(name2);
	if (start == -1 || end == -1){
		puts("No such computers!");
		return 1;
	}
	printf("Enter count of port:\n");
	int n;
	get_int(&n);
	unsigned int* port1 = malloc(n * sizeof(int));
	unsigned int* port2 = malloc(n * sizeof(int));
	for (int i = 0; i<n; i++){
		printf("Enter #%d port:\n", i+1);
		int port;
		get_int(&port);
		port1[i] = port;
		port2[i] = port;
	}
	change_port(graph, start, end, port1, n);
	change_port(graph, end, start, port2, n);
	return 0;
}

int D_Special(Graph *graph){
	if (graph->size == 0) puts("Empty!");
	else sp_func(graph);
	return 0;
}

int D_Show(Graph *graph){
	if (graph->size > 0) graph_print(graph);
	else puts("Empty");
}

int dialog(const char *msgs[]){
	char *errmsg = "";
	int rc;
	int i, n;
	do{
		puts(errmsg);
		errmsg = "You are wrong. Repeate, please!";
		for(i = 0; i < 11; ++i)
		puts(msgs[i]);
		puts("Make your choice:");
		n = get_int(&rc);
		if(n == 0)
		rc = 0;
	} while(rc < 0 || rc >= 11);
	scanf("%*c");
	return rc;
}
