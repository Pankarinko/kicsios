#include "kstd.h"
#include "vma.h"
#include "alloc.h"

void set_irq();

void terminate(void) {
    volatile int *addr = (int*) 0x100000;
    *addr = 0x5555;
}

void c_entry(void) {
    set_irq();
    //set_root_page_table();
    usize vpn = (1 << 22);
    int level = 1;
    vpn = (MAXADDRESS << 12 + LEVELS - level) | (vpn >> (level * VPNSIZE));
    print_hex(vpn);
    terminate();
}

