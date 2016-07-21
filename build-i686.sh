#!/bin/sh
#set -x
rm -r build
mkdir -p build

CFLAGS="-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -I./ -I~/opt/cross/lib/gcc/i686-elf/4.8.5/include"
LDFLAGS="-ffreestanding -O2 -nostdlib -lgcc"
AS=i686-elf-as
CC=i686-elf-gcc
CPP=i686-elf-g++
LD=i686-elf-gcc

$AS boot.s -o build/boot.o
$AS asm_gdt.s -o build/asm_gdt.o
$CPP -c kernel.cpp -o build/kernel.o $CFLAGS
$CPP -c drivers/display/vga.cpp -o build/vga.o $CFLAGS
$CPP -c terminal/vgaterminal.cpp -o build/vgaterminal.o $CFLAGS
$CPP -c gdt.cpp -o build/gdt.o $CFLAGS
$LD -T linker.ld -o build/kernel.bin build/*.o $LDFLAGS


mkdir -p build/iso/boot/grub
cp build/kernel.bin build/iso/boot/kernel.bin
cp grub.cfg build/iso/boot/grub/grub.cfg
grub-mkrescue -o build/kernel.iso build/iso

