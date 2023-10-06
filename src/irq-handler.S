.text

#define ARCHB __SIZEOF_POINTER__
#define REG_SPACE(n) ARCHB * (n)
#if ARCHB == 8
#define SR(reg, off) sd reg, (off*ARCHB)(sp) 
#else 
#define SR(reg, off) sw reg, (off*ARCHB)(sp) 
#endif

#if ARCHB == 8
#define LR(reg, off) ld reg, (off*ARCHB)(sp) 
#else 
#define LR(reg, off) lw reg, (off*ARCHB)(sp) 
#endif

.global trap_vector
.global irq_handler

//save all caller-saved registers onto stack
trap_vector:
	addi sp, sp, -REG_SPACE(18) 
	SR(ra, 0)
	SR(x3, 1)
	SR(x4, 2)
	SR(x5, 3)
	SR(x6, 4)
	SR(x7, 5)
	SR(x10, 6)
	SR(x11, 7)
	SR(x12, 8)
	SR(x13, 9)
	SR(x14, 10)
	SR(x15, 11)
	SR(x16, 12)
	SR(x17, 13)
	SR(x28, 14)
	SR(x29, 15)
	SR(x30, 16)
	SR(x31, 17)
	jal irq_handler
	LR(ra, 0)
	LR(x3, 1)
	LR(x4, 2)
	LR(x5, 3)
	LR(x6, 4)
	LR(x7, 5)
	LR(x10, 6)
	LR(x11, 7)
	LR(x12, 8)
	LR(x13, 9)
	LR(x14, 10)
	LR(x15, 11)
	LR(x16, 12)
	LR(x17, 13)
	LR(x28, 14)
	LR(x29, 15)
	LR(x30, 16)
	LR(x31, 17)
	addi sp, sp, REG_SPACE(18)
	mret
