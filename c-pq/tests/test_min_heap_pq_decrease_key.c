#include <stdio.h>
#include <assert.h>
#include "../src/min_heap_pq.h"

int main(void) {
    MinHeapPQ *pq = mh_new();

    char *x = "X";
    char *y = "Y";

    MinHeapNode *x_node = mh_insert(pq, x, 10);
    mh_insert(pq, y, 5);

    // Initially, min is Y
    assert(mh_peek(pq)->data == y);

    // Increase X should be ignored
    mh_decreaseKey(pq, x_node, 12);
    assert(mh_peek(pq)->data == y);

    // Decrease X priority below Y
    mh_decreaseKey(pq, x_node, 2);
    assert(mh_peek(pq)->data == x);

    mh_free(pq);

    printf("test_decrease_key passed\n");
    return 0;
}
