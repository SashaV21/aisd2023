#include "lab5.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int search(Graph* graph, int start){
	Queue *q = queue_new();
	unsigned int port = graph->network[start]->port;
	int* visited = calloc(sizeof(int),graph->size);
	queue_put(q, start);
	while(q->head!=NULL){
		int index;
		queue_get(q, &index);
		visited[index] = 1;
		Edge* ptr = graph->network[index]->connect;
		while(ptr){
			int flag = 0;
			for (int i=0; i < ptr->count; i++){
				if (ptr->port[i] == port) flag = 1;
			}
			if (ptr->index!=start && graph->network[ptr->index]->port == port && flag == 1){
				free(visited);
				queue_delete(q);
				return ptr->index;	
			}
			else if (graph->network[ptr->index]->port != port && flag == 1 && visited[ptr->index]==0){
				queue_put(q, ptr->index);	
			}
			ptr = ptr->next;
		}
	}
	free(visited);
	queue_delete(q);
	return -1; 
}

int* min_way(Graph* graph, int start, int end){
		unsigned int port = graph->network[start]->port;
        int* pred = calloc(sizeof(int), graph->size);
        pred[start] = start;
        int* len = calloc(graph->size, sizeof(int));
        for (int i=0; i<graph->size; i++){
        	len[i] = INT_MAX;
        }
        len[start] = 0;
        for (int c = 0; c < graph->size-1; c++){
        	for (int i = 0; i < graph->size; i++){
            	Edge* ptr = graph->network[i]->connect;
        		while(ptr){
        			int flag = 0;
        			for (int n=0; n < ptr->count; n++){
        				if (ptr->port[n] == port) flag = 1;
        			}
                	if (flag == 1 && len[i] != INT_MAX && (len[i] + 1) < len[ptr->index]){
                        pred[ptr->index] = i;
                    	len[ptr->index] = len[i] + 1;
                	}
            	ptr = ptr->next;
           		}
           	}
        }
        if (len[end] == INT_MAX){
            free(pred);
        	free(len);
            return NULL;
        }
        else{
        	printf("way len: %d\n", len[end]);
            free(len);
            return pred;
        }
}

void dfs(Graph* graph, Vector* help, int index){
	help->visit[index] = 1;
	printf("Computer: %s\n", graph->network[index]->name);
	Edge* ptr = graph->network[index]->connect;
	while(ptr){
		if (help->visit[ptr->index] == 0){
			dfs(graph, help, ptr->index);
		}
		ptr = ptr->next;
	}
}

int sp_func(Graph* graph){
	Vector* help = malloc(sizeof(Vector));
	help->visit = calloc(sizeof(int), graph->size);
	int j = 0;
	for (int i = 0; i < graph->size; i++){
		if (help->visit[i] != 1){
			j++;
			printf("Element #%d\n", j);
			dfs(graph, help, i);
		}
	}
	free(help->visit);
	free(help);
	return 0;
}

int change_name(Graph* graph, int index, char* new, int port){
	free(graph->network[index]->name);
	graph->network[index]->name = new;
	graph->network[index]->port = port;
	return 0;
}

int change_port(Graph* graph, int index1, int index2, unsigned int* port, int n){
	Edge* ptr = graph->network[index1]->connect;
	while(ptr){
		if(ptr->index == index2){
			free(ptr->port);
			ptr->port = port;
			ptr->count = n;
			return 0;
		}
		ptr = ptr->next;
	}
	return 1;
}

Graph* make_graph(){
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->size = 0;
	graph->network = malloc(sizeof(Top*));
	return graph;
}

void free_graph(Graph* graph){
	for (int i = 0; i < graph->size; i++){
		Edge* ptr = graph->network[i]->connect, *prev;
		while(ptr){
			prev = ptr;
			ptr = ptr->next;
			free(prev->port);
			free(prev);
		}
		free(graph->network[i]->name);
		free(graph->network[i]);
	}
	free(graph->network);
}

int find_top(Graph* graph, char* name){
	for (int i = 0; i < graph->size; i++){
		if (strcmp(graph->network[i]->name, name) == 0) return i;
	}
	return -1;
}

int add_top(Graph *graph, char* name, int port){
	graph->network = realloc(graph->network, (graph->size + 1) * sizeof(Top));
	Top* new = malloc(sizeof(Top));
	new->name = name;
	new->port = port;
	new->connect = NULL;
	graph->network[graph->size] = new;
	graph->size += 1;
	return 0;
}

int add_edge(Graph *graph, int start, int end, unsigned int* port, int n){
	Edge* new = malloc(sizeof(Edge));
	new->index = end;
	new->count = n;
	new->port = port;
	new->next = graph->network[start]->connect;
	graph->network[start]->connect = new;
	return 0;
}

int del_edge(Graph *graph, int start, int end){
	Edge* ptr = graph->network[start]->connect, *prev = NULL;
    while (ptr && ptr->index != end) {
        prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr) {
        return 1;
    }
    if (prev == NULL) {
        graph->network[start]->connect = ptr->next;
    }
    else{
        prev->next = ptr->next;
    }
    free(ptr->port);
    free(ptr);
	return 0;
}

int del_top(Graph *graph, int index){
	Top* del = graph->network[index];
    Edge *ptr = del->connect;
    while (ptr){
    	del_edge(graph, ptr->index, index);
        ptr = ptr->next;
    }
    for (int i = index; i < graph->size-1; i++){
    	graph->network[i] = graph->network[i+1];
    	ptr = graph->network[i]->connect;
        while(ptr){
        	if  (ptr->index > index) ptr->index-=1;
            ptr=ptr->next;
        }
   	}
    graph->size-=1;
    graph->network = realloc(graph->network, graph->size*sizeof(Top*));
	ptr = del->connect;
	Edge *prev;
	while (ptr) {
		prev = ptr;
	    ptr = ptr->next;
	    free(prev->port);
		free(prev);
	}
    free(del->name);
    free(del);
    return 0;
}

void graph_print(Graph* graph){
	for (int i = 0; i < graph->size; i++){
		printf("Computer: %s(port: %d)-> ",graph->network[i]->name, graph->network[i]->port);
		Edge* ptr = graph->network[i]->connect;
		while(ptr){
			printf("%s(p:", graph->network[ptr->index]->name);
			for (int j = 0; j < ptr->count; j++){
				printf("%d ", ptr->port[j]);
			}
			printf(")->");
			ptr = ptr->next;
		}
		printf("NULL\n");
	}
}

int get_int(int* n){
	int flag;
	do{
		flag=scanf("%d",n);
	    if(flag<0) return 0;
	    if (flag==0) scanf("%*c");
	}while(flag==0 && (*n) < 0);
}

char *get_str(){
	char *ptr = (char*)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			free(ptr);
			ptr = NULL;
			continue;
		}
		else if (n == 0){
			scanf("%*c");
			if (len == 0) return NULL;
	    }
	    else {
	    	len += strlen(buf);
	     	ptr = (char *)realloc(ptr, (len+1)*sizeof(char));
	     	strcat(ptr, buf);
	   	}
	} while (n > 0);
	return ptr;
}
