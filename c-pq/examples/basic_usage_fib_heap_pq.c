#include <stdio.h>
#include "../src/fib_heap_pq.h"

int main(void) {
    FibHeapPQ *pq = fh_new();

    char *alice = "Alice";
    char *bob = "Bob";
    char *charlie = "Charlie";

    FibHeapNode *alice_node =
        fh_insert(pq, alice, 10);

    FibHeapNode *bob_node =
        fh_insert(pq, bob, 3);

    FibHeapNode *charlie_node =
        fh_insert(pq, charlie, 7);

    printf("Initial minimum: %s\n",
           (char *)fh_peek(pq)->data);

    /*
     * Charlie priority:
     * 7 -> 1
     */
    fh_decreaseKey(pq, charlie_node, 1);

    printf("After decreaseKey: %s\n",
           (char *)fh_peek(pq)->data);

    /*
     * Remove Bob entirely
     */
    fh_remove(pq, bob_node);

    printf("\nExtracting elements:\n");

    while (!fh_isEmpty(pq)) {
        char *name = (char *)fh_extractMin(pq);

        printf("  %s\n", name);
    }

    fh_free(pq);

    return 0;
}
