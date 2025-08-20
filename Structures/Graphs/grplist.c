#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int v;
	struct node *next;
}node;

typedef struct graph {
	int isdir;
	int totnum;
	struct node **adjlist;
}graph;

node *create_node(int v){
	node *newn = malloc(sizeof(*newn));
	if (!newn){
		fprintf(stderr, "[!] Out of memory\n");
		exit(EXIT_FAILURE);
	}
	newn->v = v;
	newn->next = NULL;
	return newn;
}
graph *create_graph(int tot, int isdirected){
	graph *ptr = malloc(sizeof(*ptr));
	if (!ptr){
		fprintf(stderr, "[!] Out of memory\n");
		exit(EXIT_FAILURE);
	}
	ptr->isdir = isdirected;
	ptr->totnum = tot;
	ptr->adjlist = malloc(sizeof(int *) * tot);
	if (!ptr->adjlist){
		fprintf(stderr, "[!] Out of memory\n");
		free(ptr);
		exit(EXIT_FAILURE);
	}
	for (int i = 0;i<tot;i++){
		ptr->adjlist[i] = NULL;
	}
	return ptr;
}

/*
vertex 0: ptr->adjlist[0] --> [1 | next] --> [2 | next] --> NULL list of his neighbours: 1 2 
like vertex 0 is adiacent to 1 and 2 if there are undirected (bidirezional) 1 and 2 also are 
point to vertex 0

vertex 1: ptr->adjlist[1] --> [0 | next] --> NULL
vertex 2: ptr->adjlist[2] --> [0 | next] --> NULL
vertex 3: ptr->adjlist[3] --> NULL

our array of ptr -> is an head of the linked list
*/

void add_edge(graph *ptr, int src, int dst){
	node *newn = create_node(dst);
	newn->next = ptr->adjlist[src]; 
	ptr->adjlist[src] = newn;
	if (!ptr->isdir){
		newn = create_node(src);
		newn->next = ptr->adjlist[dst];
		ptr->adjlist[dst] = newn;
	}
}

void print_graph(graph *ptr){
	if (!ptr) return;
	printf("Adjacency List: \n");
	for (int i = 0;i<ptr->totnum;i++){
		node *tmp = ptr->adjlist[i];
		printf("%d ->>", i);
		while (tmp){
			printf(" %d -> ", tmp->v);
			tmp = tmp->next;
		}
		printf(" NULL\n");
	}
	putchar('\n');
}

void destroy(graph *ptr){
	if (!ptr) return;
	for (int i = 0;i<ptr->totnum;i++){
		node *tmp = ptr->adjlist[i];
		while (tmp){
			node *tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
	}
	free(ptr->adjlist);
	free(ptr);
	ptr = NULL;
}

int main(void){

	graph *ptr = create_graph(3, 0);
	add_edge(ptr, 0, 1);
	add_edge(ptr, 0, 2);
	add_edge(ptr, 1, 2);
	print_graph(ptr);
	destroy(ptr);
	return 0;
}
