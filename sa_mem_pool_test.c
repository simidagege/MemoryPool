#include "sa_mem_pool.h"
#include <stdint.h>

int main() {
    printf("Please input any key to start init and malloc star air memory pool\n");
    getchar();

    uint32_t buffer_capacities[] = {128, 256, 512, 1024, 2028, 4096};
    uint32_t buffer_counts_per_cloumn[] = {100, 90, 80, 70, 60, 50};
    samp_init(6, buffer_capacities, buffer_counts_per_cloumn);

    samp_node_t * node1 = samp_malloc(100);
    samp_node_t * node2 = samp_malloc(200);
    samp_node_t * node3 = samp_malloc(400);
    samp_node_t * node4 = samp_malloc(600);
    samp_node_t * node5 = samp_malloc(1200);
    samp_node_t * node6 = samp_malloc(2400);
    samp_runtime_print();

    printf("Please input any key to free memory\n");
    getchar();
    samp_free(node1);
    samp_free(node2);
    samp_free(node3);
    samp_free(node4);
    samp_free(node5);
    samp_free(node6);
    samp_runtime_print();

    printf("Please input any key to destroy memory pool\n");
    getchar();
    samp_destory();

    return 0;
}