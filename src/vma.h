#ifndef _VMA_INCLUDE
#define _VMA_INCLUDE

#include "kstd.h"
extern char endkernel[];
extern char startkernel[];

#define PAGESIZE (1ull << 12) 
#define PAGE_LOG 12
typedef __UINTPTR_TYPE__ ptetype; 

#define MEMORYSTART startkernel
//TODO set this later! 
#define MEMORYSIZE 512 * PAGESIZE 
#define NO_NEXT_FREE_PAGE 1ull


//Mode settings
#define SV32 1ull
#define SV39 8ull //Not used
#define SV48 9ull
#define SV57 10ull //Not used

//PTE flags
#define VALID 1ull
#define READ 2ull
#define WRITE 4ull
#define EXECUTE 8ull
#define USERMODE 16ull
#define GLOBAL 32ull
#define ACCESSED 64ull
#define DIRTY 128ull

// How many flag bits a PTE has (useful for shifts)
#define FLAG_BITS 10
// ??
#define ADDRESS_MASK (((usize) 1 << PPNSIZE) - 1)

//Architecture table parameters
#if ARCHSIZE == 32
#define VPNSIZE 10ull
#define PPNSIZE 34ull
#define LEVELS 2ull
// How many bits to shift when accessessing page table address recursively
#define PTE_LOG 2 
#define MAXPTE 1023
#define PPN_TO_VPN_MASK 0
#else
#define VPNSIZE 9ull
#define PPNSIZE 44ull
#define LEVELS 3ull
#define PTE_LOG 3
#define MAXPTE 511
#define PPN_TO_VPN_MASK 14
#endif



//ASID Settings (temporary)
#define ASID 0ull


//Adresses
#define ROUNDUP_PAGE(address) (((usize) (address) + (usize)(PAGESIZE - 1)) & ~(usize)(PAGESIZE - 1))
#define ROUNDDOWN_PAGE(address) ((usize) (address) & ~(usize)(PAGESIZE - 1))

#define ROOT_PAGE_TABLE ROUNDUP_PAGE(endkernel)

//PTEs
#define SET_ROOT_BARE (0 | (ASID << 22) | (ROUNDUP_PAGE(endkernel) >> 12))
#if ARCHSIZE == 32
#define SET_ROOT (((SV32) << 31) | (ASID << 22) | (ROUNDUP_PAGE(endkernel) >> 12))
#else
#define SET_ROOT (((SV39) << 60) | (ASID << 44) | (ROUNDUP_PAGE(endkernel) >> 12))
#endif

//Page table setting functions
void set_root_page_table();
void set_root_page_table_bare();
void set_mode(void);
void initialize_vm(void);
void zero_page(usize *page);
void map_tables();
void map_page(usize va);
void map_kernel();
usize translate_address(usize va);


#endif
