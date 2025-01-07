/*
FILE MANAGEMENT WITH POSIX SYSTEM CALLS

This program allows you to perform basic file operations using POSIX system calls. It includes the following functionalities:

1. CREATE FILE: Allows the user to create a new file and write content into it.
2. READ FILE: Reads and displays the content of a file.
3. READ AND WRITE: Reads content from a file and writes it into another file specified by the user.
4. EXIT: Exits the program.

All outputs are color-coded for better readability:
- Keywords (e.g., errors) are displayed in RED.
- User prompts and other text are displayed in WHITE.

To use the program, follow the menu options displayed, and provide the necessary inputs when prompted.
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define WHITE "\033[1;37m"
#define RESET "\033[0m"
#define RED "\033[1;31m"

int make_file(char *buffer, size_t size_buff, char *filename){
    int fd = open(filename, O_CREAT | O_WRONLY, 0755);
    if (fd == -1 ){
        printf(RED "Error opening the file\n" RESET);
        return 1;
    }

    printf(WHITE "What you wanna write in your file? " RESET);
    if (fgets(buffer, size_buff, stdin) == NULL){
        printf(RED "Error reading the input\n" RESET);
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    ssize_t write_bytes = write(fd, buffer, strlen(buffer));
    if (write_bytes == -1 ){
        printf(RED "Error writing the file\n" RESET);
        return 1;
    }

    close(fd);
    printf(WHITE "File written and saved\n" RESET);

    return 0;
}

int read_file(char *filename, char *buffer, size_t buf){
    int fd = open(filename, O_RDONLY);
    if (fd == -1){
        printf(RED "Error opening the file\n" RESET);
        return 1;
    }

    ssize_t read_bytes = read(fd, buffer, buf);
    if (read_bytes == -1){
        printf(RED "Error reading the file\n" RESET);
        return 1;
    }

    close(fd);

    printf(WHITE "File content: \n%s\n" RESET, buffer);

    return 0;
}

int rdwr(const char *filename, char *buf, size_t SizeBuf){
    int fd = open(filename, O_RDONLY);
    if (fd == -1){
        printf(RED "Error opening the file\n" RESET);
        return 1;
    }

    ssize_t bytes_toread = read(fd, buf, SizeBuf);
    if (bytes_toread == -1){
        printf(RED "Error with the byte reading\n" RESET);
        return 1;
    }
    close(fd);

    char name[50];
    printf(WHITE "Enter the file you wanna write the read file into: " RESET);
    scanf("%s", name);

    fd = open(name, O_CREAT | O_WRONLY, 0755);
    if (fd == -1){
        printf(RED "Error opening the file\n" RESET);
        return 1;
    }

    char buff2[1000];
    snprintf(buff2, sizeof(buff2), buf);

    ssize_t bytes_towrite = write(fd, buff2, strlen(buff2));
    if (bytes_towrite == -1){
        printf(RED "Error writing\n" RESET);
        return 1;
    }

    close(fd);

    printf(WHITE "File read, written, and saved\n" RESET);

    return 0;
}

int main(){
    int choiceMenu;
    printf(RED "FILE GESTION" WHITE " WITH POSIX by riugxss\n\n" RESET);
    char num[30];

    while(true){
        printf(WHITE "" WHITE "1" RED ") " WHITE "MAKE FILE\n" WHITE "2" RED ") " WHITE "READ FILE\n" WHITE "3" RED ") " WHITE "READ AND WRITE\n" WHITE "4" RED ") " WHITE "EXIT\n\n" RESET);
        if (fgets(num, sizeof(num), stdin) != NULL){
            if (sscanf(num, "%d", &choiceMenu) != 1){
                printf(RED "ONLY NUMBERS ALLOWED!\n" RESET);
                return 1;
            }
        }

        switch (choiceMenu) {
        case 1: {
            char filename[256];
            char buffer[1000];
            printf(WHITE "Enter a file name: " RESET);
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            if (make_file(buffer, sizeof(buffer), filename) != 0){
                printf(RED "Error writing the file\n" RESET);
            }
            break;
        }
        case 2: {
            char filenames[256];
            char buffers[1000] = "";
            printf(WHITE "Enter the file name to read: " RESET);
            if (fgets(filenames, sizeof(filenames), stdin) == NULL){
                printf(RED "Error getting the input\n" RESET);
                return 1;
            }
            filenames[strcspn(filenames, "\n")] = '\0';
            if (read_file(filenames, buffers, sizeof(buffers)) != 0){
                printf(RED "Error reading the file\n" RESET);
            }
            break;
        }
        case 3: {
            char file[256];
            char buf[1000] = "";
            printf(WHITE "Enter the file name to read: " RESET);
            if (fgets(file, sizeof(file), stdin) == NULL){
                printf(RED "Error getting the input\n" RESET);
                return 1;
            }
            file[strcspn(file, "\n")] = '\0';

            if (rdwr(file, buf, sizeof(buf)) != 0){
                printf(RED "Error with the function\n" RESET);  
            }
            getchar();
            break;
        }
        case 4:
            printf(WHITE "Bye bye!!\n" RESET);
            exit(EXIT_SUCCESS);
        default:
            printf(RED "\nInvalid option selected\n" RESET);
            break;
        }
    }

    return 0;
}
