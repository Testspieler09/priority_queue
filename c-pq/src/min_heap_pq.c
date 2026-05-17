#include "min_heap_pq.h"
#include "constants.h"
#include "helper.h"

#include <stdio.h>
#include <stdlib.h>

static inline void _double_capacity(MinHeapPQ *pq) {
    pq->capacity = pq->capacity == 0 ? 4 : pq->capacity * 2;
    void *new_first_element = realloc(
        pq->elements,
        pq->capacity * sizeof(MinHeapNode*)
    );

    if (new_first_element == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    pq->elements = new_first_element;
}

static inline void _swap_nodes_in_heap(MinHeapPQ *pq, size_t idx1, size_t idx2) {
    MinHeapNode *tmp = pq->elements[idx1];
    pq->elements[idx1] = pq->elements[idx2];
    pq->elements[idx2] = tmp;

    pq->elements[idx1]->heap_idx = idx1;
    pq->elements[idx2]->heap_idx = idx2;
}

static inline void _bubble_down(MinHeapPQ *pq, size_t i) {
    size_t smallest = i;

    for (;;) {
        size_t lh_idx = (2 * i) + 1;
        size_t rh_idx = (2 * i) + 2;

        if (lh_idx < pq->size
            && pq->elements[lh_idx]->priority < pq->elements[smallest]->priority
        ) {
            smallest = lh_idx;
        }

        if (rh_idx < pq->size
            && pq->elements[rh_idx]->priority < pq->elements[smallest]->priority
        ) {
            smallest = rh_idx;
        }

        if (smallest != i) {
            _swap_nodes_in_heap(pq, i, smallest);
            i = smallest;
        } else {
            break;
        }
    }
}

MinHeapPQ *mh_new(void) {
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

    MinHeapNode **elements = malloc(capacity * sizeof(MinHeapNode*));

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
        size_t parent_idx = (i - 1) / 2;
        if (pq->elements[parent_idx]->priority > new_node->priority) {
            _swap_nodes_in_heap(pq, parent_idx, i);
            i = parent_idx;
        } else {
            break;
        }
    }
    pq->size++;

    return new_node;
}

void *mh_extractMin(MinHeapPQ *pq) {
    if (mh_isEmpty(pq)) return NULL;

    MinHeapNode *min_node = pq->elements[0];
    void *data = min_node->data;

    pq->size--;
    if (pq->size > 0) {
        pq->elements[0] = pq->elements[pq->size];
        pq->elements[0]->heap_idx = 0;
        _bubble_down(pq, 0);
    }

    free(min_node);   // now safe to free the original min
    return data;
}

bool mh_isEmpty(MinHeapPQ *pq) { return pq->size == 0; }

void *mh_remove(MinHeapPQ *pq, MinHeapNode *node_ptr) {
    size_t node_idx = node_ptr->heap_idx;
    void *data = node_ptr->data;
    free(node_ptr);
    pq->size--;

    if (node_idx < pq->size) {
        pq->elements[node_idx] = pq->elements[pq->size];
        pq->elements[node_idx]->heap_idx = node_idx;
        _bubble_down(pq, node_idx);
    }
    return data;
}

void mh_decreaseKey(MinHeapPQ *pq, MinHeapNode *node_ptr, size_t new_priority) {
    node_ptr->priority = new_priority;

    size_t i = node_ptr->heap_idx;
    while (i > 0) {
        size_t parent_idx = (i - 1) / 2;
        if (pq->elements[parent_idx]->priority > pq->elements[i]->priority) {
            _swap_nodes_in_heap(pq, parent_idx, i);
            i = parent_idx;
        } else {
            break;
        }
    }
}

MinHeapNode *mh_peek(MinHeapPQ *pq) { return pq->elements[0]; }

MinHeapPQ *mh_merge(MinHeapPQ *lhs, MinHeapPQ *rhs) {
    MinHeapPQ *new_pq = malloc(sizeof(MinHeapPQ));
    if (new_pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    size_t new_size = lhs->size + rhs->size;
    size_t new_capacity = next_power_of_two(new_size);

    MinHeapNode **elements = malloc(new_capacity * sizeof(MinHeapNode*));
    if (elements == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    for (size_t i = 0; i < lhs->size; i++) {
        elements[i] = lhs->elements[i];
        elements[i]->heap_idx = i;
    }

    for (size_t i = 0; i < rhs->size; i++) {
        elements[lhs->size + i] = rhs->elements[i];
        elements[lhs->size + i]->heap_idx = lhs->size + i;
    }

    new_pq->elements = elements;
    new_pq->size = new_size;
    new_pq->capacity = new_capacity;

    if (new_size <= 1) {
        return new_pq;
    }

    for (ssize_t i = (new_pq->size / 2) - 1; i >= 0; i--) {
        _bubble_down(new_pq, i);
    }

    return new_pq;
}

void mh_free(MinHeapPQ *pq) {
    for (ssize_t i = pq->size - 1; i >= 0; i--) {
        free(pq->elements[i]);
    }
    free(pq->elements);
    free(pq);
}
