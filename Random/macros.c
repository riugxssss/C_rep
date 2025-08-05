#include <stdio.h>
#include <stdlib.h>
#define MACROTEST(t) _Generic((t), \
    int: "int", \
    float: "float", \
    double: "double", \
    default: "other type")
#define NAME(x) #x
int main(void) {
    
    int test = 5;
    printf("Type of var named '%s' --> %s\n", NAME(test), MACROTEST(test));
    typeof(test) secvar = 23;
    printf("Type of var named '%s', --> %s\n", NAME(secvar), MACROTEST(secvar));
    
    return 0;
}
