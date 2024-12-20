//Riugxs portscanner without multithreading

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

int main(){
    int port;
    char ip_address[100];
    struct sockaddr_in addrtarget;
    int sock;
    time_t start_time, end_time;

    printf("Enter the IP address: ");
    scanf("%s", ip_address);
    printf("Enter the max port: ");
    scanf("%d", &port);

    time(&start_time);
    printf("Scanning %s\nstarted at: %s\n", ip_address, ctime(&start_time));

    addrtarget.sin_family = AF_INET;

    if (inet_pton(AF_INET, ip_address, &addrtarget.sin_addr)  == 1){
    printf("IP valid.\n");
    return 1;
    } else {
        printf("IP invalid.\n");
    }


    for (int i=1; i<=port; i++){
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0){
            printf("Error with the socket creation...");
            return 1;
        }
        addrtarget.sin_port = htons(i);

        if (connect(sock, (struct sockaddr*)&addrtarget, sizeof(addrtarget)) == 0){
            printf("Port: %i open\n", i);

        } else {
            printf("Port: %i close\n", i);
        }
        close(sock);
    }
    printf("Scanning %s completed at: %s\n", ip_address, ctime(&end_time));
    double elapsed = difftime(end_time, start_time);
    printf("The operation completed in: %.2f\n", elapsed);    
    return 0;

}
