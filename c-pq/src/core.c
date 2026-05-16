#include "core.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void _double_capacity(MinHeapPQ *pq) {
    pq->capacity *= 2;
    void *new_first_element = realloc(
        pq->first_element,
        pq->capacity * sizeof(MinHeapNode)
    );

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

MinHeapNode *mh_insert(MinHeapPQ *pq, void *data, size_t priority) {
    if (pq->size == pq->capacity) {
        _double_capacity(pq);
    }

    MinHeapNode *new_node = malloc(sizeof(MinHeapNode));
    if (new_node == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    void *append_pos = pq->first_element + pq->size;
    new_node->data = data;
    new_node->priority = priority;

    // TODO: reconcile the heap
    // as the heap is already sorted we only need to check the parent node and
    // switch if needed -> continue else return

    return new_node;
}

void *mh_extractMin(MinHeapPQ *pq) {
    MinHeapNode *data_ptr = pq->first_element->data;
    free(pq->first_element);

    // TODO: reconcile the heap

    return data_ptr;
}

bool mh_isEmpty(MinHeapPQ *pq) { return pq->size == 0; }

void mh_remove(MinHeapPQ *pq, MinHeapNode *node_ptr) {
    // TODO: find node index
    free(node_ptr);
    // TODO: and reconcile
}

void mh_decreaseKey(MinHeapPQ *pq, MinHeapNode *node_ptr, size_t new_priority) {
    // TODO: find node index
    node_ptr->priority = new_priority;
    // TODO: reconcilde heap
}

MinHeapNode *mh_peek(MinHeapPQ *pq) { return pq->first_element; }

MinHeapPQ *mh_merge(MinHeapPQ *lhs, MinHeapPQ *rhs) {
    // TODO: new min heap with the capacity of the sum of the sizes or
    // capacities.
    // then insert all the data that we already have. I.e. a build operation
    return NULL;
}

void mh_free(MinHeapPQ *pq) {
    for (size_t i = pq->size - 1; i >= 0; i--) {
        free(pq->first_element + i);
    }

    free(pq);
}
