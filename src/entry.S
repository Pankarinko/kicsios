.text

.global asm_entry, "ax"

asm_entry:
    la sp, asm_stackbottom
    j c_entry
asm_stacktop:
    .space 1024
asm_stackbottom:
