#! /usr/bin/bash

riscv64-unknown-elf-gcc -nostdlib -nostartfiles -march=rv64g -mabi=lp64 -mcmodel=medany -fvisibility=hidden -T script.ld entry.c -o entry
