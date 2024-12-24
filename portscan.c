//Riugxs port scanner V1 mutex, semaphore and poolthread usage, with logs

#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sema;
pthread_t thread_pool[MAX];

typedef struct {
    int port;
    char ipaddr[100];
} scan;


void logs_write(char *message){
    pthread_mutex_lock(&mutex);
    FILE *logging;
    logging = fopen("Portscanlogs.log", "a");
    if (logging == NULL){
        perror("Error opening the file");
        pthread_mutex_unlock(&mutex);
        exit(EXIT_FAILURE);
    }
    fprintf(logging, "%s\n", message);
    fclose(logging);
    pthread_mutex_unlock(&mutex);
}
void* scan_port(void *m3) {
    scan *data = (scan*)m3;
    int sock;
    struct sockaddr_in v1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating the socket");
        pthread_exit(NULL);
    }

    v1.sin_family = AF_INET;
    v1.sin_port = htons(data->port);
    if (inet_pton(AF_INET, data->ipaddr, &v1.sin_addr) <= 0) {
        perror("Error converting the IP");
        close(sock);
        free(data);
        pthread_exit(NULL);
    }

    if (connect(sock, (struct sockaddr*)&v1, sizeof(v1)) == 0) {
        pthread_mutex_lock(&mutex);
        printf("The port: %d is open\n", data->port);

        char connect[200];
        snprintf(connect, sizeof(connect), "IP: %s PORT OPEN: %d\n", data->ipaddr, data->port);
        logs_write(connect);
        pthread_mutex_unlock(&mutex);
    }

    close(sock);
    free(data);
    sem_post(&sema);
    pthread_exit(NULL);
}

void* thread_pool_worker(void* arg) {
    scan *data = (scan*)arg;
    scan_port((void*)data); 

    return NULL;
}

int main() {
    int max_port;
    char ip[100];
    int pool_thread = 10;

    printf("\033[1;35m▌│█║▌║▌║ \033[1;37m𝗣𝗢𝗥𝗧 𝗦𝗖𝗔𝗡𝗡𝗘𝗥 \033[1;35m║▌║▌║█│▌\t\t\033[1;35m[\033[1;37m!\033[1;35m]\033[1;37mRiugxss\n  \t\t\t\t\t\033[1;35m[\033[1;37m!\033[1;35m]\033[1;37mGitHub: \033[1;37mRiugxssss\n\n\n");
    printf("Enter the IP address: ");
    scanf("%s", ip);
    printf("Enter the max port: ");
    scanf("%d", &max_port);

    sem_init(&sema, 0, max_port);

    if (max_port < 0 || max_port > 65535) {
        perror("Out of the Range ");
        return 1;
    }

    time_t current = time(NULL);
    printf("Scanning the IP: %s \nAt: %s", ip, ctime(&current));
    char start[100];
    snprintf(start, sizeof(start), "Scanning the IP: %s AT: %s", ip, ctime(&current));
    logs_write(start);

    for (int i = 1; i <= max_port; i++) {

        scan *data = malloc(sizeof(scan));
        if (data == NULL){
            perror("Error with the memory");
            return 1;
        }

        strcpy(data->ipaddr, ip);
        data->port = i;
        sem_wait(&sema);

        pthread_create(&thread_pool[i % pool_thread], NULL, thread_pool_worker, (void*)data);
    }

    for (int i = 0; i < pool_thread; i++) {
        pthread_join(thread_pool[i], NULL);
    }

    time_t end = time(NULL);
    double elapsed = difftime(end, current);
    printf("Scanning completed in %.2f seconds \033[0m", elapsed);
    char end_scan[100];
    snprintf(end_scan, sizeof(end_scan), "Scanning the IP: %s completed in: %.2f seconds", ip, elapsed);

    char messagemain[100];
    snprintf(messagemain, sizeof(messagemain), "\n:)");
    logs_write(messagemain);

    sem_destroy(&sema);
    return 0;
}
