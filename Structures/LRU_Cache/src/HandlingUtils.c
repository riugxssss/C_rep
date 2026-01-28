#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

#define LOGGINFILE "loggingfile.txt"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct Log_info {
    FILE *FILEhandler;
    int MRUval;
    int LRUval;
}log_info;

void error_handler(int handle_code){
    printf("Error code value -> %d\n", handle_code);
    printf("Error message -> %s\n", strerror(handle_code));
    exit(EXIT_FAILURE);
}

static void *timestamp_function(void *args){
    log_info *ptr = (log_info *)args;
    pid_t tid = syscall(SYS_gettid);
    char BufTime[100];
    pthread_mutex_lock(&mutex);
    time_t raw;
    time(&raw);
    struct tm *times = localtime(&raw);
    strftime(BufTime, sizeof(BufTime), "%X", times);
    int OutRetCode = fprintf(ptr->FILEhandler,"[%s][tid:%d]MRU: %d | LRU: %d\n", BufTime, tid, 
    ptr->MRUval, ptr->LRUval);
    if (OutRetCode == -1){
        pthread_mutex_unlock(&mutex);
        error_handler(OutRetCode);
    }
    fflush(ptr->FILEhandler); //We use fflush due buffering of Standard C functions causing UB when writing in the file
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void logging_function(int MRUvalue, int LRUvalue){
    FILE *ptr = fopen(LOGGINFILE, "a");
    if (!ptr){
        perror("Error");
    }
    static int CallCounter = 1;
    fprintf(ptr, "<LOG STAMP N:%d>\n", CallCounter);

    log_info structptr; 
    pthread_t pthread_arr;

    structptr.FILEhandler = ptr;
    structptr.LRUval = LRUvalue;
    structptr.MRUval = MRUvalue;

    int retcode = pthread_create(&pthread_arr, NULL, timestamp_function, &structptr);
    if (retcode != 0){
        error_handler(retcode);
    }
    pthread_join(pthread_arr, NULL);
    fclose(ptr);
    CallCounter++;
}
