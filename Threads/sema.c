#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 12
sem_t sema;

void *rt(void *args){
    int index = *(int *)args;
    printf("Thread n:%d wait\n", index);
    sem_wait(&sema);
    printf("Thread n:%d logged in\n", index);
    sleep(1);
    printf("Thread n:%d logged out\n", index);
    sem_post(&sema);
}


int main(void){
    
    pthread_t th[N];
    
    int a[N];
    sem_init(&sema, 0, 6);
    for (int i = 0;i<N;i++){
        a[i] = i;
        pthread_create(&th[i], NULL, rt, &a[i]);
    }
    for (int i =0;i<N;i++){
        pthread_join(th[i], NULL);
    }
    sem_destroy(&sema);
    return 0;
}
