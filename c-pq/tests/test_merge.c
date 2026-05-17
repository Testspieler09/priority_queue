#include <stdio.h>
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

    mh_merge(pq1, pq2);

    // After merge, pq1 should have all elements
    assert(strcmp((char *)mh_extractMin(pq1), "B") == 0);
    assert(strcmp((char *)mh_extractMin(pq1), "D") == 0);
    assert(strcmp((char *)mh_extractMin(pq1), "C") == 0);
    assert(strcmp((char *)mh_extractMin(pq1), "A") == 0);
    assert(mh_isEmpty(pq1));

    mh_free(pq1);
    mh_free(pq2);

    printf("test_merge passed\n");
    return 0;
}
