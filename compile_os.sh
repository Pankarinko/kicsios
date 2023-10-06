#! /usr/bin/bash

if [ "$1" = 32 ]; then
	bits=32
	abi=ilp32f
	arch=rv32g
else
	bits=64
	abi=lp64f
	arch=rv64g
fi

archabi="-march=$arch -mabi=$abi"

set -e

mkdir -p build

for i in src/*.c
do
	riscv"$bits"-unknown-elf-gcc -O0 -nostdlib -nostartfiles $archabi -mcmodel=medany -c "$i" -o build/"$(basename $i .c)".o
done

for i in src/*.S
do
	riscv"$bits"-unknown-elf-gcc -O0 -nostdlib -nostartfiles $archabi -mcmodel=medany -c "$i" -o build/asm_"$(basename $i .S)".o
done

riscv"$bits"-unknown-elf-gcc -O0 -nostdlib -nostartfiles $archabi -mcmodel=medany -T script.ld build/*.o -o kernel
