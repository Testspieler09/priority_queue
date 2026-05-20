#include <stdio.h>
#include <assert.h>
#include "../src/fib_heap_pq.h"

int main(void) {
    FibHeapPQ *pq = fh_new();

    char *a = "A";
    char *b = "B";
    char *c = "C";

    FibHeapNode *a_node = fh_insert(pq, a, 1);
    FibHeapNode *b_node = fh_insert(pq, b, 2);
    fh_insert(pq, c, 3);

    // Remove middle element
    fh_remove(pq, b_node);

    // Check remaining order
    assert(fh_extractMin(pq) == a);
    assert(fh_extractMin(pq) == c);
    assert(fh_isEmpty(pq));

    fh_free(pq);

    printf("test_remove passed\n");
    return 0;
}
