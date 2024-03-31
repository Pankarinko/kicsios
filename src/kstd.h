#ifndef _KSTD_INCLUDE
#define _KSTD_INCLUDE

// Integer data types
typedef __UINT8_TYPE__ uint8;
typedef __UINT32_TYPE__ uint32;
typedef __UINT64_TYPE__ uint64;
typedef __UINTPTR_TYPE__ usize; // Unsigned integer in size of architecture
typedef __INTPTR_TYPE__ ssize; // Signed integer in the size of the architectur
#define ARCHSIZE __INTPTR_WIDTH__ // Size of architecture

// Print functions
void prints(char* word);
void println(char* word);
void print_u32(uint32 num);
void print_u64(uint64 num);
void printu(usize num);
void print_hex32(uint32 num);
void print_hex64(uint64 num);
void print_hex(usize num);

//Print functions dependent on architecture
#if ARCHSIZE == 32
#define PRINTHEX(num) print_hex32((uint32) num)
#define PRINTU(num) print_u32((uint32) num)
#else
#define PRINTHEX(num) print_hex64((uint64) num)
#define PRINTU(num) print_u64((uint64) num)
#endif

// Bit operations
int clz32(uint32 v); // Counts leading zeros for 32bit values
int clz64(uint64 v); // Counts leading zeros for 64bit values

#endif
