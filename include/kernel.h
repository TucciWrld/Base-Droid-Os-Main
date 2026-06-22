#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

void kernel_main();
void clear_screen();
void print_char(char c);
void print_string(const char *str);
void print_newline();
int strlen(const char *str);
void *memset(void *ptr, int value, unsigned int size);
void *memcpy(void *dest, const void *src, unsigned int size);

#endif