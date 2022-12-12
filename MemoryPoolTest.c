#include "MemoryPool.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    uint16_t queueCapacity = 20;
    uint16_t itemCapacity = 512;
    MemoryPool_t* queue = MemoryPool_init(itemCapacity);
    MemoryPoolItem_t* item = MemoryPool_alloc(queue);
    if (item) {
        memset(item->data, 88, 8);
        printf("succeed to get free memory, item->addr: %p, item->capacity: %d, item->length:%d\n",
            &(item->data), item->capacity, item->length);
        for (int i = 0; i < 10; i++) {
            printf("item->data[%d]: %d\n", i, item->data[i]);
        }
    }
    MemoryPoolItem_t* item1 = MemoryPool_alloc(queue);
    if (item1) {
        printf("succeed to get free memory, item1->addr: %p, item1->capacity: %d, item1->length:%d\n",
            &(item1->data), item1->capacity, item1->length);
    }
    if (MemoryPool_free(queue, item) == MP_STATUS_OK) {
        printf("succeed to free item\n");
    }
    MemoryPool_destroy(queue);
    return 0;
}