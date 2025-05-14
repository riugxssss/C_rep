#include <stdint.h>
#include "registers_utils.h"
#include <stdio.h>


typedef union{
    uint16_t ax;
    struct{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

        uint16_t opcode : 4; // LSB
        uint16_t reg_id : 4;
        uint16_t flags : 3;
        uint16_t reserved : 1;
        uint16_t value : 4; // MSB
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        uint16_t value : 4; // MSB
        uint16_t reserved : 1;
        uint16_t flags : 3;
        uint16_t reg_id : 4;
        uint16_t opcode : 4; //LSB
#else
#error "Endian not implemented"
#endif
    }bitaccess;

}AXRegister;

int main(void){
    
    printf("START: \n");
    AXRegister instancereg;
    instancereg.ax = 0x0;
    set_bit(&instancereg.ax, 0);
    print_registers(instancereg.ax);
    instancereg.bitaccess.opcode = 0xf;
    print_registers(instancereg.ax);
    set_bit(&instancereg.ax, 15);
    toggle_bit(&instancereg.ax, 7);
    instancereg.bitaccess.reserved = 0x1;
    print_registers(instancereg.ax);
    clear_bit(&instancereg.ax, 7);
    set_bit(&instancereg.ax, 12);
    int cont = read_bit(instancereg.ax, 14);
    printf("The bit at position %d is setted to %d\n", 14, cont);
    print_registers(instancereg.ax);
    printf("END\n");
 return 0; 
}
