ENTRY(asm_entry)
OUTPUT_ARCH(riscv)

MEMORY {

    RAM (rwx) : org = 0x80000000, len = 1M
}

PHDRS {
  text PT_LOAD;
}

SECTIONS {
 .text : {
    . = ALIGN(8);
    *(.text)
    *(.text*)
 } > RAM : text

}
