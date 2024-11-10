#include "kstd.h"
#include "vma.h"
#include "timer.h"

void set_irq();

void terminate(void) {
    volatile int *addr = (int*) 0x100000;
    *addr = 0x5555;
}

void c_entry(void) {
    //initialize_vm();
    printu(5);
    set_irq();
    printu(get_time());
    for (int i = 0; i < 200; i++) {
        printu(get_time());
        println("");
    }
    terminate();
}