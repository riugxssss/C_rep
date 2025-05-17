#include <stdio.h>

void print_registers(int reg, int totbit){
    for (int i = totbit - 1;i>= 0;i--){
        printf("%d", (reg >> i) & 1u);
        if (i % 8 == 0){
            putchar(' ');
        }
    }
    putchar('\n');
}

