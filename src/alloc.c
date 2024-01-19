#include "vma.h"
#include "kstd.h"
#include "alloc.h"

usize firstfree;

//For this method, we need to set satp_mode to BARE
void createfreelist(void) {
    firstfree = ROOT_PAGE_TABLE;
    usize i;
    for (i = ROOT_PAGE_TABLE; i < MEMORYSTART + MEMORYSIZE - PAGESIZE; i += PAGESIZE ) { 
            *(usize*) i = i + PAGESIZE;
    }
    *(usize*) i = 0ull;
}
    
//Following methods are for satp_mode SVXX
int talloc(usize vpn) {
    if (!(firstfree << 10)) {
        return -1;
    }

    *(usize*)vpn = firstfree | VALID | GLOBAL;
    firstfree = *(usize*)(vpn << 12);
    if (!firstfree) {
        return -1;
    }
    return 0;
} 

usize palloc(usize vpn) {
        if (!(firstfree << 10)) {
        return -1;
    }
    *(usize*)vpn = firstfree | READ | WRITE | EXECUTE| GLOBAL;
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

