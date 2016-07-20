#!/bin/sh
rm -r build/*
i686-elf-as boot.s -o build/boot.o
#i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-g++ -c kernel.cpp -o build/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -T linker.ld -o build/kernel.bin -ffreestanding -O2 -nostdlib build/*.o -lgcc


mkdir -p build/iso/boot/grub
cp build/kernel.bin build/iso/boot/kernel.bin
cp grub.cfg build/iso/boot/grub/grub.cfg
grub-mkrescue -o build/kernel.iso build/iso

