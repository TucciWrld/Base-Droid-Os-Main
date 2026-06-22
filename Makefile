# Base Droid OS Makefile

CC = gcc
AS = nasm
LD = ld

CFLAGS = -ffreestanding -fno-stack-protector -nostdlib -m32 -Wall -Wextra
LDFLAGS = -m elf_i386 -Tlinker.ld -nostdlib

# Source files
BOOT_SRC = boot/bootloader.asm
KERNEL_SRC = kernel/kernel.c kernel/memory.c kernel/interrupts.c kernel/task.c
OBJS = kernel.o memory.o interrupts.o task.o

# Output
BOOT_BIN = boot.bin
KERNEL_ELF = kernel.elf
FLOPPY_IMG = floppy.img

all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c -o $@ $<

memory.o: kernel/memory.c
	$(CC) $(CFLAGS) -c -o $@ $<

interrupts.o: kernel/interrupts.c
	$(CC) $(CFLAGS) -c -o $@ $<

task.o: kernel/task.c
	$(CC) $(CFLAGS) -c -o $@ $<

bootloader: $(BOOT_BIN)

$(BOOT_BIN): $(BOOT_SRC)
	$(AS) -f bin -o $@ $<

clean:
	rm -f $(OBJS) $(KERNEL_ELF) $(BOOT_BIN) *.o

.PHONY: all clean bootloader