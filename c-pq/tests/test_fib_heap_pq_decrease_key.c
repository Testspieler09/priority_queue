#include <stdio.h>
#include <assert.h>
#include "../src/fib_heap_pq.h"

int main(void) {
    FibHeapPQ *pq = fh_new();

    char *x = "X";
    char *y = "Y";

    FibHeapNode *x_node = fh_insert(pq, x, 10);
    fh_insert(pq, y, 5);

    // Initially, min is Y
    assert(fh_peek(pq)->data == y);

    // Increase X should be ignored
    fh_decreaseKey(pq, x_node, 12);
    assert(fh_peek(pq)->data == y);

    // Decrease X priority below Y
    fh_decreaseKey(pq, x_node, 2);
    assert(fh_peek(pq)->data == x);

    fh_free(pq);

    printf("test_decrease_key passed\n");
    return 0;
}
