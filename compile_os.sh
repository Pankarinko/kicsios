#! /usr/bin/bash

mkdir -p build

riscv64-unknown-elf-gcc -O3 -nostdlib -nostartfiles -march=rv64g -mabi=lp64 -mcmodel=medany -fvisibility=hidden -c entry.S -o build/asm_entry.o

riscv64-unknown-elf-gcc -O3 -nostdlib -nostartfiles -march=rv64g -mabi=lp64 -mcmodel=medany -fvisibility=hidden -c entry.c -o build/c_entry.o

riscv64-unknown-elf-gcc -O3 -nostdlib -nostartfiles -march=rv64g -mabi=lp64 -mcmodel=medany -fvisibility=hidden -T script.ld build/*.o -o kernel
