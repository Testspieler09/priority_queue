#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../src/min_heap_pq.h"

int main(void) {
    MinHeapPQ *pq1 = mh_new();
    MinHeapPQ *pq2 = mh_new();

    mh_insert(pq1, "A", 5);
    mh_insert(pq1, "B", 1);

    mh_insert(pq2, "C", 3);
    mh_insert(pq2, "D", 2);

    MinHeapPQ *merged = mh_merge(pq1, pq2);
    assert(strcmp((char *)mh_extractMin(merged), "B") == 0);
    assert(strcmp((char *)mh_extractMin(merged), "D") == 0);
    assert(strcmp((char *)mh_extractMin(merged), "C") == 0);
    assert(strcmp((char *)mh_extractMin(merged), "A") == 0);
    assert(mh_isEmpty(merged));
    mh_free(merged);
    // pq1 and pq2 nodes are now owned by merged, so just free the shells
    free(pq1->elements); free(pq1);
    free(pq2->elements); free(pq2);

    printf("test_merge passed\n");
    return 0;
}
