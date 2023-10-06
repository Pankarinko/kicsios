#include "kstd.h"

void trap_vector();

void irq_handler(void) {
  println("Interrupt");
}

void test(void) {
  println("Interrupt ende");
}

void set_irq(void) {
  void (*irq_addr)(void) = &trap_vector;
  asm("csrrw x0, mtvec, %0"
      : 
      : "r" (irq_addr));
}
