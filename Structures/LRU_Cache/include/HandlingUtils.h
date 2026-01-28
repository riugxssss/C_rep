#pragma once

//Logging struct
typedef struct Log_info log_info;

void error_handler(int handle_code);

void logging_function(int MRUvalue, int LRUvalue);

//Clear the input stream to avoid incorrent reading or some printf bug
inline void clear_stdin(){
    while (getchar() != '\n' && getchar() != EOF);
}

