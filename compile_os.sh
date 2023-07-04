#! /usr/bin/bash

riscv64-unknown-elf-gcc -O3 -nostdlib -nostartfiles -march=rv64g -mabi=lp64 -mcmodel=medany -fvisibility=hidden -T script.ld entry.S -o kernel
