#include "../include/kernel.h"
#include "../include/io.h"

volatile char *video_memory = (volatile char *) 0xB8000;
int cursor_x = 0;
int cursor_y = 0;

void kernel_main() {
    clear_screen();
    print_string("===================================");
    print_newline();
    print_string("Base Droid OS - Kernel Loaded");
    print_newline();
    print_string("===================================");
    print_newline();
    print_newline();
    
    print_string("Initializing kernel components...");
    print_newline();
    
    init_memory();
    print_string("[OK] Memory management initialized");
    print_newline();
    
    init_interrupts();
    print_string("[OK] Interrupt handlers initialized");
    print_newline();
    
    init_task_manager();
    print_string("[OK] Task manager initialized");
    print_newline();
    
    print_newline();
    print_string("Kernel initialization complete!");
    print_newline();
    print_string("Ready for user mode...");
    print_newline();
    
    while(1) {
        asm volatile("hlt");
    }
}

void clear_screen() {
    int i;
    for(i = 0; i < 80 * 25 * 2; i++) {
        video_memory[i] = 0x00;
    }
    cursor_x = 0;
    cursor_y = 0;
}

void print_char(char c) {
    if(c == '\n') {
        cursor_y++;
        cursor_x = 0;
        return;
    }
    
    int offset = (cursor_y * 80 + cursor_x) * 2;
    video_memory[offset] = c;
    video_memory[offset + 1] = 0x0F; // White text on black background
    
    cursor_x++;
    if(cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
}

void print_string(const char *str) {
    int i = 0;
    while(str[i] != '\0') {
        print_char(str[i]);
        i++;
    }
}

void print_newline() {
    cursor_y++;
    cursor_x = 0;
}

int strlen(const char *str) {
    int count = 0;
    while(str[count] != '\0') {
        count++;
    }
    return count;
}

void *memset(void *ptr, int value, unsigned int size) {
    unsigned char *p = (unsigned char *)ptr;
    for(unsigned int i = 0; i < size; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

void *memcpy(void *dest, const void *src, unsigned int size) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for(unsigned int i = 0; i < size; i++) {
        d[i] = s[i];
    }
    return dest;
}