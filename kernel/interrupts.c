#include "../include/interrupts.h"
#include "../include/kernel.h"

// IDT (Interrupt Descriptor Table)
static idt_entry_t idt[256];
static idt_ptr_t idt_ptr;

void init_interrupts() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (unsigned int)&idt;
    
    memset(&idt, 0, sizeof(idt));
    
    // Install default handlers
    install_handler(0, isr_0);
    install_handler(1, isr_1);
    install_handler(8, isr_8);
    install_handler(13, isr_13);
    
    // Load IDT
    asm volatile("lidt %0" : : "m"(idt_ptr));
}

void install_handler(int interrupt, void (*handler)(void)) {
    idt[interrupt].offset_low = (unsigned int)handler & 0xFFFF;
    idt[interrupt].selector = 0x08;  // Kernel code segment
    idt[interrupt].zero = 0;
    idt[interrupt].type_attr = 0x8E;  // Present, 32-bit interrupt gate
    idt[interrupt].offset_high = ((unsigned int)handler >> 16) & 0xFFFF;
}

void isr_0(void) {
    print_string("[ERROR] Division by Zero!");
    print_newline();
    while(1) asm volatile("hlt");
}

void isr_1(void) {
    print_string("[ERROR] Debug Exception!");
    print_newline();
}

void isr_8(void) {
    print_string("[ERROR] Double Fault!");
    print_newline();
    while(1) asm volatile("hlt");
}

void isr_13(void) {
    print_string("[ERROR] General Protection Fault!");
    print_newline();
    while(1) asm volatile("hlt");
}