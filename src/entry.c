#include "kstd.h"

void set_irq();

void terminate(void) {
    volatile int *addr = (int*) 0x100000;
    *addr = 0x5555;
}

void c_entry(void) {
    set_irq();
    int uwu = 0x12345;
     asm volatile("jalr 0(%0)" 
        :
        :"r" (uwu));
    terminate();
}

