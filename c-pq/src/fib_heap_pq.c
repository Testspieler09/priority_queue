#include "fib_heap_pq.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

FibHeapPQ *fh_new(void) {
    FibHeapPQ *new_pq = malloc(sizeof(FibHeapPQ));
    if (new_pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    new_pq->min = NULL;
    new_pq->root_list_first_node = NULL;
    new_pq->size = 0;

    return new_pq;
}

FibHeapNode *fh_insert(FibHeapPQ *pq, void *data, size_t priority) {
    FibHeapNode *new_node = malloc(sizeof(FibHeapNode));
    if (new_node == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    new_node->priority = priority;
    new_node->degree = 0;
    new_node->marked = false;

    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->left = new_node;
    new_node->right = new_node;

    if (pq->root_list_first_node == NULL) {
        pq->root_list_first_node = new_node;
    } else {
        new_node->right = pq->root_list_first_node;
        new_node->left = pq->root_list_first_node->left;
        pq->root_list_first_node->left->right = new_node;
        pq->root_list_first_node->left = new_node;
    }

    new_node->data = data;

    if (pq->min == NULL || pq->min->priority > priority) {
        pq->min = new_node;
    }

    pq->size++;

    return new_node;
}

void *fh_extractMin(FibHeapPQ *pq) {
    pq->size--;
}

bool fh_isEmpty(FibHeapPQ *pq) { return pq->size == 0; }

void *fh_remove(FibHeapPQ *pq, FibHeapNode *node_ptr) {
    // TODO: find element
    // FIX: this does not work if the min is 0 though.
    if (pq->min != node_ptr) {
        fh_decreaseKey(pq, node_ptr, 0);
    }

    return fh_extractMin(pq);
}

void fh_decreaseKey(FibHeapPQ *pq, FibHeapNode *node_ptr, size_t new_priority) {}

FibHeapNode *fh_peek(FibHeapPQ *pq) { return pq->min; }

// FIX: this mutates the existing lhs and rhs which should not happen
FibHeapPQ *fh_merge(FibHeapPQ *lhs, FibHeapPQ *rhs) {
    FibHeapPQ *new_pq = malloc(sizeof(FibHeapPQ));
    if (new_pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    new_pq->min = lhs->min < rhs->min ? lhs->min : rhs->min;
    new_pq->root_list_first_node = lhs->root_list_first_node;
    new_pq->size = lhs->size + rhs->size;

    if (new_pq->root_list_first_node == NULL) {
        new_pq->root_list_first_node = rhs->root_list_first_node;
    } else {
        rhs->root_list_first_node->right = new_pq->root_list_first_node;
        rhs->root_list_first_node->left = new_pq->root_list_first_node->left;
        new_pq->root_list_first_node->left->right = rhs->root_list_first_node;
        new_pq->root_list_first_node->left = rhs->root_list_first_node->left;
    }

    return new_pq;
}

void fh_free(FibHeapPQ *pq) {
    // TODO: for each node free all its pointer allocated on the heap
    // probably recursive, as i need to treverse the tree
    // depth first search and then delete neighbors -> next layer above ...

    free(pq);
}
