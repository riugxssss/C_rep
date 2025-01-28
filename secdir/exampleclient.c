//Client TCP from riugxss

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
    int portForServer;
    char LOCAL_address[200];
}info;

int client(info *data){
    int server_sock;
    struct sockaddr_in  addr;
    char buffer[BUFFER];
    char messageFromClient[BUFFER];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock != 0){
        fprintf(stderr, "Error with the server socket\n");
        free(data);
        return 1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(data->portForServer);
    if (inet_pton(AF_INET, data->LOCAL_address, &addr.sin_addr) != 0){
        fprintf(stderr, "Error converting the IP address\n");
        free(data);
        return 1;
    }

    if (connect(server_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0){
        fprintf(stderr, "Error connectin to the IP: %s", data->LOCAL_address);
        free(data);
        return 1;
    }

    printf("Connection from: %s | %d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

    size_t bytes_sent;
    size_t bytes_recv;
    printf("Send a message to the server (quit for leave)\n");    
    while (bytes_sent > 0 && bytes_recv > 0){
        fgets(messageFromClient, sizeof(messageFromClient), stdin);

        messageFromClient[strcspn(messageFromClient, "\n")] = '\0';
        if (strcmp(messageFromClient, "quit") == 0){
            printf("Exiting..\n");
            free(data);
            exit(EXIT_SUCCESS);
        }
        
        bytes_sent= send(server_sock, messageFromClient, strlen(messageFromClient), 0);
        if (bytes_sent < 0){
            fprintf(stderr, "Error sending the byte\n");
            free(data);
            return 1;
        }

        memset(buffer, 0, BUFFER);
        bytes_recv = recv(server_sock, buffer, BUFFER, 0);
        if (bytes_recv < 0){
            fprintf(stderr, "Error receiving the data from the serv\n");
            free(data);
            return 1;
        }
        printf("The server response: %s\n", buffer);
    }

    close(server_sock); 
    free(data);

    return 0;
}
int main(){
    info *data = malloc(sizeof(info));
    if (data == NULL){
        fprintf(stderr, "Error allocating the memory\n");
        free(data);
        return 1;
    }
    char ipaddr[150];
    int port;
    printf("Enter the port to connect: ");
    scanf("%d", port);
    if (port < 0 || port > 65535){
        fprintf(stderr, "Port out of the range (1-65535)\n");
        return 1;
    }
    printf("Enter the IP address: %d");
    scanf("%s", ipaddr);

    data->portForServer = port;
    strncpy(data->LOCAL_address, ipaddr, sizeof(ipaddr) +1);

    printf("Press enter to start the client..\n");
    getchar();

    free(data);
}
