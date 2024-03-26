#include "vma.h"
#include "kstd.h"
#include "alloc.h"

//TODO global lock
usize firstfree;

//For this method, we need to set satp_mode to BARE
void createfreelist(void) {
    firstfree = ROOT_PAGE_TABLE;
    usize i;
    for (i = ROOT_PAGE_TABLE; i < MEMORYSTART + MEMORYSIZE - PAGESIZE; i += PAGESIZE ) { 
            *(usize*) i = i + PAGESIZE;
    }
    *(usize*) i = NO_NEXT_FREE_PAGE;
    } 



//Following methods are for satp_mode SVXX
usize p_alloc(usize vpn, uint table) {
        if (!(firstfree << 10)) {
        return -1;
    }
    if (table) {
        *(usize*)vpn = (firstfree | VALID | GLOBAL);
    } else {
        *(usize*)vpn = (firstfree | READ | WRITE | EXECUTE | VALID | GLOBAL);
    }
    firstfree = *(usize*)(vpn << 12);
    if (!firstfree) {
        return -1;
    }
    return 0;
}

int pfree(usize vpn, usize ppn) {

    *(usize*)vpn = firstfree;
    firstfree = ppn;
 }

