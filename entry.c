void loop(void) {
    volatile int *addr = (int*) 0x100000;
    *addr = 0x5555;
}