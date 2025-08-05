#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define INFOVAR(x) printf("Name: %s\nMemory address: %p\n", #x, (void*)&(x), \
                    printf("Value: %d\n", x))
#define MAX(x, s) (x > s) ? x : s
#define GENTYPE(var) _Generic((var), \
    int: "int", \
    float: "float", \
    double: "double", \
    char: "char",  \
    void*: "void*", \
    default: "other type")

int IntConv(void *num){
    return *(int*)num;
}
void turn(volatile int *var){
    *var = 1;
}
void mapping(void){
    volatile int *dontoptpls = mmap(NULL, sizeof *dontoptpls, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1 , 0);
    *dontoptpls = 0;
    int i = 0;
    pid_t process;
    process = fork();
    if (process < 0){
        printf("Error with the process");
        exit(EXIT_FAILURE);
    }
    if (process == 0){
        printf("-SON PID: %d\n", getpid());
        printf("BEGIN: \n");
        while(!*dontoptpls){
            printf("In the loop\n");
            sleep(2);
        }
    } else {
        sleep(1);
        int status;
        printf("-MAIN PID: %d\n", process);
        turn(dontoptpls);
        waitpid(process, &status, 0);
        if (WIFEXITED(status)){
            printf("Son process closed\nexit code: %d\n", WEXITSTATUS(status));
        }
        printf("END: \n");

    }
}
int main(void){
   
    void *vartoChange;
    int varuser;
    int choice;
    printf("Choices:\n1)INFOVAR\n2)MAPwork\n");
    int t2 = scanf("%d", &choice);
    if (!(t2)){
        fprintf(stderr, "-scanf");
        exit(-1);
    }
    switch (choice)
    {
    case 1:
    printf("Enter a value for the var: ");
    int t1 = scanf("%d", &varuser);
    if (!(t1)){
        printf("-scanf");
        exit(-1);
    }

    printf("INFO VAR\n");
    INFOVAR(varuser);
    printf("Type: %s\n", GENTYPE(varuser));
    //typeof(IntConv(&varuser)) varchanged;
   // printf("New type: %s\n", GENTYPE(varchanged));
        break;
    case 2:
        mapping();
        break;
    default:
        printf("bro are you blind or what");
        break;
    }
    

    return 0;
}
