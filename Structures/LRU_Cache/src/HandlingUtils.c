#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

#define LOG_FILE "loggingfile.txt"

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct LogInfo {
    FILE *file;      // File pointer
    int mru_value;   // Most Recently Used value
    int lru_value;   // Least Recently Used value
} LogInfo;

/*This error handler only print the code value and
the error, the value handled manually*/
void error_handler(int error_code){
    printf("Error code value -> %d\n", error_code);
    printf("Error message -> %s\n", strerror(error_code));
    exit(EXIT_FAILURE);
}

/*Timestamp function called by logging function where 
is thread-safe from concurrency (mutex) that stamp the 
the local time with data, creating a file (FILE ptr declared in the struct) that pass the
MRU and the LRU value and print into the file (fflush used to force the output because std c library
are canon-buffered)*/
static void *timestamp_function(void *args){
    LogInfo *log_data = (LogInfo *)args;
    pid_t thread_id = syscall(SYS_gettid);
    char timestamp[100];

    pthread_mutex_lock(&log_mutex);

    time_t now;
    time(&now);
    struct tm *local_time = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%X", local_time);

    int fprintf_result = fprintf(log_data->file, "[%s][tid:%d] MRU: %d | LRU: %d\n",
                                 timestamp, thread_id, log_data->mru_value, log_data->lru_value);

    if (fprintf_result == -1){
        pthread_mutex_unlock(&log_mutex);
        error_handler(fprintf_result);
    }

    fflush(log_data->file); // Ensure the output is written immediately
    pthread_mutex_unlock(&log_mutex);

    return NULL;
}

/*Its used a FILE ptr with the 'a' prefix that means append
and a log counter for the LOG STAMP thus an user can log whenever he wants
the MRU and LRU of the cache*/
void logging_function(int MRUvalue, int LRUvalue){
    FILE *log_fp = fopen(LOG_FILE, "a");
    if (!log_fp){
        perror("Error opening log file");
        return;
    }

    static int log_counter = 1;
    fprintf(log_fp, "<LOG STAMP N:%d>\n", log_counter);

    LogInfo log_data;
    pthread_t log_thread;

    log_data.file = log_fp;
    log_data.mru_value = MRUvalue;
    log_data.lru_value = LRUvalue;

    int thread_result = pthread_create(&log_thread, NULL, timestamp_function, &log_data);
    if (thread_result != 0){
        error_handler(thread_result);
    }

    pthread_join(log_thread, NULL);
    fclose(log_fp);
    log_counter++;
}
