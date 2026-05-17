#include <stdio.h>
#include "../src/min_heap_pq.h"

int main(void) {
    MinHeapPQ *pq = mh_new();

    char *alice = "Alice";
    char *bob = "Bob";
    char *charlie = "Charlie";

    MinHeapNode *alice_node =
        mh_insert(pq, alice, 10);

    MinHeapNode *bob_node =
        mh_insert(pq, bob, 3);

    MinHeapNode *charlie_node =
        mh_insert(pq, charlie, 7);

    printf("Initial minimum: %s\n",
           (char *)mh_peek(pq)->data);

    /*
     * Charlie priority:
     * 7 -> 1
     */
    mh_decreaseKey(pq, charlie_node, 1);

    printf("After decreaseKey: %s\n",
           (char *)mh_peek(pq)->data);

    /*
     * Remove Bob entirely
     */
    mh_remove(pq, bob_node);

    printf("\nExtracting elements:\n");

    while (!mh_isEmpty(pq)) {
        char *name = (char *)mh_extractMin(pq);

        printf("  %s\n", name);
    }

    mh_free(pq);

    return 0;
}
