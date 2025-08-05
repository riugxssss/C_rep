#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define MEM_SIZE 4096

int main() {
    int fd;
    char *str = "test.bin";
    int *r;
    
    fd = open(str, O_CREAT | O_RDWR, 0600);
    ftruncate(fd, MEM_SIZE),
    r = mmap(NULL, MEM_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    r[0] = 0xDEAD;
    uint32_t val = r[0];
    printf("0x%08x", val);
    munmap(r, MEM_SIZE);
    unlink(str);

    return 0;
}
