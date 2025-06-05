#include <stdio.h>

//Print the register copy left shift ( / 2 ) if & 1u = 1 else 0

void print_registers(int reg, int totbit){
    for (int i = totbit - 1;i>= 0;i--){
        printf("%d", (reg >> i) & 1u);
        if (i % 8 == 0){ //spacing by 8 
            putchar(' ');
        }
    }
    putchar('\n');
}

