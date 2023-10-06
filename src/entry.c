#include "kstd.h"

void set_irq();

void terminate(void) {
    volatile int *addr = (int*) 0x100000;
    *addr = 0x5555;
}

void c_entry(void) {
    set_irq();
    asm("ebreak");
    terminate();
}

