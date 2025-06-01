#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutual;
pthread_cond_t cond;
int fuel = 0;


void *rt(void *args){
    for (int i=0;i<5;i++){
        pthread_mutex_lock(&mutual);
        fuel += 60;
        printf("filling %d\n", fuel);
        pthread_mutex_unlock(&mutual);
        pthread_cond_broadcast(&cond);
        sleep(1);
    }

}

void *car(void *arg){
      pthread_mutex_lock(&mutual);
     while (fuel < 40){
        printf("no fuel\n");
        pthread_cond_wait(&cond, &mutual);

     }
        fuel -= 40;
        printf("got fuel: %d left\n", fuel);
        pthread_mutex_unlock(&mutual);
}


int main()
{
    pthread_t pt[5];
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutual, NULL);
    for (int i = 0;i<5;i++){
        if (i == 4){
        pthread_create(&pt[i], NULL, rt, NULL);
        }else {
            pthread_create(&pt[i], NULL, car, NULL);
        }
    }
    for (int i =0; i<5;i++){
        pthread_join(pt[i], NULL);
    }
    pthread_mutex_destroy(&mutual);
    pthread_cond_destroy(&cond);
    return 0;
}
