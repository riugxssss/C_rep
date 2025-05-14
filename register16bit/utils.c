#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#define DIM 16
void set_bit(uint16_t *reg, int bit){
    assert(bit < DIM);
    *reg |= (uint16_t)(1u << bit);
}
int read_bit(uint16_t reg, int bit){
    assert(bit < DIM);
    return (uint16_t)(reg >> bit) & 1u;
}
void toggle_bit(uint16_t *reg, int bit){
    assert(bit < DIM);
    *reg ^= (uint16_t)(1u << bit);
}
void clear_bit(uint16_t *reg, int bit){
    assert(bit < DIM);
    *reg &=(uint16_t) ~(1u << bit);
}
void print_registers(uint16_t reg){
    for (int i = DIM - 1;i>= 0;i--){
        printf("%d", (reg >> i) & 1u);
        if (i % 8 == 0){
            putchar(' ');
        }
    }
    putchar('\n');
}

