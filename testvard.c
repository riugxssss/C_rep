#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...){
    va_list args;
    va_start(args, count);
    int tot = 0;
    for (int i = 0;i<count;i++){
        tot += va_arg(args, int);
    }
    va_end(args);
    return tot;
}
int main(void){
    

        
    return 0;
}
