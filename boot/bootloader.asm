; Base Droid OS Bootloader
; x86 Real Mode Bootloader
; Loads kernel into memory and switches to protected mode

[BITS 16]
[ORG 0x7C00]

BOOT_DRIVE db 0

start:
    cli                 ; Disable interrupts
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti                 ; Enable interrupts

    mov [BOOT_DRIVE], dl ; Store boot drive

    mov ah, 0x0E        ; BIOS print char function
    mov al, 'B'         ; Print 'B'
    mov bh, 0x00
    int 0x10

    mov al, 'o'
    int 0x10

    mov al, 'o'
    int 0x10

    mov al, 't'
    int 0x10

    mov al, '!'
    int 0x10

    ; Enter protected mode
    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1         ; Set protection enable bit
    mov cr0, eax

    jmp CODE_SEG:init_pm

[BITS 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000   ; Set stack pointer

    call 0x10000       ; Jump to kernel
    jmp $              ; Halt

; GDT (Global Descriptor Table)
gdt_start:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510 - ($ - $$) db 0
dw 0xAA55