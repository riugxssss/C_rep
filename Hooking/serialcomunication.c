#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef CRTSCTS
#define CRTSCTS 020000000000
#endif

#define chardevice "/dev/ttyACM0"

void fatal(const char *error){
    fprintf(stderr, "<%s>", error);
    abort();
}

int main(void){
    int serialport = open(chardevice, O_RDWR | O_NOCTTY, O_SYNC);
    if (serialport < 0){
        fatal("open");
    }

    struct termios tty;

    if (tcgetattr(serialport, &tty) != 0){
        fatal("confport");
    }

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);


    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);    
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); 

    tty.c_oflag &= ~ONLCR; 
    tty.c_oflag &= ~OPOST;  

    tty.c_cc[VMIN] = 0;   
    tty.c_cc[VTIME] = 5; 

    if (tcsetattr(serialport, TCSANOW, &tty) != 0){
        fatal("setport");
        close(serialport);
    }
    printf("Connection to %s Press q to exit\n", chardevice);
    printf("--- Start communication ---\n");
    char buffer[256];
    char input_char;
    int n_read = 0;
    struct termios old_stdin_tty, new_stdin_tty;
    tcgetattr(STDIN_FILENO, &old_stdin_tty); 
    new_stdin_tty = old_stdin_tty;
    new_stdin_tty.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &new_stdin_tty); 

    while (1){
        input_char = 0; 
            if (read(STDIN_FILENO, &input_char, 1) > 0) {
                if (input_char == 'q' || input_char == 'Q') {
                    printf("\033[1;31mexiting\n");
                    break; 
            }
            if (write(serialport, &input_char, 1) < 0) {
                perror("<error write in port serial>\n");
                break;
            }
            printf("\033[1;37mSent: '%c'\n", input_char);
        }

        n_read = read(serialport, buffer, sizeof(buffer) - 1);
        if (n_read > 0) {
            buffer[n_read] = '\0';
            printf("\033[1;37mRecv: %s", buffer); 
            fflush(stdout); 
        } else if (n_read < 0) {
            perror("<error read in port serial>\n");
            break;
        }

        usleep(10000); 
    
    } 
    tcsetattr(STDIN_FILENO, TCSANOW, &old_stdin_tty);
    close(serialport);
    
    return 0;

}
