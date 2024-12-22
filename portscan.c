//Port scanner by riugxss with multi threading + mutex for race conditions!

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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct 
{
    int port;
    char ipaddr[100];
}scan;

void* scan_port(void *m3){
    scan *data = (scan*)m3;
    int sock;
    struct sockaddr_in v1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("Error creating the socket");
        pthread_exit(NULL);
    }

    v1.sin_family = AF_INET;
    v1.sin_port = htons(data->port);
    if (inet_pton(AF_INET, data->ipaddr, &v1.sin_addr) <= 0){
        perror("Error converting the IP");
        close(sock);
        free(scan);
        pthread_exit(NULL);
    }

    if (connect(sock, (struct sockaddr*)&v1, sizeof(v1)) == 0){
        pthread_mutex_lock(&mutex);
        printf("The port: %d is open\n", data->port);
        pthread_mutex_unlock(&mutex);
    }


    close(sock);
    free(data);
    pthread_exit(NULL);
}

int main(){
    int max_port;
    char ip[100];
    int number_threads = 0;

    printf("\033[1;35m▌│█║▌║▌║ \033[1;37m𝗣𝗢𝗥𝗧 𝗦𝗖𝗔𝗡𝗡𝗘𝗥 \033[1;35m║▌║▌║█│▌\t\t\033[1;35m[\033[1;37m!\033[1;35m]\033[1;37mRiugxss\n  \t\t\t\t\t\033[1;35m[\033[1;37m!\033[1;35m]\033[1;37mGitHub: \033[1;37mRiugxssss\n\n\n");
    printf("Enter the IP address: ");
    scanf("%s", ip);
    printf("Enter the max port: ");
    scanf("%d", &max_port);

    if (max_port < 0 || max_port > 65535){
        perror("Out of the Range ");
        return 1;
    }

    pthread_t threads[max_port];

    time_t current = time(NULL);
    printf("Scanning the IP: %s \nAt: %s", ip, ctime(&current));

    for (int i=1; i<=max_port; i++){
        scan *data = malloc(sizeof(scan));
        if (data == NULL){
            perror("Error allocating the memory");
            return 1;
        }

        strcpy(data->ipaddr, ip);
        data->port = i;

        if (pthread_create(&threads[number_threads], NULL, scan_port, (void*)data) != 0){
            perror("Failed to create the thread");
            return 1;
        }
        
        number_threads++;

        if (number_threads>= 100){
            for (int j=0; j<number_threads;j++){
                pthread_join(threads[j], NULL);
            }
            number_threads = 0;
        }
    }
    for (int i=0; i<number_threads; i++){
        pthread_join(threads[i], NULL);
    }

    time_t end = time(NULL);
    double elpsd = difftime(end, current);
    printf("Scanning completed in %.2f seconds \033[0m", elpsd);


    return 0;
}
