#include "vma.h"
#include "kstd.h"
#include "alloc.h"

usize *root_page_table;

int initialize_vm() {
    set_root_page_table_init();
    createfreelist();
    map_kernel();
    set_root_page_table();
}

void set_root_page_table_init(void) {
    usize root_page_table = ROOT_PAGE_TABLE;
    // TODO recursion
    usize set_satp = SET_ROOT_INIT;
    asm ("csrrw zero, satp, %0"
        :
        : "r" (root_page_table));
     zero_page(root_page_table);
}

void set_root_page_table(void) {
    usize set_satp = SET_ROOT;
    asm ("csrrw zero, satp, %0"
        :
        : "r" (root_page_table));
}

void zero_page(usize *page) {
    for (usize *copy_root = page; copy_root < page + (PAGESIZE / sizeof(ptetype)); copy_root++) {
        *copy_root = 0;
    }
}

void map_kernel() {
    usize kernel_pages = ROUNDDOWN_PAGE(endkernel) - ROUNDDOWN_PAGE(startkernel);
    if (kernel_pages % PAGESIZE) {
    } else {
        kernel_pages = kernel_pages / PAGESIZE + 1;
    }
    for (usize i = 0; i < kernel_pages; i++) {
        map_page((usize) (ROUNDDOWN_PAGE(startkernel) + (i * PAGESIZE)));
    }
}
void map_page(usize va) {
    ptetype *t_addr = ~(PAGESIZE - 1);
    for (uint8 lev = 0; lev < LEVELS - 1; lev++) {
      t_addr =(usize) t_addr << (lev * VPNSIZE) | (va >> (12 + (LEVELS - 1 -lev) * VPNSIZE)) << PTE_LOG;
      if (!(*t_addr & VALID)) {
        talloc(t_addr); // TODO function to set pte bits
      }
    }
    palloc(va);

}


int unmap_page(usize va) {
    ptetype *p_addr =( ~(PAGESIZE - 1) << ( VPNSIZE * (LEVELS - 1))) | ((va >> PAGESIZE) << PTE_LOG);
    zero_page(&va);
   *p_addr &= (!VALID);
    pfree(va,((usize)p_addr &  ~(PAGESIZE - 1)));
}
