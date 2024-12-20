#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER  1024

int main(){
    int sock;
    struct sockaddr_in server, client;
    char buffer[BUFFER];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        printf("Error with the socket");
        return 1;
    }
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Error binding");
        close(sock);
        return 1;
    }
    printf("Connetion work\n");

    if (listen(server, 10) < 0){
        printf("Impossible listening");
        close(sock);
        return 1;
    }
    printf("Listening on port: %d", PORT);

    socklen_t addr_cleint = sizeof(client.sin_addr);
    client = accept(server, (struct sockaddr*)&client, &addr_cleint);
    if (client < 0){
        printf("The server refused the connection");
    }
    printf("The client is connected");

    memset(buffer, 0, BUFFER);
    recv(client, buffer, 0, BUFFER);
    pritnf("Message to the server %s\n", buffer);
    char *reply = "Hi from the serv!";
    send(client, reply, strlen(reply), 0);

    close(client);
    close(server);



    return 0;
}
