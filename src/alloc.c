#include "vma.h"
#include "kstd.h"
#include "alloc.h"

// TODO optimize with expandable freelist to reach 34 bit physical addresses

// TODO global lock
// this is the Page Frame Number (22 bits for 32 bit etc.)
usize firstfree;

// For this method, we need to set satp_mode to BARE
void createfreelist(void) {
    firstfree = (ROOT_PAGE_TABLE) >> PAGE_LOG;
    usize i;
    for (i = ROOT_PAGE_TABLE; i < MEMORYSTART + MEMORYSIZE - PAGESIZE; i += PAGESIZE ) { 
            *(usize*) i = (i + PAGESIZE) >> PAGE_LOG;
    }
    *(usize*) i = NO_NEXT_FREE_PAGE;
} 


//Following methods are for satp_mode SVXX
usize p_alloc(usize table) {
    usize vpn;
    if (table) {
        usize vpn = ((firstfree << FLAG_BITS) | VALID | GLOBAL);
    } else {
        usize vpn = ((firstfree << FLAG_BITS) | READ | WRITE | EXECUTE | VALID | GLOBAL);
    }
    return vpn;
}

int pfree(usize vpn, usize ppn) {

    *(usize*)vpn = firstfree;
    firstfree = ppn;
}

