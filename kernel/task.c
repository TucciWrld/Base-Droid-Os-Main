#include "../include/task.h"
#include "../include/kernel.h"

#define MAX_TASKS 256

static task_t tasks[MAX_TASKS];
static int task_count = 0;
static int current_task = 0;

void init_task_manager() {
    memset(tasks, 0, sizeof(tasks));
    task_count = 0;
    current_task = 0;
}

int create_task(void (*entry_point)(void), char *name) {
    if(task_count >= MAX_TASKS) {
        return -1; // Task table full
    }
    
    tasks[task_count].id = task_count;
    tasks[task_count].state = TASK_READY;
    tasks[task_count].entry_point = entry_point;
    memcpy(tasks[task_count].name, name, 32);
    
    int task_id = task_count;
    task_count++;
    
    return task_id;
}

void switch_task() {
    current_task = (current_task + 1) % task_count;
    
    if(tasks[current_task].state == TASK_READY) {
        tasks[current_task].state = TASK_RUNNING;
    }
}

void schedule() {
    int i;
    for(i = 0; i < task_count; i++) {
        if(tasks[i].state == TASK_READY) {
            tasks[i].state = TASK_RUNNING;
            current_task = i;
            break;
        }
    }
}

task_t *get_current_task() {
    if(current_task < task_count) {
        return &tasks[current_task];
    }
    return 0;
}

int get_task_count() {
    return task_count;
}