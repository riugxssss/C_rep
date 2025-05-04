#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <signal.h>

#define MAX_LENGHT 100
#define RED "\033[1;31m"
#define RESET "\33[0m"

void handling(int sig){
    printf("\n<'Ctrl+C' pressed: exiting>");
    usleep(500000);
    exit(2);
}

void exec_command(char *command){
    pid_t process;
    process = fork();
    if (process == 0){
        char *args[75];
        int count = 0;
        char *tokens = strtok(command, " ");
        
        while (tokens != NULL){
            args[count++] = tokens;
            tokens = strtok(NULL, " ");
        }
        args[count] = NULL;
        
        if (execvp(args[0], args) == -1){
            fprintf(stderr, "<invalid command>\n");
            exit(EXIT_FAILURE);
        }
        exit(1);
        
    } else if (process > 0){
        wait(NULL);
    } else {
        fprintf(stderr, "<process error>\n");
        exit(-1);
    }
}
int main()
{
    signal(SIGINT, handling);
    char command[MAX_LENGHT];
    char exitkey[5] = "exit";
    char bufferNAME[20];
    printf("INTERACTIVE SHELL "RED"by riugxs"RESET"\n---------------------------\n\n");
    
    printf("Enter your name: ");
    scanf("%19s", bufferNAME);
    while (getchar() != '\n');
    while(1){
        printf("%s@unknown> ", bufferNAME);
        if (fgets(command, MAX_LENGHT, stdin) == NULL){
            fprintf(stderr, "<fgets error>");
            exit(1);
        }
        command[strcspn(command, "\n")] = '\0';
        if (strncmp(command, exitkey, strlen(exitkey)) == 0){
            printf("<exit command>\n");
            exit(0);
        }
        
        exec_command(command);
    }
    return 0;
}
