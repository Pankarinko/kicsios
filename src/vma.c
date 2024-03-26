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
    for (usize *copy_root = page; copy_root < (usize*)((usize)page + PAGESIZE); copy_root++) {
        *copy_root = 0;
    }
}

#define T 1
#define P 0

void map_page(usize va) {
    ptetype page_addr = (ptetype) ROUNDDOWN_PAGE(va);
    ptetype current_page_table = root_page_table;

    for (uint8 lev = LEVELS - 1; lev > 0 ; lev++) {
        ptetype tmp_page_addr = (page_addr >> ((lev + 1) * VPNSIZE)) & (MAXPTE << PTE_LOG);
        ptetype pte = (*((usize*)(current_page_table + tmp_page_addr)));
        
        if (!(pte & VALID)) {
            p_alloc(current_page_table, T);
        }
        // TODO set current_page_table
    }
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
