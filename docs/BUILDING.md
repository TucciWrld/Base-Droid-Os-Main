# Building Base Droid OS

## Prerequisites

You need to install a cross-compiler toolchain for i686 (32-bit x86):

### On Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install build-essential nasm

# Install cross-compiler
sudo apt-get install gcc-i686-linux-gnu
# Or use: gcc-multilib for 32-bit support
```

### On macOS (with Homebrew)

```bash
brew install binutils nasm

# Install i686-elf-gcc from source or use Docker
```

### On Windows

Use Windows Subsystem for Linux (WSL) and follow Ubuntu instructions, or use:
- MinGW
- Docker with Linux container

## Building the OS

### Step 1: Clone the Repository

```bash
git clone https://github.com/TucciWrld/Base-Droid-Os-Main.git
cd Base-Droid-Os-Main
```

### Step 2: Compile

```bash
make clean
make
```

This will generate:
- `kernel.o` - Compiled kernel object
- `kernel.elf` - Linked kernel executable

### Step 3: Testing with QEMU

Install QEMU:

```bash
# Ubuntu/Debian
sudo apt-get install qemu-system-x86

# macOS
brew install qemu

# Windows - Download from https://www.qemu.org/download/
```

Run the kernel:

```bash
qemu-system-i386 -kernel kernel.elf
```

You should see:
```
===================================
Base Droid OS - Kernel Loaded
===================================

Initializing kernel components...
[OK] Memory management initialized
[OK] Interrupt handlers initialized
[OK] Task manager initialized

Kernel initialization complete!
Ready for user mode...
```

### Step 4: Debugging with QEMU

```bash
# Run with GDB support
qemu-system-i386 -s -S -kernel kernel.elf &

# In another terminal, start GDB
i686-elf-gdb kernel.elf
(gdb) target remote :1234
(gdb) break kernel_main
(gdb) continue
```

## Troubleshooting

### "gcc: No such file or directory"

You need to install the cross-compiler:

```bash
sudo apt-get install gcc-multilib
```

### "nasm: No such file or directory"

Install NASM:

```bash
sudo apt-get install nasm
```

### QEMU not found

Install QEMU:

```bash
sudo apt-get install qemu-system-x86
```

### Kernel crashes on boot

- Check linker script (linker.ld)
- Verify entry point is correct
- Use QEMU debugging with GDB
- Check memory addresses in code

## Build System Details

The Makefile supports:

- `make` - Build kernel
- `make clean` - Remove compiled files
- `make bootloader` - Build bootloader separately

## Next Steps

1. Add more hardware support
2. Implement paging
3. Create a simple shell
4. Add file system support
5. Build user-mode applications