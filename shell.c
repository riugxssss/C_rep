#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>

#define MAX_LENGHT 100
#define RED "\033[1;31m"
#define RESET "\33[0m"

void handling(int sig){
    printf("\n<'Ctrl+C' pressed: exiting>");
    usleep(500000);
    exit(2);
}
void chgdir(const char *pathTochange){
    if (chdir(pathTochange) == -1){
        fprintf(stderr, "<invalid path>\n");
    }
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
    srand(time(NULL));
    int color = rand() % 8;
    char array[100];
    char cwds[MAX_LENGHT];
    signal(SIGINT, handling);
    int counter = 0;
    char command[MAX_LENGHT];
    char exitkey[5] = "exit";
    char bufferNAME[20];
    for (int i =0 ; i<27;i++){
        array[i] = '-';
    }
    printf("\033[1;5;37mINTERACTIVE SHELL "RESET "\033[1;%dmby riugxs\n", 30+color ,RESET);
    for (int i =0;i<27;i++){
        printf("\033[1;%dm%c" RESET,30+ color,array[i]);
        fflush(stdout);
        usleep(150000);
    }
    printf("\nEnter terminal name: ");
    scanf("%19s", bufferNAME);
    while (getchar() != '\n');
    putchar('\n');
    while(1){

        if (!(getcwd(cwds, MAX_LENGHT) != NULL)){
            fprintf(stderr, "<cwd>");
            continue;
        }
        printf("\033[32m("RESET"\033[1;%dm%s@unknown"RESET"\033[32m) - ",30 +color, bufferNAME, RESET);
        printf("\033[32m[\033[1;37m%s\033[0m\033[32m]\n-$ "RESET, cwds);
        if (fgets(command, MAX_LENGHT, stdin) == NULL){
            fprintf(stderr, "<fgets error>");
            exit(1);
        }
        command[strcspn(command, "\n")] = '\0';
        if (strncmp(command, exitkey, strlen(exitkey)) == 0){
            printf(RED"<exit command>\n"RESET);
            exit(0);
        }
        char *tokens =strtok(command, " ");

        if (strcmp(tokens, "cd")== 0){
            tokens = strtok(NULL, " ");
            chgdir(tokens);
        }else exec_command(command);
    }
    return 0;
}
