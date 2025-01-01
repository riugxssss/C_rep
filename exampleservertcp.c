//Server TCP from riugxss 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/stat.h>
#define BUFFER 1024

typedef struct
{
    int port;
}info;

int server(info *data){

    int sock, cosk;
    struct sockaddr_in a, b;
    char buffer[BUFFER];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock != 0){
        fprintf(stderr, "Error with the socket");
        
        return 1;
    }

    a.sin_addr.s_addr = INADDR_ANY;
    a.sin_family = AF_INET;
    a.sin_port = htons(data->port);

    if (bind(sock, (struct sockaddr*)&a, sizeof(a)) !=0 ){
        fprintf(stderr, "Error associating the port with the socket");
        free(data);
        return 1;
    }
    if (listen(sock, 3) == -1){
        fprintf(stderr, "Error the listening on port: %d", data->port);
        free(data);
        return 1;
    }
    printf("Successfull connession on port: %d", data->port);

    socklen_t lenaddr = sizeof(b.sin_addr);
    cosk = accept(sock, (struct sockaddr*)&b, &lenaddr);
    if (cosk != 0){
        fprintf(stderr, "Error with the socket client");
        free(data);
        return 1;
    }

    printf("Connection from: %s | %d", inet_ntoa(b.sin_addr), ntohs(b.sin_port));

    memset(buffer, 0, BUFFER);
    size_t buffer_recv = recv(cosk, buffer, BUFFER, 0);
    if (buffer_recv <= 0){
        fprintf(stderr, "Error with recv");
        free(data);
        return 1;
    }
    printf("Message from the client: %s", buffer);
    size_t bytes_send;
    char *message = "Hi from the server!;";
    bytes_send = send(cosk, message, strlen(message), 0);
    if (bytes_send == -1){
        fprintf(stderr, "Error sending the message");
        free(data);
        return 1;
    }

    printf("Message sended by the client: %s\n", message);

    
    close(cosk);
    close(sock);
    free(data);
    return 0;
}
int main(){
    info *data = malloc(sizeof(info));
    if (data == NULL){
        fprintf(stderr, "Error allocating memory");
        return 1;
    }

    int portToServer;
    printf("Enter the port for host the server: ");
    scanf("%d", portToServer);

    if (portToServer < 0 || portToServer > 65535){
        fprintf(stderr, "Port out of the range (1-65535)\n");
    }
    data->port = portToServer;
    printf("Press enter to start the server..\n");
    getchar();
    server(data);
    free(data);
    return 0;
}
