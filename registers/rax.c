#include "registers_utils.h"
#include <stdio.h>
#include <stdint.h>

typedef struct{
    union{
        uint8_t modifyal;
        struct{
            uint8_t enable : 1;
            uint8_t ready : 1;
            uint8_t mode : 2;
            uint8_t flag : 1;
            uint8_t res : 3;
        }bitaccess8;      
    }al;
    union{
        uint16_t modifyax;
        struct{
            uint16_t enable : 2;
            uint16_t ready : 2;
            uint16_t mode : 4;
            uint16_t error : 2;
            uint16_t irq : 1;
            uint16_t flag : 1;
            uint16_t status : 4;
        }bitaccess16;
    }ax;
    union{
        uint32_t modifyeax;
        struct{
            uint32_t enable : 4;
            uint32_t ready : 4;
            uint32_t mode : 8;
            uint32_t error : 4;
            uint32_t irq : 1;
            uint32_t flag : 1;
            uint32_t status : 8;
            uint32_t res : 2;
        }bitaccess32;
    }eax;
}Registers;
int main(void){
    
    const int bit8 = 8;
    const int bit16 = 16;
    const int bit32 = 32;
    Registers instance;

    printf("START\n");
    // <8 BIT>
    instance.al.bitaccess8.res = 7;
    set_bit(&instance.al.modifyal, 0);
    print_registers(instance.al.modifyal, bit8);
    // <16 BIT>
    instance.ax.bitaccess16.enable = 3;
    clear_bit(&instance.ax.modifyax,0);
    print_registers(instance.ax.modifyax, bit16);
    // <32 BIT>
    instance.eax.bitaccess32.status =  0x80;
    toggle_bit(&instance.eax.modifyeax, 0);
    print_registers(instance.eax.modifyeax, bit32);
   
    printf("END\n");
    return 0;
}
