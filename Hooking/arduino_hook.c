#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define WHITE "\033[1;37m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

static ssize_t (*realwrite)(int fd, const void *buf, size_t byte);

__attribute__((constructor))
void hook_init(void){

    realwrite = dlsym(RTLD_NEXT, "write");
    if (realwrite == NULL){
        fprintf(stderr, RED "["WHITE"HOOK ERROR"RED"] "RESET"Impossible to find 'write' address: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, RED"["WHITE"HOOK INIT"RED"]"RESET" Success\n");
    fflush(stdout);
}
ssize_t write(int fildes, const void *buf, size_t nbytes){
    fprintf(stderr, RED"["WHITE"HOOK"RED"] 'write'"RESET" info\nfd: %d\nbuffer address: %p\nbyte: %zu\n", fildes, buf, nbytes);

    char *modify_letter = (char*)malloc(nbytes);
    memcpy(modify_letter, buf, nbytes);

  for (size_t i = 0; i < nbytes; i++){
        if (modify_letter[i] == '1'){
            modify_letter[i] = '3'; 
        } else if (modify_letter[i] == '2'){ 
            modify_letter[i] = '1'; 
        } else if (modify_letter[i] == '3'){ 
            modify_letter[i] = '2'; 
        }
    }
    ssize_t bytes_w = realwrite(fildes, modify_letter, nbytes);
    free(modify_letter);
    return bytes_w;
}
