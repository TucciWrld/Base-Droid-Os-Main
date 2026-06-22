#include "../include/memory.h"
#include "../include/kernel.h"

#define HEAP_SIZE 0x100000  // 1MB heap
#define HEAP_START 0x100000 // Start at 1MB

static unsigned char heap[HEAP_SIZE];
static unsigned int heap_used = 0;

void init_memory() {
    memset(heap, 0, HEAP_SIZE);
    heap_used = 0;
}

void *kmalloc(unsigned int size) {
    if(heap_used + size > HEAP_SIZE) {
        return 0; // Out of memory
    }
    
    void *ptr = (void *)(heap + heap_used);
    heap_used += size;
    return ptr;
}

void kfree(void *ptr) {
    // Simple heap - no free for now
    // Real implementation would use free list
}

unsigned int get_heap_used() {
    return heap_used;
}

unsigned int get_heap_free() {
    return HEAP_SIZE - heap_used;
}

void print_memory_info() {
    print_string("Memory Info:");
    print_newline();
    print_string("Heap Used: ");
    // Print number function would go here
    print_newline();
    print_string("Heap Free: ");
    print_newline();
}