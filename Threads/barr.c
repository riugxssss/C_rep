#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_barrier_t barr;

void *rt(void *args){
    int ind = *(int*)args;
    printf("Threads joining\n");
    sleep(1);
    pthread_barrier_wait(&barr);
    printf("Here we go\n");
    
}


int main()
{
    pthread_t arr[6];
    int id[6];
    int i;
    pthread_barrier_init(&barr, NULL, 2);
    for (i = 0;i<6;i++){
        id[i] = i;
        pthread_create(&arr[i], NULL, rt, &id[i]);
    }
    for (i = 0;i< 6;i++){
        pthread_join(arr[i], NULL);
    }
    pthread_barrier_destroy(&barr);

    return 0;
}
