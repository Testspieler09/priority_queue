#include <stdio.h>
#include <assert.h>
#include "../src/fib_heap_pq.h"

int main(void) {
    FibHeapPQ *pq = fh_new();

    char *a = "A";
    char *b = "B";
    char *c = "C";

    fh_insert(pq, a, 5);
    fh_insert(pq, b, 2);
    fh_insert(pq, c, 8);

    // Peek should return B (priority 2)
    assert(fh_peek(pq)->data == b);

    // Extract min should follow priority order
    assert(fh_extractMin(pq) == b);
    assert(fh_extractMin(pq) == a);
    assert(fh_extractMin(pq) == c);

    // Now heap should be empty
    assert(fh_isEmpty(pq));

    fh_free(pq);

    printf("test_insert_extract passed\n");
    return 0;
}
