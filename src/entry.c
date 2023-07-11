#include "parser.c"

void terminate(void) {
    volatile int *addr = (int*) 0x100000;
    *addr = 0x5555;
}

void c_entry(void) {
    char* word = "HelloWorld";
    println(word);
    terminate();
}

