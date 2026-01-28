#pragma once

typedef struct Log_info log_info;
void error_handler(int handle_code);
void logging_function(int MRUvalue, int LRUvalue);
inline void clear_stdin(){
    while (getchar() != '\n' && getchar() != EOF);
}
