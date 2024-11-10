#include "kstd.h"


struct time_unit {
    uint64 minute;
    uint64 seconds;
} typedef time_unit;

/*Get the current value of the MTIME register*/
uint64 get_time();

/*Set timer in human readable form*/
void set_timer_h(time_unit time);