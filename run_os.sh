#! /usr/bin/bash

if $(file kernel | grep 32-bit); then
	qemu="qemu-system-riscv32"
else
	qemu="qemu-system-riscv64"
fi

$qemu -nographic -machine virt -bios none -kernel kernel
