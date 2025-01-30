#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

#define BACKLOG 5
#define BUFFER 1024

void print_help(){
    printf( "Usage: SERVER [OPTIONS]\n");
    printf( "Options:\n");
    printf( "  -h, --help           Show this help message and exit\n");
    printf( "  -g, --github         Show the GitHub account\n");
    printf( "  -p, --port           Specify the port to host\n");
    printf( "\n");

}

int serverfunc(int port_connect){
    struct sockaddr_in server_addr, client_addr;
    int serv_sock, client_sock;
    char ip_str[INET6_ADDRSTRLEN];
    char buffer[1024];
    char messageFor_client[BUFFER] = "DDos this server";
    size_t bytes_recv, bytes_send;
    char *stringmess = "quit";

   if((serv_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Error: %s", strerror(errno));
        return 1;
   }

   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(port_connect);
   server_addr.sin_addr.s_addr = INADDR_ANY;

   if (bind(serv_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
    fprintf(stderr, "Failed to associating the port to the socket! Error: %s\n", strerror(errno));
    close(serv_sock);
    return 1;
   }

   if (listen(serv_sock, BACKLOG) != 0){
        printf("Error: %s", strerror(errno));
        printf("Code type: %d", errno);
        close(serv_sock);
        exit(EXIT_FAILURE);
   }

   printf("Connected on port: %d\n", port_connect);

    socklen_t sizelenaddress = sizeof(client_addr.sin_addr);
   if ((client_sock= accept(serv_sock, (struct sockaddr*)&client_addr, &sizelenaddress)) == -1){
        printf("Error: %s", strerror(errno));
   }

    if (inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str)) == NULL){
        printf("Error: %s", strerror(errno));
        close(serv_sock);
        close(client_sock);
        return 1;
    }
    printf("Connection accepted: %s | %d\n", ip_str, ntohs(client_addr.sin_port));

    memset(buffer, 0, sizeof(buffer));
    while (true){
    bytes_recv = recv(client_sock, buffer, BUFFER, 0);
    if (bytes_recv == -1){
        fprintf(stderr, "Error: %s", strerror(errno));
        fprintf(stderr, "Code type error: %d", errno);
        close(serv_sock);
        close(client_sock);
        return 1;
    } else if (bytes_recv == 0){
        printf("Client disconnected..\n");
        break;
    }
        if (strncmp(buffer, stringmess, strlen(stringmess)) == 0){
        send(client_sock, "Bye from the server!", BUFFER, 0);
        close(client_sock);
        close(serv_sock);
        exit(EXIT_SUCCESS);
    }
        printf("Message from the client: %s\n", buffer);

    bytes_send = send(client_sock, messageFor_client, BUFFER, 0);
    if (bytes_send == -1){
        printf("Error: %s", strerror(errno));
        printf("Code type error: %d", errno);
        close(serv_sock);
        close(client_sock);
        return 1;
    }
    }
    return 0;
}
int main(int argc, char **argv){
    int var_parse;
    int port;
    if (argc < 2){
        printf("Missing requirment argument <port>\n");
        exit(EXIT_FAILURE);
    }

    
    struct option parse[] = {
        {"help", no_argument, 0, 'h'},
        {"port", required_argument, 0, 'p'},
        {"github", no_argument, 0, 'g'},
        {0,0,0,0}
    };
    while ((var_parse = getopt_long(argc, argv, "hp:g", parse, NULL)) != -1){
        switch (var_parse)
        {
        case 'h':
            printf("HELP INFO:\n");
            print_help();
            exit(EXIT_SUCCESS);
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'g':
            printf("GitHub: https://github.com/riugxssss\n");
            printf("All my projects in C -> C_rep\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            print_help();
            exit(EXIT_SUCCESS);
            break;
        }
    }
     if (port <= 0 || port > 65355){
        fprintf(stderr, "Port out of the range\n");
        exit(EXIT_FAILURE);
    }
    printf("Press enter to start the server\n");
    getchar();
    printf("Started..\n");
    serverfunc(port);

    return 0;
}
