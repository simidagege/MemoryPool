#ifndef STAR_AIR_MEM_POOL_H
#define STAR_AIR_MEM_POOL_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

/**
 * @brief SAMP: Star Air Memory Pool
 * 
 */
#define SAMP_OK 0
#define SAMP_MALLOC_FAILURE -1
#define SAMP_UNINITIALIZED -2
#define SAMP_INVALID_ARGUMENT -3

/**
 * @brief buffer node
 * 
 */
typedef struct buffer_node_s samp_node_t;
struct buffer_node_s {
	uint32_t column;
	uint8_t * buffer;
	samp_node_t * next;
};

/**
 * @brief buffer column, each column contains number of buffers in same buffer capacity
 * 
 */
typedef struct samp_column_s {
    uint32_t totol_counts;
    uint32_t used_counts;
    uint32_t buffer_capacity;
    samp_node_t * free;
    samp_node_t * used;
} samp_column_t;

int samp_init(uint32_t columns, uint32_t buffer_capacities[], uint32_t buffer_counts_per_cloumn[]);
samp_node_t * samp_malloc(uint32_t capacity);
int samp_free(samp_node_t * buffer);
int samp_destory(void);
int samp_runtime_print(void);

#endif // STAR_AIR_MEM_POOL_H