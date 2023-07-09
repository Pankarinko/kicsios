#include "src/kstd.h"

void output_UART(void) {
    volatile uint8 *base = (uint8*) 0x10000000;
    uint8 init = 3;
    *(base + 3) = init;
    *base = 'a';
}


void c_entry(void) {
    volatile int *addr = (int*) 0x100000;
    output_UART();
    *addr = 0x5555;
}

