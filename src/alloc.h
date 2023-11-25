#ifndef _ALLOC
#define _ALLOC

extern char startkernel[];

#define MEMORYSTART startkernel
//TODO set this later! 
#define MEMORYSIZE 512 * PAGESIZE 

//Initialize the list of free physical pages. Every free page stores the address of the next free page. 
int createfreelist();

//Used after freeing a page. Insert the freed page into the free-pages list.
int update_free();

//Allocate a page for a page table
int talloc();
//Free the page of the page table.
int tfree();

//Allocate a page for data
int palloc();
//Free a page
int pfree();

#endif
