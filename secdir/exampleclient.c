#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#define BUFFER 1024

typedef struct
{
    int port_main;
    char local_address[200];
} info;

int client(info *data){
    struct sockaddr_in server_addr;
    int socketToConn;
    size_t bytes_recv, bytes_send;
    char message[BUFFER], buffer[BUFFER];
    char *stringmess = "quit";

    if ((socketToConn = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "Error: %s", strerror(errno));
        free(data);
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port_main);
    if (inet_pton(AF_INET, data->local_address, &server_addr.sin_addr) == -1){
        fprintf(stderr, "Error: %s", strerror(errno));
        free(data);
        close(socketToConn);
        return -1;
    }

    if (connect(socketToConn, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        fprintf(stderr, "Error: %s", strerror(errno));
        free(data);
        close(socketToConn);
        return -1;
    }

    printf("Connected to the server\nINFO:\nIP: %s\nPORT: %d\n", data->local_address, data->port_main);

    printf("Write a message to the server! (quit to leave)\n");

    while (true) {
         if (strncmp(message, stringmess, strlen(stringmess)) == 0){
            printf("Exiting..\n");
            free(data);
            close(socketToConn);
            exit(EXIT_SUCCESS);
         }
        printf("Enter a message: ");
        fgets(message, sizeof(message), stdin);

        message[strcspn(message, "\n")] = '\0';

        bytes_send = send(socketToConn, message, BUFFER, 0);
        if (bytes_send == -1){
            fprintf(stderr, "Error: %s", strerror(errno));
            free(data);
            close(socketToConn);
            exit(EXIT_FAILURE);
        }

        memset(buffer, 0, BUFFER);

        bytes_recv = recv(socketToConn, buffer, BUFFER, 0);
        if (bytes_recv == -1){
            fprintf(stderr, "Error: %s", strerror(errno));
            free(data);
            close(socketToConn);
            exit(EXIT_FAILURE);
        }

        printf("Message from the server is: %s\n", buffer);
    }

    free(data);
    close(socketToConn);
}

void print_help(){
    printf("Usage: CLIENT [OPTIONS]\n");
    printf("Options:\n");
    printf("  -h, --help           Show this help message and exit\n");
    printf("  -g, --github         Show the GitHub account\n");
    printf("  -p, --port           Specify the port to connect to\n");
    printf("  -a, --address        Specify the IP address to connect\n");
    printf("\n");
}

int main(int argc, char **argv){
    int port;
    char IP_addr[196];
    int var_parse;


    info *data = malloc(sizeof(info));
    if (data == NULL){
        fprintf(stderr, "Failed allocating the memory\n");
        return 1;
    }

    struct option parse[] = {
        {"help", no_argument, 0, 'h'},
        {"port", required_argument, 0, 'p'},
        {"address", required_argument, 0, 'a'},
        {"github", no_argument, 0, 'g'},
        {0,0,0,0}
    };

    while ((var_parse = getopt_long(argc, argv, "hp:a:g", parse, NULL)) != -1){
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
        case 'a':
            strncpy(IP_addr, optarg, sizeof(IP_addr) - 1);  
            IP_addr[sizeof(IP_addr) - 1] = '\0';  
            break;
        case 'g':
            printf("GitHub: https://github.com/riugxssss\n");
            printf("All my projects in C -> C_rep\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            print_help();
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (port < 1 || port > 65535){
        fprintf(stderr, "The port is out of the range\n");
        free(data);
        return 1;
    }

    data->port_main = port;
    strncpy(data->local_address, IP_addr, sizeof(data->local_address) - 1);
    data->local_address[sizeof(data->local_address) - 1] = '\0';  

    printf("Press enter to start the client\n");
    getchar();
    printf("Started..\n");
    client(data);

    free(data);
    return 0;
}
