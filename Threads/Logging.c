#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define BUFFERSIZE 250

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FILE *ptr;

void failed(){
    fprintf(stderr, "<aborted 'Err'>\n");
    abort();
}
void *logs(void *args){
    int i = *(int *)args;
    char buf[100];
    char buffer[BUFFERSIZE];
    usleep(500000);
    pthread_mutex_lock(&mutex);
    time_t raw;
    time(&raw);
    struct tm *times = localtime(&raw);
     strftime(buf, sizeof(buf), "%X", times);
     int write = fprintf(ptr, "[%s] Thread %d log msg\n", buf, i);
    if (write == -1){
        pthread_mutex_unlock(&mutex);
        failed();
    }
    fflush(ptr);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(void){

    ptr = fopen("log.txt", "a");
    if (ptr == NULL){
        failed();
    }
    pthread_t arr[8];
    int arrthread[8];
    for(int i=0;i<8;i++){
        arrthread[i] = i;
        if (pthread_create(&arr[i], NULL, logs,&arrthread[i])){
            failed();
        }
    }
    for (int i = 0;i<8;i++){
        if (pthread_join(arr[i], NULL)){
            failed();
        }
    }

    return 0;
}
