#include <stdio.h>
#include <assert.h>
#include "../src/min_heap_pq.h"

int main(void) {
    MinHeapPQ *pq = mh_new();

    char *a = "A";
    char *b = "B";
    char *c = "C";

    mh_insert(pq, a, 5);
    mh_insert(pq, b, 2);
    mh_insert(pq, c, 8);

    // Peek should return B (priority 2)
    assert(mh_peek(pq)->data == b);

    // Extract min should follow priority order
    assert(mh_extractMin(pq) == b);
    assert(mh_extractMin(pq) == a);
    assert(mh_extractMin(pq) == c);

    // Now heap should be empty
    assert(mh_isEmpty(pq));

    mh_free(pq);

    printf("test_insert_extract passed\n");
    return 0;
}
