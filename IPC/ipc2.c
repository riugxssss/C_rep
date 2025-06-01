#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{

    int fd[2];
    if (pipe(fd) == -1){
        fprintf(stderr, "<pipe>");
        return 1;
    }
    char buf[150];
    pid_t proc = fork();
    if (proc < 0){
        fprintf(stderr, "Error");
    }
    if (proc == 0){
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        printf("ciao");
    }
    else {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        fgets(buf, sizeof(buf), stdin);
        printf("%s", buf);
    }
    
    return 0;
}
