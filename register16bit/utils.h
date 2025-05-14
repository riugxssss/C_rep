#ifndef REGISTERS_UTILS_H
#define REGISTERS_UTILS_H
#include <stdint.h>

void set_bit(uint16_t *reg, int bit);
int read_bit(uint16_t reg, int bit);
void toggle_bit(uint16_t *reg, int bit);
void clear_bit(uint16_t *reg, int bit);
void print_registers(uint16_t reg);

#endif
