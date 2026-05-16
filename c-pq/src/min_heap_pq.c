#include "min_heap_pq.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>

// NOTE: math for reconcile
// Parent node = floor((i-1) / 2)
// left child node = 2i + 1
// right child node = 2i + 2

void _double_capacity(MinHeapPQ *pq) {
    pq->capacity *= 2;
    void *new_first_element = realloc(
        pq->elements,
        pq->capacity * sizeof(MinHeapNode)
    );

    if (new_first_element == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    pq->elements = new_first_element;
}

void _swap(MinHeapNode *lhs, MinHeapNode *rhs) {
    MinHeapNode temp = *lhs;
    *lhs = *rhs;
    lhs->heap_idx = rhs->heap_idx;
    *rhs = temp;
    rhs->heap_idx = temp.heap_idx;
}

MinHeapPQ *mh_new() {
    MinHeapPQ *pq = malloc(sizeof(MinHeapPQ));

    if (pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    pq->elements = NULL;
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

    MinHeapNode **elements = malloc(capacity * sizeof(MinHeapNode));

    if (elements == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    pq->elements = elements;
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

    pq->elements[pq->size] = new_node;

    new_node->priority = priority;
    new_node->heap_idx = pq->size;
    new_node->data = data;

    size_t i = pq->size;
    while (i > 0) {
        MinHeapNode *parent = pq->elements[(i - 1) / 2];
        if (parent->priority > priority) {
            _swap(parent, new_node);
        } else {
            break;
        }
    }

    return new_node;
}

void *mh_extractMin(MinHeapPQ *pq) {
    if (!mh_isEmpty(pq)) {
        return NULL;
    }

    MinHeapNode *data_ptr = pq->elements[0]->data;
    free(pq->elements);

    // TODO: reconcile the heap

    return data_ptr;
}

bool mh_isEmpty(MinHeapPQ *pq) { return pq->size == 0; }

void *mh_remove(MinHeapPQ *pq, MinHeapNode *node_ptr) {
    // TODO: find node index
    void *data = node_ptr->data;
    free(node_ptr);
    // TODO: and reconcile

    return data;
}

void mh_decreaseKey(MinHeapPQ *pq, MinHeapNode *node_ptr, size_t new_priority) {
    // TODO: find node index
    node_ptr->priority = new_priority;
    // TODO: reconcilde heap
}

MinHeapNode *mh_peek(MinHeapPQ *pq) { return pq->elements[0]; }

MinHeapPQ *mh_merge(MinHeapPQ *lhs, MinHeapPQ *rhs) {
    // TODO: new min heap with the capacity of the sum of the sizes or
    // capacities.
    // then insert all the data that we already have. I.e. a build operation
    return NULL;
}

void mh_free(MinHeapPQ *pq) {
    for (size_t i = pq->size - 1; i >= 0; i--) {
        free(pq->elements[i]);
    }
    free(pq->elements);
    free(pq);
}
