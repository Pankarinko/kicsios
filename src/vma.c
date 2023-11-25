#include "vma.h"
#include "kstd.h"
#include "alloc.h"


usize *root_page_table;

void set_root_page_table(void) {
    usize root_page_table = ROOT_PAGE_TABLE;
    usize set_satp = SET_ROOT;
    print_hex((usize) endkernel);
    println("");
    print_hex(root_page_table);
    asm ("csrrw zero, satp, %0"
          :
          : "r" (root_page_table));
}

//Initialize page tables with zeros
void initialize_vm(void) {
    initialize_page(root_page_table);´98432
    }
}

void initialize_page(usize *page) {
   for (usize *copy_root = page; copy_root < page + (PGAESIZE / sizeof(ptetype)); copy_root++) {
        *copy_root = 0;
   +p  }
}

int check_pte_validity(ptetype pte) {
  //TODO
}

void map_page(usize va, ptetype pte) {
      usize *current_pte;
      usize rootcopy = root_page_table;
      usize vacopy = va;
      for (int i = LEVELS - 1 ; i > 0; i--) {
        current_pte = rootcopy + (vacopy >> (12 + (LEVELS - i + 1);
      
        if (!(*current_pte & VALID)) {
            initialize_page();
         }
        
        //Delete first VPNSIZE bits
        vacopy = va;
        vacopy = (vacopy << VPNSIZE) << VPNSIZE;
      }
}

