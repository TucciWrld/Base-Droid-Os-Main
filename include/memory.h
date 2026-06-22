#ifndef MEMORY_H
#define MEMORY_H

volatile typedef unsigned int size_t;

void init_memory();
void *kmalloc(unsigned int size);
void kfree(void *ptr);
unsigned int get_heap_used();
unsigned int get_heap_free();
void print_memory_info();

#endif