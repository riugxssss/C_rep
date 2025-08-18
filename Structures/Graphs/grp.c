#include <stdio.h>
#include <stdlib.h>

typedef struct graph_t {
        int tot;
        int **edges;
}graph;

void dest(graph *t){
        if (!t) return;

        for (int i = 0;i<t->tot;i++){
                if (t->edges[i]){
                        free(t->edges[i]);
                }
        }
        free(t->edges);
        free(t);
}

graph *create_graph(int tot){
        graph *ptr = malloc(sizeof(*ptr));
        if (!ptr){
                fprintf(stderr, "[!] Out of memory\n");
                exit(EXIT_FAILURE);
        }
        ptr->tot = tot;
        ptr->edges = calloc(tot, sizeof(int *));
        if (!ptr->edges){
                fprintf(stderr, "[!] Out of memory\n");
                free(ptr);
                exit(EXIT_FAILURE);
        }
        for (int i = 0;i<tot;i++){
                ptr->edges[i] = calloc(tot, sizeof(int));
                if (!ptr->edges[i]){
                        fprintf(stderr, "[!] Out of memory\n");
                        dest(ptr);
                }
        }
        return ptr;
}

void print_all(graph *ptr){
        if (!ptr) return;

        printf("Directed Graph {\n");
        for (int start = 0;start< ptr->tot;start++){
                for (int end = 0;end < ptr->tot;end++){
                        if (ptr->edges[start][end]){
                                printf("%d -> %d\n", start, end);
                        }
                }
        }
        printf("}\n");
}

static int checkifedge(graph *ptr, int start, int end){
        if (!ptr || start < 0 || start >= ptr->tot || end < 0 || end >= ptr->tot){
                return 0;
        }
        return  ptr->edges[start][end];
}
int add_vert(graph *ptr, int start, int end){
        if (checkifedge(ptr, start, end)){
                return 0;
        }
        ptr->edges[start][end] = 1;
        return 1;
}

int main(void){
        graph *ptr = create_graph(3);
 
        add_vert(ptr, 0, 1);
        add_vert(ptr, 1, 1);
        add_vert(ptr, 1, 2);

        print_all(ptr);
        dest(ptr);
        return 0;
}
