#include "MemoryPool.h"

MemoryPool_t* MemoryPool_init(int16_t itemCapacity) {
    MemoryPool_t* cq = calloc(0, sizeof(MemoryPool_t));
    if (!cq) {
        printf("failed to calloc memory pool");
        return NULL;
    }
    cq->used_count = 0;
    cq->current = 0;
    pthread_mutex_init(&(cq->mutex), NULL);

    for (int16_t i = 0; i < (int16_t)MEMORY_POOL_CAPACITY; i++) {
        MemoryPoolItem_t* item = calloc(0, sizeof(MemoryPoolItem_t));
        item->data = calloc(0, sizeof(uint8_t) * itemCapacity);
        item->capacity = itemCapacity;
        item->length = 0;
        memcpy(&(cq->queue[i]), item, sizeof(MemoryPoolItem_t));
        printf("calloc for item[%d]: data:%p, capacity: %d, length:%d\n", i, &(cq->queue[i]), cq->queue[i].capacity, cq->queue[i].length);
        cq->used_map[i] = 0;
    }
    return cq;
}

MP_STATUS_t MemoryPool_destroy(MemoryPool_t* cq) {
    if (!cq) {
        printf("invalid memory pool\n");
        return MP_STATUS_ERROR;
    }

    for (int16_t i = 0; i < (int16_t)MEMORY_POOL_CAPACITY; i++) {
        if (cq->used_map[i] == 1) {
            MemoryPoolItem_t* itemTmp = &(cq->queue[i]);
            free(itemTmp->data);
            itemTmp->length = 0;
            itemTmp->capacity = 0;
            free(itemTmp);
            itemTmp = NULL;
        }
    }
    free(cq);
    cq = NULL;
    printf("succeed to destroy memory pool\n");
    return MP_STATUS_OK;
}

MemoryPoolItem_t* MemoryPool_alloc(MemoryPool_t* cq) {
    if (!cq) {
        printf("null memory pool\n");
        return NULL;
    }
    pthread_mutex_trylock(&(cq->mutex));
    // search free memory from current position
    int16_t i = cq->current;
    for (; i < (int16_t)MEMORY_POOL_CAPACITY; i++) {
        printf("current:%d\n", i);
        if (cq->used_map[i]) {
            printf("used id:%d \n", cq->used_map[i]);
            continue;
        }
        cq->used_map[i] = 1;
        cq->current += 1;
        cq->used_count += 1;
        if (cq->used_count == (int16_t)MEMORY_POOL_CAPACITY) {
            // reset
            cq->used_count = 0;
        }
        // found free one, return
        printf("found free memory with idex: %d\n", i);
        return &(cq->queue[i]);
    }
    // if search from current failed, try search from head again
    for (i = 0; i < cq->current; i++) {
        if (cq->used_map[i]) {
            continue;
        }
        cq->used_map[i] = 1;
        cq->used_count += 1;
        printf("found free memory with idex: %d\n", i);
        return &(cq->queue[i]);
    }
    pthread_mutex_unlock(&(cq->mutex));
    printf("none free memory found");
    return NULL;
}

MP_STATUS_t MemoryPool_free(MemoryPool_t* cq, MemoryPoolItem_t* item) {
    if (!cq || !item) {
        printf("null input arguments\n");
        return MP_STATUS_ERROR;
    }
    pthread_mutex_trylock(&(cq->mutex));
    for (int16_t i = 0; i < (int16_t)MEMORY_POOL_CAPACITY; i++) {
        if (&(cq->queue[i]) == item) {
            printf("found item:%d\n", i);
            cq->used_map[i] = 0;
            cq->used_count -= 1;
            MemoryPoolItem_t* itemTmp = &(cq->queue[i]);
            memset(itemTmp->data, 0, itemTmp->capacity);
            itemTmp->length = 0;
            itemTmp = NULL;
            return MP_STATUS_OK;
        }
    }
    pthread_mutex_unlock(&(cq->mutex));
    printf("cannot found item in pool\n");
    return MP_STATUS_ERROR;
}