#include "kstd.h"

void trap_vector();

void irq_handler(void) {
  usize cause = 0;
  asm("csrrs %0, mcause, zero"
      : "=r" (cause));
  if ((cause >> (ARCHSIZE - 1)) == 1) {
      cause = (cause << 1) >> 1;
      switch (cause) {
          case 0 ... 3:
               println("SOFTWARE INTERRUPT");
               while (1);
           case 4 ... 7:
               println("TIMER INTERRUPT");
               while (1);
           case 8 ... 11:
               println("EXTERNAL INTERRUPT");
               while (1);
         default: 
              println("UNKNOWN INTERRUPT");
              while (1); 
      }
  } else {
  cause = (cause << 1) >> 1;
      switch (cause) {
          case 0:
          case 1: 
               println("KERNEL PANIC");
               println("Running this instruction is not possible");
               while (1);
          case 2: 
              println("KERNEL PANIC");
              println("Illegal instruction");
              while (1);
          case 3: 
               println("KERNEL PANIC");
               println("Breakpoint");
              while (1);
         case 4:
         case 5: 
              println("KERNEL PANIC");
              println("Loading from this address is not possible");
              while (1);
         case 6:
         case 7: 
              println("KERNEL PANIC");
              println("Storing data to address is not possible");
              while (1);
         case 8:
         case 9:
         case 11: 
              println("KERNEL PANIC");
              println("Environment call");
              while (1);
         case 12:
         case 13:
         case 15: 
              println("KERNEL PANIC");
              println("Page fault");
              while (1);
         default: 
              println("KERNEL PANIC");
              println("Unknown reason");
              while (1); 
      }
  }
}

void test(void) {
  println("Interrupt ende");
}

void set_irq(void) {
  void (*irq_addr)(void) = &trap_vector;
  asm("csrrw zero, mtvec, %0"
      : 
      : "r" (irq_addr));
}
