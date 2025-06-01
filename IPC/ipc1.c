#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
    char *buf = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int fd[2];
    if (pipe(fd) == -1){
        fprintf(stderr, "<pipe>");
        exit(EXIT_FAILURE);
    }
    pid_t proc1 = fork();
    int restorefd = dup(1);
    if (proc1 ==0 ){
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        printf("proc1 sending to base\n");
        exit(0);
    } else {
        wait(NULL);
        close(fd[1]);
        read(fd[0], buf, 100);
        exit(0);
}
    dup2(fd[1], restorefd);
    pid_t testa = fork();
    if (testa == 0){
        printf("c");
    }
    return 0;
}
