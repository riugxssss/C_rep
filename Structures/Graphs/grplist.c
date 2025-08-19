#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    struct node *next;
}node;
typedef struct graph {
    int tot;
    struct node **list;
    int isdir;
}graph;

node *create_node(int n){   
    node *newn = malloc(sizeof(*newn));
    newn->next = NULL;
    newn->v = n;
    return newn;
}

graph *create_graph(int tot, int isdir){
    graph *ptr = malloc(sizeof(*ptr));
    ptr->tot = tot;
    ptr->isdir = isdir;
    ptr->list = malloc(sizeof(node *) * tot);
    for (int i= 0;i<tot;i++){
        ptr->list[i] = NULL;
    }
    return ptr;
}
void print_all(graph *ptr){
    if (!ptr) return;
    for (int i = 0; i<ptr->tot;i++){
        node *tmp = ptr->list[i];
        printf("List [%d]: ", i);
        while (tmp){
            printf("%d ", tmp->v);
            tmp = tmp->next;
        }
        putchar('\n');
    }
}

void add_edge(graph *ptr, int src, int dst){
    node *newn = create_node(dst);
    newn->next = ptr->list[src]; //is the head
    ptr->list[src] = newn;

    if (!ptr->isdir){
        newn = create_node(src);
        newn->next = ptr->list[dst]; //is the head of the linked list
        ptr->list[dst] = newn;
    }
}

void destroy(graph *ptr) {
    if (!ptr) return;
    for (int i = 0; i < ptr->tot; i++) {
        node *tmp = ptr->list[i];
        while (tmp) {
            node *next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }
    free(ptr->list);
    free(ptr);
}

int main(void){
    	
	graph * ptr = create_graph(4, 0);
	add_edge(ptr, 0, 1);
	add_edge(ptr, 0, 2);
	add_edge(ptr, 0, 3);
	add_edge(ptr, 1, 2);
	print_all(ptr);
    destroy(ptr);
    return 0;
}
