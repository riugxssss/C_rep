#ifndef REGISTERS_UTILS_H
#define REGISTERS_UTILS_H
#include <stdint.h>
#include <assert.h>

static inline uint8_t set_bit8(uint8_t *reg, uint8_t bit){
    assert(bit < 8);
    return *reg |= (uint8_t)(1U << bit);
}
static inline uint16_t set_bit16(uint16_t *reg, uint16_t bit){
    assert(bit < 16);
    return *reg |= (uint16_t)(1U << bit);
}
static inline uint32_t set_bit32(uint32_t *reg, uint32_t bit){
    assert(bit < 32);
    return *reg |= (uint32_t)(1UL << bit);
}

//MACRO using Generic func to reveal the type inserted

#define set_bit(reg, bit) _Generic(*(reg), \
uint8_t: set_bit8, \
uint16_t: set_bit16, \
uint32_t: set_bit32 \
)((reg), (bit) )

static inline uint8_t toggle_bit8(uint8_t *reg, uint8_t bit){
        assert(bit < 8);
        return *reg ^= (uint8_t)(1U << bit);
        }
 static inline uint16_t toggle_bit16(uint16_t *reg, uint16_t bit){
        assert(bit < 16);
        return *reg ^= (uint16_t)(1U << bit);
        }
static inline uint32_t toggle_bit32(uint32_t *reg, uint32_t bit){
        assert(bit < 32);
        return *reg ^= (uint32_t)(1UL << bit);
        }

//.

#define toggle_bit(reg, bit) _Generic(*(reg), \
uint8_t: toggle_bit8, \
uint16_t: toggle_bit16, \
uint32_t: toggle_bit32 \
)( (reg), (bit) )

static inline uint8_t clear_bit8(uint8_t *reg, uint8_t bit){
       assert(bit < 8);
       return *reg &= (uint8_t) ~(1U << bit);
    }
static inline uint16_t clear_bit16(uint16_t *reg, uint16_t bit){
        assert(bit < 16);
        return *reg &= (uint16_t) ~(1U << bit);
    }
 static inline uint32_t clear_bit32(uint32_t *reg, uint32_t bit){
        assert(bit < 32);
    return *reg &= (uint32_t) ~(1UL << bit);    
    }


//.

#define clear_bit(reg, bit) _Generic(*(reg), \
uint8_t: clear_bit8, \
uint16_t: clear_bit16, \
uint32_t: clear_bit32 \
)((reg), (bit))

static inline uint8_t read_bit8(uint8_t reg, uint8_t bit){
        assert(bit < 8);
        return (uint8_t)(reg >> bit) & 1U;
    }
static inline uint16_t read_bit16(uint16_t reg, uint16_t bit){
        assert(bit < 16);
        return (uint16_t)(reg >> bit) & 1U;
    }
static inline uint32_t read_bit32(uint32_t reg, uint32_t bit){
        assert(bit < 32);
        return (uint32_t)(reg >> bit) & 1UL;
    }

//.
#define read_bit(reg, bit) _Generic((reg), \
uint8_t: read_bit8, \
uint16_t: read_bit16, \
uint32_t: read_bit32 \
)((reg), (bit))

void print_registers(int reg, int totbit);

#endif
