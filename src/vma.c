#include "vma.h"
#include "kstd.h"
#include "alloc.h"

usize *root_page_table;

int initialize_vm() {
    set_root_page_table_bare();
    createfreelist();
    map_kernel();
    setmode();
}

// Used for initializing the mapping
void set_root_page_table_bare(void) {
    usize root_page_table = ROOT_PAGE_TABLE;
    // TODO recursion
    usize set_satp = SET_ROOT_BARE;
    asm ("csrrw zero, satp, %0"
        :
        : "r" (root_page_table));
     zero_page(root_page_table);
}

// Should only be called after the kernel is mapped
void setmode(void) {
    usize set_satp = SET_ROOT;
    asm ("csrrw zero, satp, %0"
        :
        : "r" (root_page_table));
}

void zero_page(usize *page) {
    for (usize *copy_root = page; copy_root < page + (PAGESIZE / sizeof(pte)); copy_root++) {
        *copy_root = 0;
    }
}

#define 1 T
#define 0 P

void map_page(usize va) {
    usize page_beginning = ROUNDDOWN_PAGE(va);
    ptetype *t_addr = ~(PAGESIZE - 1);
    for (uint8 lev = 0; lev < LEVELS - 1; lev++) {
      t_addr =(usize) t_addr << (lev * VPNSIZE) | (va >> (12 + (LEVELS - 1 -lev) * VPNSIZE)) << PTE_LOG;
      if (!(*t_addr & VALID)) {
        p_alloc(t_addr, T);
      }
    }
     p_alloc(t_addr, P);
}

void map_kernel() {
    usize kernel_pages = ROUNDDOWN_PAGE(endkernel) - ROUNDDOWN_PAGE(startkernel);
    for (usize i = 0; i < kernel_pages; i++) {
        map_page((usize) (ROUNDDOWN_PAGE(startkernel) + (i * PAGESIZE)));
    }
}

int unmap_page(usize va) {
    ptetype *p_addr =( ~(PAGESIZE - 1) << ( VPNSIZE * (LEVELS - 1))) | ((va >> PAGESIZE) << PTE_LOG);
    zero_page(&va);
   *p_addr &= (!VALID);
    pfree(va,((usize)p_addr &  ~(PAGESIZE - 1)));
}
