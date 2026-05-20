#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../src/fib_heap_pq.h"

int main(void) {
    FibHeapPQ *pq1 = fh_new();
    FibHeapPQ *pq2 = fh_new();

    fh_insert(pq1, "A", 5);
    fh_insert(pq1, "B", 1);

    fh_insert(pq2, "C", 3);
    fh_insert(pq2, "D", 2);

    FibHeapPQ *merged = fh_merge(pq1, pq2);
    assert(strcmp((char *)fh_extractMin(merged), "B") == 0);
    assert(strcmp((char *)fh_extractMin(merged), "D") == 0);
    assert(strcmp((char *)fh_extractMin(merged), "C") == 0);
    assert(strcmp((char *)fh_extractMin(merged), "A") == 0);
    assert(fh_isEmpty(merged));
    fh_free(merged);
    // pq1 and pq2 nodes are now owned by merged, so just free the shells
    free(pq1);
    free(pq2);

    printf("test_merge passed\n");
    return 0;
}
