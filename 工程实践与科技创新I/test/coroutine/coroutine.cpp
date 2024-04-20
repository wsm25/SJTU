#include "coroutine.h"

Task task_pool[MAX_TASKS];
short task_pool_index=0;

// 8 bit
struct Task{
    void (*fn)(void);
    Task* next;
};