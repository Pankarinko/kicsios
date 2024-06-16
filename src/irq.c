#include "kstd.h"

void trap_vector();

void print_interrupt_addr(usize intaddr) {
    prints("at address ");
    print_hex(intaddr);
    println("");
    }

void irq_handler(void) {
    usize cause = 0;
    usize intaddr = 0;
    asm("csrrs %0, mcause, zero"
        : "=r" (cause));
    asm("csrrs %0, mepc, zero"
        : "=r" (intaddr));
    print_interrupt_addr(intaddr);
    if ((cause >> (ARCHSIZE - 1)) == 1) {
        cause = (cause << 1) >> 1;
        switch (cause) {
            case 0 ... 3:
                println("SOFTWARE INTERRUPT");
                print_interrupt_addr(intaddr);
                while (1);
            case 4 ... 7:
                println("TIMER INTERRUPT");
                print_interrupt_addr(intaddr);
                while (1);
            case 8 ... 11:
                println("EXTERNAL INTERRUPT");
                print_interrupt_addr(intaddr);
                while (1);
            default: 
                println("UNKNOWN INTERRUPT");
                print_interrupt_addr(intaddr);
                while (1); 
        }
    } else {
    cause = (cause << 1) >> 1;
        switch (cause) {
            case 0:
            case 1: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Running this instruction is not possible");
                while (1);
            case 2: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Illegal instruction");
                while (1);
            case 3: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Breakpoint");
                while (1);
            case 4:
            case 5: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Loading from this address is not possible");
                while (1);
            case 6:
            case 7: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Storing data to address is not possible");
                while (1);
            case 8:
            case 9:
            case 11: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Environment call");
                while (1);
            case 12:
            case 13:
            case 15: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Page fault");
                while (1);
            default: 
                println("KERNEL PANIC");
                print_interrupt_addr(intaddr);
                println("Unknown reason");
                while (1); 
        }
    }
}

void set_irq(void) {
    void (*irq_addr)(void) = &trap_vector;
    asm("csrrw zero, mtvec, %0"
        : 
        : "r" (irq_addr));
}
