#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;  

void* consumer(void* arg) {
    printf("Consumer waiting for resource...\n");
    sem_wait(&sem);  
    printf("Consumer acquired resource!\n");
    return NULL;
}

void* producer(void* arg) {
    printf("Producer producing resource...\n");
    sem_post(&sem); 
    printf("Producer released resource!\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&sem, 0, 0);

    pthread_create(&t1, NULL, consumer, NULL);
    pthread_create(&t2, NULL, producer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);

    return 0;
}
