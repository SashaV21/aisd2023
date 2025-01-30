#ifndef LAB5_H
#define LAB5_H

typedef struct Edge{
	int index;
	unsigned int* port;
	int count;
	struct Edge* next;
}Edge;

typedef struct Top{
	char* name;
	unsigned port;
	Edge* connect;
}Top;

typedef struct{
	Top** network;
	int size;
}Graph;

Graph* make_graph();
void free_graph(Graph*);
char* get_str();
int get_int(int*);
int add_top(Graph*, char*, int);
int add_edge(Graph*, int, int, unsigned int*, int);
void graph_print(Graph*);
int find_top(Graph*, char*);
int del_edge(Graph*, int, int);
int del_top(Graph*, int);
int search(Graph*, int);
int sp_func(Graph*);
int* min_way(Graph*, int, int);
int change_name(Graph*, int, char*, int);
int change_port(Graph*, int, int, unsigned int*, int);
#endif
