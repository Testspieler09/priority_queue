#include "core.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void _double_capacity(MinHeapPQ *pq) {
    pq->capacity *= 2;
    void *new_first_element = realloc(pq->first_element, pq->capacity * sizeof(MinHeapNode));

    if (new_first_element == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    pq->first_element = new_first_element;
}


MinHeapPQ *mh_new() {
    MinHeapPQ *pq = malloc(sizeof(MinHeapPQ));

    if (pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    pq->first_element = NULL;
    pq->size = 0;
    pq->capacity = 0;

    return pq;
}

MinHeapPQ *mh_with_capacity(size_t capacity) {
    MinHeapPQ *pq = malloc(sizeof(MinHeapPQ));

    if (pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    MinHeapNode *dyn_arr = malloc(capacity * sizeof(MinHeapNode));

    if (dyn_arr == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    pq->first_element = dyn_arr;
    pq->size = 0;
    pq->capacity = capacity;

    return pq;
}

void mh_insert(MinHeapPQ *pq, void *data) {

}

void *mh_extractMin(MinHeapPQ *pq) {
    // TODO: also removes the element
    return pq->first_element;
}

bool mh_isEmpty(MinHeapPQ *pq) { return pq->size == 0; }

// TODO: need to adjust signature, a specific element gets removed
void mh_remove(MinHeapPQ *pq) {

}

void mh_decreaseKey(MinHeapPQ *pq) {

}

MinHeapNode *mh_peek(MinHeapPQ *pq) { return pq->first_element; }

MinHeapPQ *mh_merge(MinHeapPQ *lhs, MinHeapPQ *rhs) {
    // TODO: new min heap with the capacity of the sum of the sizes or
    // capacities.
    // then insert all the data that we already have. I.e. a build operation
    return NULL;
}

void mh_free(MinHeapPQ *pq) {
    // TODO: free not only the heap itself but also the elements in it.
    // This does not need to be called on modern operating systems if it is at
    // the end of the program, as it will free the occupied memory automatically
    // and thus it would only create more overhead.
}
