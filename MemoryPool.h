#ifndef XR_MEMORY_POOL_H
#define XR_MEMORY_POOL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <pthread.h>

// memory pool capacity, default: 20
#define MEMORY_POOL_CAPACITY 20

static const int32_t MP_STATUS_OK = 0;
static const int32_t MP_STATUS_ERROR = -1;

typedef int32_t MP_STATUS_t;

typedef struct MemoryPoolItem_s {
    uint8_t *data; // data buffer
    int16_t length; // buffer used length
    int16_t capacity; // buffer capacity
} MemoryPoolItem_t;

typedef struct MemoryPool_s {
    MemoryPoolItem_t queue[MEMORY_POOL_CAPACITY];
    int16_t used_map[MEMORY_POOL_CAPACITY];
    int16_t used_count;
    int16_t current;
    pthread_mutex_t mutex;
} MemoryPool_t;

MemoryPool_t* MemoryPool_init(int16_t itemCapacity);
MP_STATUS_t MemoryPool_destroy(MemoryPool_t* cq);
MemoryPoolItem_t* MemoryPool_alloc(MemoryPool_t* cq);
MP_STATUS_t MemoryPool_free(MemoryPool_t* cq, MemoryPoolItem_t* item);

#endif // XR_MEMORY_POOL_H