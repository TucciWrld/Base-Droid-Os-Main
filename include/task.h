#ifndef TASK_H
#define TASK_H

#include "types.h"

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_TERMINATED
} task_state_t;

typedef struct {
    int id;
    task_state_t state;
    void (*entry_point)(void);
    char name[32];
} task_t;

void init_task_manager();
int create_task(void (*entry_point)(void), char *name);
void switch_task();
void schedule();
task_t *get_current_task();
int get_task_count();

#endif