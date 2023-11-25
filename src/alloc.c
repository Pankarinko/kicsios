#include "vma.h"
#include "kstd.h"
#include "alloc.h"

usize firstfree;

//For this method, we need to set satp_mode to BARE
void createfreelist() {
    firstfree = ROOT_PAGE_TABLE;
    usize i;
    for (i = ROOT_PAGE_TABLE; i < MEMORYSTART + MEMORYSIZE - PAGESIZE; i += PAGESIZE ) { 
            *(usize*) i = i + PAGESIZE;
    }
    *(usize*) i = 0ull;
}
    
int talloc() { }
int tfree() { }
 }

int palloc() {  }
int pfree() { }

int update_free() { }
