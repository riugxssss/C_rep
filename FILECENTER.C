#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

/*
 * PROGRAM OVERVIEW FROM RIUGXSS
 * This program is a simple file system management tool.
 * It provides a menu-driven interface to perform various operations like:
 * - Viewing the current working directory (PWD)
 * - Creating directories and files
 * - Reading the contents of directories and files
 * - Changing directories
 * - Appending text to files
 * - Removing files and directories
 * - Exiting the application
 *
 * USAGE:
 * - The menu displays a list of options. Each option corresponds to a specific operation.
 * - Enter the number corresponding to your desired operation.
 * - Follow the on-screen prompts to provide any additional input (e.g., file or directory names).
 * - The program handles errors and provides feedback for invalid inputs or unsuccessful operations.
 *
 * NOTES:
 * - This program assumes the user has appropriate permissions for the requested operations.
 * - Use valid file and directory names to avoid errors.
 * - To exit the program, choose option 10 from the menu.
 */

#define RED "\033[31m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

void pwd(){
    char buffer[50];
    char *cwd = getcwd(buffer, sizeof(buffer));
    if (cwd != NULL){
        printf(WHITE "Current directory:\n%s\n\n" RESET, cwd);
    } else {
        fprintf(stderr, WHITE "Failed to print the working directory\n" RESET);
        exit(EXIT_FAILURE);
    }
}
void mkdirr(const char *name, mode_t mode_dir){
    if (mkdir(name, mode_dir) == 0){
        printf(WHITE "Directory created\nPress enter to return\n" RESET);
        getchar();
    } else {
        fprintf(stderr, WHITE "Failed to create the directory\n" RESET);
        exit(EXIT_FAILURE);
    }
}
int readDir(DIR *dir, int counter, struct dirent *showsall){
    dir = opendir(".");
    if (dir == NULL){
        fprintf(stderr, WHITE "Failed to open the directory\n" RESET);
        return 1;
    }
    while ((showsall = readdir(dir)) != NULL){
        printf(WHITE "FIle N:%d\t%s\n" RESET, counter++, showsall->d_name);
    }
    putchar('\n');
    if (closedir(dir) == -1){
        fprintf(stderr, WHITE "Error closing the directory\n\n" RESET);
        return 1;
    }
    printf(WHITE "Press enter to return at the menu\n" RESET);
    getchar();
    return 0;
}
int mkfile(FILE *indir, const char *fileName){
    indir = fopen(fileName, "w+");
    if (indir == NULL){
        fprintf(stderr, WHITE "Error creating the file\n" RESET);
        return 1;
    }
    char contentOfFile[150];
    printf(WHITE "Write something in your file!\n" RESET);
    fgets(contentOfFile, sizeof(contentOfFile), stdin);

    size_t filewrite = fwrite(contentOfFile, 1, strlen(contentOfFile), indir);
    if (filewrite != strlen(contentOfFile)){
        fprintf(stderr, WHITE "Error writing in the file\n" RESET);
        fclose(indir);
        return 1;
    }
    fclose(indir);
    printf(WHITE "File writed and saved with success!\nPress enter to return at the menu\n" RESET);
    getchar();
}
void readfile(FILE *indir, const char *pathToRead){
    indir = fopen(pathToRead, "r+");
    if (indir == NULL){
        fprintf(stderr, WHITE "Error opening the file\n" RESET);
        exit(EXIT_FAILURE);
    }
    char bufferForRead[4096];

    size_t file_read = fread(bufferForRead, 1, sizeof(bufferForRead), indir);
    if (file_read != sizeof(bufferForRead)){
        fprintf(stderr, WHITE "Error reading the file\n" RESET);
        fclose(indir);
    }
    printf(WHITE "Content of file: \n%s" RESET, bufferForRead);
}
int change_dir(const char *chd){
    if (chdir(chd) == 0){
        printf(WHITE "Directory change with success!\n" RESET);
    } else {
        fprintf(stderr, WHITE "Failed to change the directory\n" RESET);
        return 1;
    }
    return 0;
}
void append_file(FILE *indir, const char *bufferToAppend, char *filename){
    indir = fopen(filename, "a");
    if (indir == NULL){
        fprintf(stderr, WHITE "Failed open the file\n" RESET);
        exit(EXIT_FAILURE);
    }

    size_t appendAfile = fwrite(bufferToAppend, 1 ,strlen(bufferToAppend), indir);
    if (appendAfile != strlen(bufferToAppend)){
        fprintf(stderr, WHITE "Error appending the text to the file\n" RESET);
        fclose(indir);
        exit(EXIT_FAILURE);
    }
    fclose(indir);
    printf(WHITE "Text writed with success\n" RESET);
}
int rmfile(const char *file_remove){
    if (remove(file_remove) == 0){
        printf(WHITE "File removed with success\n" RESET);
    } else {
        fprintf(stderr, WHITE "Error removing the file\n" RESET);
        return 1;
    }
    return 0;
}
int rmAdir(const char *directoryto_remove){
    if (rmdir(directoryto_remove) == 0){
        printf(WHITE "Directory removed\n" RESET);
    } else {
        fprintf(stderr, WHITE "Failed to remove the directory\n" RESET);
        return 1;
    }
    return 0;
}
int main(){
    DIR *directory;
    FILE *file_use;
    struct dirent *showfile;
    int count = 1;
    int userChoice = 0;
    char Ignore_num[50];

    while(userChoice != 10){
        printf(WHITE "1" RED ") " WHITE "PWD\n"
               WHITE "2" RED ") " WHITE "MKDIR\n"
               WHITE "3" RED ") " WHITE "READDIR\n"
               WHITE "4" RED ") " WHITE "MKFILE\n"
               WHITE "5" RED ") " WHITE "READFILE\n"
               WHITE "6" RED ") " WHITE "CHDIR\n"
               WHITE "7" RED ") " WHITE "APPEND\n"
               WHITE "8" RED ") " WHITE "RMFILE\n"
               WHITE "9" RED ") " WHITE "RMDIR\n"
               WHITE "10" RED ") " WHITE "EXIT\n\n" RESET);
        if (fgets(Ignore_num, sizeof(Ignore_num), stdin)){
            if (!sscanf(Ignore_num, "%d", &userChoice) == 1){
                printf(WHITE "\nONLY NUMBER ALLOWED\n" RESET);
                exit(EXIT_FAILURE);
            }
        }
        switch (userChoice)
        {
        case 1:
            pwd();
            break;
        case 2:
            char directoryUser[75];
            mode_t mode;
            printf(WHITE "Choose a name for your directory: " RESET);
            scanf("%74s", directoryUser);
            mkdirr(directoryUser, 0755);
            break;
        case 3:
            readDir(directory, count, showfile);
            break;
        case 4:
            char nameForFile[100];
            printf(WHITE "Choose a name for the file: " RESET);
            scanf("%99s", nameForFile);
            getchar();
            mkfile(file_use, nameForFile);
            break;
        case 5:
            char path_directory[100];
            printf(WHITE "Enter the file name (or the path): " RESET);
            scanf("%99s", path_directory);
            readfile(file_use, path_directory);
            break;
        case 6:
            char chd[50];
            printf(WHITE "Enter the path: (/path/to/dir): " RESET);
            scanf("%49s", chd);
            change_dir(chd);
            break;
        case 7:
            char filetoappend[100];
            printf(WHITE "Enter the name of your file: " RESET);
            scanf("%99s", filetoappend);
            getchar();

            char Text_Cont[4096];

            printf(WHITE "Enter a text to append: \n\n" RESET);
            fgets(Text_Cont, sizeof(Text_Cont), stdin);

            append_file(file_use, Text_Cont, filetoappend);
        break;
        case 8:
            char rmthefile[100];
            printf(WHITE "Enter the file name to remove: " RESET);
            scanf("%99s", rmthefile);
            getchar();
            rmfile(rmthefile);
            break;
        case 9:
            char rmthedir[100];
            printf(WHITE "Enter the directory you want to remove: " RESET);
            scanf("%99s", rmthedir);
            getchar();
            rmAdir(rmthedir);
            break;
        case 10:
            printf(WHITE "Thank you for using the system gestion by riugxss\n" RESET);
            exit(EXIT_SUCCESS);
            break;
        default:
            printf(WHITE "Invalid option\n\n" RESET);
            break;
        }
    }

    return 0;
}
