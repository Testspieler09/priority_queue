#include <stdio.h>
#include <assert.h>
#include "../src/min_heap_pq.h"

int main(void) {
    MinHeapPQ *pq = mh_new();

    char *a = "A";
    char *b = "B";
    char *c = "C";

    MinHeapNode *a_node = mh_insert(pq, a, 1);
    MinHeapNode *b_node = mh_insert(pq, b, 2);
    mh_insert(pq, c, 3);

    // Remove middle element
    mh_remove(pq, b_node);

    // Check remaining order
    assert(mh_extractMin(pq) == a);
    assert(mh_extractMin(pq) == c);
    assert(mh_isEmpty(pq));

    mh_free(pq);

    printf("test_remove passed\n");
    return 0;
}
