#ifndef _ALLOC
#define _ALLOC

//Initialize the list of free physical pages. Every free page stores the address of the next free page. 
#include "kstd.h"
void createfreelist(void);

//Allocate a page for data
usize p_alloc(usize vpn);
//Free a page
int pfree(usize vpn, usize ppn);

#endif
