#include "registers_utils.h"
#include <stdio.h>
#include <stdint.h>

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define ENDIAN_SYSTEM 1 //Little
#else
    #define ENDIAN_SYSTEM 0 //Big
#endif

#define RED "\033[1;31m"
#define RESET "\033[0m"

#define bit8 8
#define bit16 16
#define bit32 32


typedef struct {
    union {
        uint8_t modifyal;
    #if LITTLE_ENDIAN_SYSTEM //if little endian follow an order (portable on various system)
        struct { 
            uint8_t enable : 1;
            uint8_t ready  : 1;
            uint8_t mode   : 2;
            uint8_t flag   : 1;
            uint8_t res    : 3;
        } bitaccess8;
    #else //big endian reverse follow the: 1234 rule little endian: 4321 first the LSB
        struct {
            uint8_t res    : 3;
            uint8_t flag   : 1;
            uint8_t mode   : 2;
            uint8_t ready  : 1;
            uint8_t enable : 1;
        } bitaccess8;
    #endif
    } al;

    union {
        uint16_t modifyax;
    #if ENDIAN_SYSTEM
        struct {
            uint16_t enable : 2;
            uint16_t ready  : 2;
            uint16_t mode   : 4;
            uint16_t error  : 2;
            uint16_t irq    : 1;
            uint16_t flag   : 1;
            uint16_t status : 4;
        } bitaccess16;
    #else
        struct {
            uint16_t status : 4;
            uint16_t flag   : 1;
            uint16_t irq    : 1;
            uint16_t error  : 2;
            uint16_t mode   : 4;
            uint16_t ready  : 2;
            uint16_t enable : 2;
        } bitaccess16;
    #endif
    } ax;

    union {
        uint32_t modifyeax;
    #if ENDIAN_SYSTEM
        struct {
            uint32_t enable : 4;
            uint32_t ready  : 4;
            uint32_t mode   : 8;
            uint32_t error  : 4;
            uint32_t irq    : 1;
            uint32_t flag   : 1;
            uint32_t status : 8;
            uint32_t res    : 2;
        } bitaccess32;
    #else
        struct {
            uint32_t res    : 2;
            uint32_t status : 8;
            uint32_t flag   : 1;
            uint32_t irq    : 1;
            uint32_t error  : 4;
            uint32_t mode   : 8;
            uint32_t ready  : 4;
            uint32_t enable : 4;
        } bitaccess32;
    #endif
    } eax;

} Registers;

//Function to reveal the order in run. 

void print_endian(void){
    #if ENDIAN_SYSTEM
    printf("COMPILE-TIME: Little-endian system\n");
    #else
    printf("COMPILE-TIME: Big-endian system\n");
    #endif
}

int main(void) {
    Registers instance;
    
    print_endian();

    printf(RED"START\n" RESET);

    // <8 BIT>
    instance.al.bitaccess8.res = 7;
    set_bit(&instance.al.modifyal, 0);
    printf("[8-BIT] = ");
    print_registers(instance.al.modifyal, bit8);

    // <16 BIT>
    instance.ax.bitaccess16.enable = 3;
    clear_bit(&instance.ax.modifyax, 0);
    printf("[16-BIT] = ");
    print_registers(instance.ax.modifyax, bit16);

    // <32 BIT>
    instance.eax.bitaccess32.status = 0x80;
    toggle_bit(&instance.eax.modifyeax, 0);
    printf("[32-BIT] = ");
    print_registers(instance.eax.modifyeax, bit32);

    printf(RED"END\n" RESET);
    return 0;
}
