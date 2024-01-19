#ifndef _VMA_INCLUDE
#define _VMA_INCLUDE

extern char endkernel[];
extern char startkernel[];

#define PAGESIZE (1ull << 12) 
typedef __UINTPTR_TYPE__ ptetype; 

#define MEMORYSTART startkernel
//TODO set this later! 
#define MEMORYSIZE 512 * PAGESIZE 


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

//Architecture table parameters
#if ARCHSIZE == 32
#define VPNSIZE 10ull
#define LEVELS 2ull
// How many bits to shift when accessessing page table address recursively
#define PTE_LOG 2 
#define MAXADDRESS 1023
#else
#define VPNSIZE 9ull
#define LEVELS 4ull
#define PTE_LOG 3
#define MAXADDRESS 511
#endif


//ASID Settings (temporary)
#define ASID 0ull


//Adresses
#define ROUNDUP_PAGE(address) (((usize) (address) + (usize)(PAGESIZE - 1)) & ~(usize)(PAGESIZE - 1))
#define ROUNDDOWN_PAGE(address) ((usize) (address) & ~(usize)(PAGESIZE - 1));

#define ROOT_PAGE_TABLE ROUNDUP_PAGE(endkernel)

//PTEs
#define SET_ROOT_INIT (0 | (ASID << 22) | (ROUNDUP_PAGE(endkernel) >> 12))
#if ARCHSIZE == 32
#define SET_ROOT (((SV32) << 31) | (ASID << 22) | (ROUNDUP_PAGE(endkernel) >> 12))
#else
#define SET_ROOT (((SV48) << 60) | (ASID << 44) | (ROUNDUP_PAGE(endkernel) >> 12))
#endif

//Page table setting functions
void set_root_page_table();
void initialize_vm(void);
void zero_page(usize *page);

#endif
