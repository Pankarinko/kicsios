#include "vma.h"
#include "kstd.h"
#include "alloc.h"

// Address of the root page table
usize *root_page_table;
/* The frist free physical page
Caution! It contains the PPN not the whole physical address (physical_address >> 12)
*/
usize *first_free_ppn;

int initialize_vm() {
    set_root_page_table_bare();
    createfreelist();
    map_kernel();
    setmode();
}

// Used for initializing the mapping
void set_root_page_table_bare(void) {
    usize root_page_table = ROOT_PAGE_TABLE;
    usize set_satp = SET_ROOT_BARE;
    asm ("csrrw zero, satp, %0"
        :
        : "r" (set_satp));
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

// Mapping the whole physical address space from 0x8000
// This has to be done in BARE mode
void map_tables() {
    ptetype *pte = ROOT_PAGE_TABLE;
    usize page_table_address = ROOT_PAGE_TABLE + PAGESIZE;
    usize number_of_tables = (1 << VPNSIZE);
    for (usize level = 0; level < LEVELS - 1; level++) {
        for (usize i = 0; i < number_of_tables; i++) {
            /* TODO Not really satisfied with this part, because 
            it would be pretty useless to allocate the whole memory 
            only for page tables

            However, I will deal with this later. Now I will just assume that the RAM space is sufficient
            */
            if (page_table_address + PAGESIZE <= MEMORYSIZE) {
            // TODO something on error
            }
            *pte = (ptetype) ((page_table_address >> 12) << 2) | GLOBAL | VALID;
            page_table_address += PAGESIZE;
            pte += 1;
        }
        number_of_tables *= number_of_tables;
    }
    first_free_ppn = page_table_address >> 12;
}

// This function should only be called AFTER map_tables()
void map_page(usize va) {
    usize *address = ROOT_PAGE_TABLE;
    usize pt_index = 0;
    for (usize level = LEVELS; level > 1; level--) {
        pt_index = ((ADRESS_MASK & va) >> (level)) & (MAXPTE << PTE_LOG); 
        usize *address = *(usize*) (address + pt_index); //This still needs shifting somebits
    }
    *(ptetype*) address = va | READ | WRITE | EXECUTE | VALID | GLOBAL; 
}

// This is right now an identity function but who knows what happens later
usize translate_address(usize va) {
    return va;
}

/*void map_page(usize va) {
    ptetype page_addr = (ptetype) ROUNDDOWN_PAGE(va);
    ptetype current_page_table = root_page_table;

    for (uint8 lev = LEVELS - 1; lev > 0 ; lev++) {
        ptetype tmp_page_addr = (page_addr >> ((lev + 1) * VPNSIZE)) & (MAXPTE << PTE_LOG);
        ptetype pte = *(usize*)(current_page_table + tmp_page_addr);
        
        if (!(pte & VALID)) {
            pte = p_alloc(T);
            *(usize*)(current_page_table + tmp_page_addr) = pte;
        }
        current_page_table = pte ;
    }
}*/

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
