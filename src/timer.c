#include "kstd.h"
#include "timer.h"

uint64 get_time() {
    uint64 time = 0;
    uint64 clint_base = 0;

asm volatile (
    "la %0, 0x2000000"
     : "=r" (clint_base));
asm volatile (
    "ld %1, 0(%0)" 
    : "=r" (time)
    : "r" (clint_base));
    return time;
}

void set_timer_h(time_unit time) {

}