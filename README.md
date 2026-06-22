# Base Droid OS - A Real Computer Operating System in C

A minimal but functional operating system written in C with x86 bootloader and kernel implementation.

## Project Overview

Base Droid OS is an educational operating system project designed to demonstrate core OS concepts including:
- Bootloader and kernel initialization
- Memory management (paging, segmentation)
- Process/task management and scheduling
- Interrupt handling
- Basic file system
- Device drivers

## Architecture

```
Base-Droid-Os-Main/
├── boot/                 # Bootloader (x86 assembly)
├── kernel/              # Kernel source code (C)
├── drivers/             # Device drivers
├── fs/                  # File system implementation
├── mm/                  # Memory management
├── include/             # Header files
├── Makefile             # Build configuration
└── docs/                # Documentation
```

## Building

### Prerequisites
- GCC cross-compiler (i686-elf-gcc)
- GNU Make
- NASM (Netwide Assembler)
- QEMU (for testing)

### Build Instructions

```bash
make clean
make
```

## Running on QEMU

```bash
qemu-system-i386 -kernel kernel.elf
```

## Project Status

- [x] Basic bootloader structure
- [x] Kernel initialization
- [ ] Paging and virtual memory
- [ ] Process management
- [ ] Interrupt handlers
- [ ] File system
- [ ] User mode execution

## License

MIT License

## Author

TucciWrld

---

**Note**: This is an educational project for learning OS concepts. Not intended for production use.