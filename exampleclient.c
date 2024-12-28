#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>


#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
    char mess[BUFFER_SIZE];
    char buffer[BUFFER_SIZE] = {0};
    struct sockaddr_in server;
    int sock;
    char *ip = "127.0.0.0";

    sock= socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        printf("Error with the socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if (inet_pton(AF_INET, ip, &server.sin_addr) == 1){
        printf("The IP is valid");
    }
    else {
        perror("IP address invalid..");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Impossible to connect to the server");
        close(sock);
        return 1;
    }
    printf("Connected to the server on port: %d", PORT);

    while (true){
        printf("Send a message (exit for quit) " );
        fgets(mess, sizeof(mess), stdin);
        mess[strcspn(mess, "\n")] = '\0'

        if (strcmp(mess, "exit") == 0){
            printf("Connetions interrupted");
            break;
        }
        send(sock, mess, strlen(mess), 0);

        memset(buffer, 0, BUFFER_SIZE);
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes < 0){
            printf("Connetion closed by the server");
            break;
        }
        printf("Server response: %s", buffer);


    }
    close(sock);

    return 0;
}
