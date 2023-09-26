void irq(void) {
  
}


void set_irq(void) {
  void (*irq_addr)(void) = &irq;
  asm("csrrw x0, mtvec, %0"
      : 
      : "r" (irq_addr));
  print_u64((uint64) *irq_addr);
}
