#ifndef _VMA_INCLUDE
#define _VMA_INCLUDE

extern char endkernel[];

#define PAGESIZE (1 << 12) 

//Mode settings
#define SV32 1ull
#define SV39 8ull
#define SV48 9ull
#define SV57 10ull

//ASID Settings (temporary)
#define ASID 0ull


//Adresses
#define ROUNDUP_PAGE (((usize) endkernel + (usize)(PAGESIZE - 1)) & ~(usize)(PAGESIZE - 1))
#define ROUNDDOWN_PAGE ((usize) endkernel & ~(usize)(PAGESIZE - 1));

//PTEs
#if ARCHSIZE == 32
#define SET_ROOT (((SV32) << 31) | (ASID << 22) | (ROUNDUP_PAGE >> 12))
#else
#define SET_ROOT (((SV48) << 60) | (ASID << 44) | (ROUNDUP_PAGE >> 12))
#endif

//Page table setting functions
void set_root_page_table();

#endif
