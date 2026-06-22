# Base Droid OS Architecture

## Overview

Base Droid OS is a 32-bit x86 operating system designed with the following architecture:

## Bootloader Phase

1. **Real Mode (16-bit)** - Bootloader runs in x86 real mode
   - Located at 0x7C00 (standard BIOS boot location)
   - Loads GDT (Global Descriptor Table)
   - Initializes basic registers
   - Prints boot messages

2. **Protected Mode Transition**
   - Sets protection enable bit in CR0
   - Loads GDT descriptor
   - Performs far jump to protected mode

## Kernel Phase

### Memory Layout
```
0x00000000 - 0x000FFFFF : Real mode memory / BIOS data
0x00100000 - 0x001FFFFF : Kernel code and data (1MB)
0x00200000 - 0x002FFFFF : Heap space (1MB)
0xB8000    : VGA text buffer (80x25 characters)
```

### Core Components

#### 1. Memory Management (`kernel/memory.c`)
- Simple heap allocator
- kmalloc() for allocation
- kfree() placeholder for deallocation
- Tracks heap usage

#### 2. Interrupt Handling (`kernel/interrupts.c`)
- IDT (Interrupt Descriptor Table) initialization
- ISR (Interrupt Service Routine) handlers
- Exception handling (Division by Zero, GPF, etc.)

#### 3. Task Management (`kernel/task.c`)
- Task control blocks (TCB)
- Task states (READY, RUNNING, BLOCKED, TERMINATED)
- Task scheduling framework
- Context switching stub

#### 4. I/O Operations (`include/io.h`)
- Port I/O (inb, outb)
- Used for device communication

## Boot Process

1. BIOS loads bootloader at 0x7C00
2. Bootloader displays "Boot!" message
3. Sets up GDT
4. Switches to protected mode
5. Jumps to kernel at 0x10000
6. Kernel initializes:
   - Clears screen
   - Initializes memory manager
   - Initializes interrupt handlers
   - Initializes task manager
   - Enters main loop (halts)

## Compilation and Linking

- **Bootloader**: Assembled to binary with NASM
- **Kernel**: Compiled with GCC (i686-elf-gcc)
- **Linking**: LD (GNU Linker) with custom linker script

## Future Enhancements

- [ ] Virtual memory (paging)
- [ ] User mode execution rings
- [ ] Process creation (fork, exec)
- [ ] Inter-process communication (IPC)
- [ ] File system (FAT32, ext2)
- [ ] Device drivers (keyboard, disk)
- [ ] Networking stack
- [ ] Shell/command interpreter