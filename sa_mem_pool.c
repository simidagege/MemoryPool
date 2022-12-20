#include "sa_mem_pool.h"

samp_column_t * p_column = NULL;
int column_counts = 0;

int samp_init(uint32_t columns, uint32_t buffer_capacities[], uint32_t buffer_counts_per_cloumn[]) {
    p_column = (samp_column_t *)malloc(sizeof(samp_column_t) * columns);
    if (!p_column) {
        printf("failed to malloc for mem pool\n");
        return SAMP_MALLOC_FAILURE;
    }
    memset(p_column, 0, sizeof(samp_column_t) * columns);
    column_counts = columns;

    samp_node_t * curr_node = NULL;
    samp_node_t * new_node = NULL;
    for (int i = 0; i < columns; i++) {
        p_column[i].totol_counts = buffer_counts_per_cloumn[i];
        p_column[i].buffer_capacity = buffer_capacities[i];
        for (int j = 0; j < buffer_counts_per_cloumn[i]; j++) {
            new_node = (samp_node_t *)malloc(sizeof(samp_node_t));
            new_node->column = i;
            new_node->buffer = (uint8_t *)malloc(buffer_capacities[i]);
            memset(new_node->buffer, 0, buffer_capacities[i]);
            if (!new_node || !new_node->buffer) {
                printf("failed to malloc for mem pool node\n");
                return SAMP_MALLOC_FAILURE;
            }
            new_node->next = NULL;
            if (j == 0) {
                p_column[i].free = new_node;
                curr_node = p_column[i].free;
            } else {
                curr_node->next = new_node;
                curr_node = curr_node->next;
            }
        }
    }
    return SAMP_OK;
}

samp_node_t * samp_malloc(uint32_t capacity) {
    if (!p_column) {
        printf("mem pool uninitialized\n");
        return NULL;
    }
    samp_node_t * node = NULL;
    if (capacity > p_column[column_counts - 1].buffer_capacity) {
        printf("out of max buffer capacity\n");
        return NULL;
    }
    for (int i = 0; i < column_counts; i++) {
        if (capacity > p_column[i].buffer_capacity) {
            continue;
        }
        if (p_column[i].totol_counts == p_column[i].used_counts) {
            printf("warning: will try to use bigger capacity buffer: %d\n", p_column[i].buffer_capacity);
            continue;
        }
        node = p_column[i].free;
        p_column[i].free = p_column[i].free->next;
        p_column[i].used_counts++;
        node->next = p_column[i].used;
        p_column[i].used = node;
        return node;
    }
    printf("fatal: failed to malloc buffer node\n");
    return NULL;
}

int samp_free(samp_node_t * buffer) {
    if (!p_column) {
        printf("mem pool uninitialized\n");
        return SAMP_UNINITIALIZED;
    }
    if (!buffer) {
        printf("invalid argument\n");
        return SAMP_INVALID_ARGUMENT;
    }
    samp_node_t * curr_node = p_column[buffer->column].used;
    samp_node_t * prev_node = NULL;
    while (curr_node) {
        if (curr_node != buffer) {
            prev_node = curr_node;
            curr_node = curr_node->next;
            continue;
        }
        if (prev_node == NULL) {
            p_column[buffer->column].used = p_column[buffer->column].used->next;
        } else {
            prev_node->next = curr_node->next;
        }
        p_column[buffer->column].used_counts--;
        curr_node->next = p_column[buffer->column].free;
        p_column[buffer->column].free = curr_node;
        memset(p_column[buffer->column].free->buffer, 0, p_column[buffer->column].buffer_capacity);
        break;
    }
    return SAMP_OK;
}

int samp_destory(void) {
    if (!p_column) {
        printf("mem pool uninitialized\n");
        return SAMP_UNINITIALIZED;
    }
    samp_node_t * curr_node = NULL;
    samp_node_t * del_node = NULL;
    for (int i = 0; i < column_counts; i++) {
        curr_node = p_column[i].used;
        while (curr_node) {
            del_node = curr_node;
            curr_node = curr_node->next;
            free(del_node->buffer);
            free(del_node);
        }
        curr_node = p_column[i].free;
        while (curr_node) {
            del_node = curr_node;
            curr_node = curr_node->next;
            free(del_node->buffer);
            free(del_node);
        }
    }
    free(p_column);
    p_column = NULL;
    column_counts = 0;
    return SAMP_OK;
}

int samp_runtime_print(void) {
    if (!p_column) {
        printf("mem pool uninitialized\n");
        return SAMP_UNINITIALIZED;
    }
    printf("\n*********************** samp runtime report start ************************\n");
    for (int i = 0; i < column_counts; i++) {
        printf("mem_pool column[%d] buffer_capacity[%d] total_counts[%d] used[%d] used percentage[%d%%]\n" \
			, i, p_column[i].buffer_capacity, p_column[i].totol_counts, p_column[i].used_counts \
            , p_column[i].used_counts*100/ p_column[i].totol_counts);
    }
    printf("\n*********************** samp runtime report end **************************\n");
}