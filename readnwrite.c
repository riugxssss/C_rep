#include <stdio.h>
#include <string.h>

/*
[!] INFO

Example program to read a file in your system and write on another
file, view the file gestion project to implement some technique to use C with
POSIX libraries

by riugxss   


*/

int main(){

    FILE *test;

    test = fopen("negro.txt", "r");
    if (test == NULL){
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    char read_buffer[150];

    size_t read = fread(read_buffer, 1, sizeof(read_buffer), test);
    if (read != strlen(read_buffer)){
        fprintf(stderr, "Error reading the file\n");
        fclose(test);
        return 1;
    }

    fclose(test);

    test = fopen("test1.txt", "w+");
    if (test == NULL){
        fprintf(stderr, "Error with the file\n");
        return 1;
    }

    char buffer[200];

    snprintf(buffer, sizeof(buffer), read_buffer);

    size_t write = fwrite(buffer, 1, strlen(buffer), test);
    if (write != strlen(buffer)){
        fprintf(stderr, "Error writing the file\n");
        fclose(test);
        return 1;
    }

    fclose(test);

    printf("File saved and texted\n");


    return 0;
}
