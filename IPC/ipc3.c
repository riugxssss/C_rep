#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    char buf[100];
    int fd[2];
    pipe(fd);
    if (pid == 0){
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        
    } else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        read(fd[0], buf, sizeof(buf));
        printf("%s", buf);
        wait(NULL);
    }
    return 0;
}
