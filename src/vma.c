#include "vma.h"
#include "kstd.h"


void set_root_page_table(void) {
    usize root_page_table = SET_ROOT;
    print_hex((usize) endkernel);
    println("");
    print_hex(root_page_table);
    asm ("csrrw zero, satp, %0"
          :
          : "r" (root_page_table));
}



