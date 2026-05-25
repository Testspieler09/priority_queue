#include "fib_heap_pq.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void _merge_with_root_list(FibHeapPQ *pq, FibHeapNode *node) {
    if (pq->min == NULL) {
        node->left = node;
        node->right = node;
        pq->min = node;
    } else {
        node->right = pq->min;
        node->left = pq->min->left;

        pq->min->left->right = node;
        pq->min->left = node;

        node->right->left = node;
    }

    if (node->priority < pq->min->priority) {
        pq->min = node;
    }
}

void _remove_from_child_list(FibHeapNode *parent, FibHeapNode *node) {
    if (parent->child == node) {
        parent->child = (node->right == node) ? NULL : node->right;
    }
    node->left->right = node->right;
    node->right->left = node->left;
    node->left = node;
    node->right = node;
    parent->degree--;
}

void _remove_from_root_list(FibHeapPQ *pq, FibHeapNode *node) {
    if (node->right == node) {
        pq->min = NULL;
    } else {
        if (pq->min == node) {
            pq->min = node->right;
        }

        node->left->right = node->right;
        node->right->left = node->left;
    }

    node->left = node;
    node->right = node;
}

void _cut(FibHeapPQ *pq, FibHeapNode *l_node, FibHeapNode *r_node) {
    _remove_from_child_list(r_node, l_node);
    _merge_with_root_list(pq, l_node);
    l_node->parent = NULL;
    l_node->marked = false;
}

void _cascading_cut(FibHeapPQ *pq, FibHeapNode *node) {
    FibHeapNode *ref_node = node->parent;
    if (ref_node != NULL) {
        if (!node->marked) {
            node->marked = true;
        } else {
            _cut(pq, node, ref_node);
            _cascading_cut(pq, ref_node);
        }
    }
}

void _heap_link(FibHeapPQ *pq, FibHeapNode *l_node, FibHeapNode *r_node) {
    _remove_from_root_list(pq, l_node);
    l_node->left = l_node;
    l_node->right = l_node;
    l_node->parent = r_node;
    l_node->marked = false;

    if (r_node->child == NULL) {
        r_node->child = l_node;
    } else {
        l_node->right = r_node->child;
        l_node->left = r_node->child->left;
        r_node->child->left->right = l_node;
        r_node->child->left = l_node;
    }
    r_node->degree++;
}

void _consolidate(FibHeapPQ *pq) {
    if (pq->min == NULL || pq->min->right == pq->min) {
        return;
    }

    size_t max_degree = log2(pq->size) * 2 + 1;
    FibHeapNode *A[max_degree];
    memset(A, 0, sizeof(A));

    size_t root_count = 0;
    FibHeapNode *w = pq->min;
    do { root_count++; w = w->right; } while (w != pq->min);

    FibHeapNode *roots[root_count];
    w = pq->min;
    for (size_t i = 0; i < root_count; i++) {
        roots[i] = w;
        w = w->right;
    }

    for (size_t i = 0; i < root_count; i++) {
        FibHeapNode *x = roots[i];
        size_t d = x->degree;
        while (A[d] != NULL) {
            FibHeapNode *y = A[d];
            if (x->priority > y->priority) {
                FibHeapNode *tmp = x; x = y; y = tmp;
            }
            _heap_link(pq, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }

    pq->min = NULL;
    for (size_t i = 0; i < max_degree; i++) {
        if (A[i] == NULL) {
            continue;
        }
        A[i]->left = A[i]->right = A[i];
        if (pq->min == NULL) {
            pq->min = A[i];
        } else {
            A[i]->right = pq->min->right;
            A[i]->left = pq->min;
            pq->min->right->left = A[i];
            pq->min->right = A[i];
            if (A[i]->priority < pq->min->priority) {
                pq->min = A[i];
            }
        }
    }
}

static void _free_node_list(FibHeapNode *start) {
    if (start == NULL) return;
    FibHeapNode *cur = start;
    do {
        FibHeapNode *next = cur->right;
        _free_node_list(cur->child);
        free(cur);
        cur = next;
    } while (cur != start);
}

FibHeapPQ *fh_new(void) {
    FibHeapPQ *new_pq = malloc(sizeof(FibHeapPQ));
    if (new_pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    new_pq->min = NULL;
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

    _merge_with_root_list(pq, new_node);

    new_node->data = data;

    pq->size++;

    return new_node;
}

void *fh_extractMin(FibHeapPQ *pq) {
    FibHeapNode *ref_node = pq->min;
    if (ref_node != NULL) {
        FibHeapNode *child = ref_node->child;
        if (child != NULL) {
            FibHeapNode *start = child;
            FibHeapNode *next;

            do {
                next = child->right;

                child->left = child;
                child->right = child;

                _merge_with_root_list(pq, child);

                child->parent = NULL;
                child->marked = false;
                child = next;
            } while (child != start);
        }

        bool singleton = (ref_node->right == ref_node);
        FibHeapNode *next_root = ref_node->right;

        _remove_from_root_list(pq, ref_node);

        if (singleton) {
            pq->min = NULL;
        } else {
            pq->min = next_root;
            _consolidate(pq);
        }

        pq->size--;
    } else {
        return NULL;
    }

    void *data = ref_node->data;
    free(ref_node);
    return data;
}

bool fh_isEmpty(FibHeapPQ *pq) { return pq->size == 0; }

void *fh_remove(FibHeapPQ *pq, FibHeapNode *node) {
    node->priority = 0;

    FibHeapNode *parent = node->parent;
    if (parent != NULL) {
        _cut(pq, node, parent);
        _cascading_cut(pq, parent);
    }
    pq->min = node;
    return fh_extractMin(pq);
}

void fh_decreaseKey(FibHeapPQ *pq, FibHeapNode *node, size_t new_priority) {
    if (new_priority > node->priority) {
        return;
    }

    node->priority = new_priority;
    FibHeapNode *ref_node = node->parent;

    if (ref_node != NULL && node->priority < ref_node->priority) {
        _cut(pq, node, ref_node);
        _cascading_cut(pq, ref_node);
    }
    if (node->priority < pq->min->priority) {
        pq->min = node;
    }
}

FibHeapNode *fh_peek(FibHeapPQ *pq) { return pq->min; }

FibHeapPQ *fh_merge(FibHeapPQ *lhs, FibHeapPQ *rhs) {
    FibHeapPQ *new_pq = malloc(sizeof(FibHeapPQ));
    if (new_pq == NULL) {
        printf("%s", ALLOCATION_ERROR);
        exit(1);
    }

    // HACK: the new_pq->min value will be set in the _merge_with_root_list function
    new_pq->min = lhs->min;
    new_pq->size = lhs->size + rhs->size;

    if (lhs->min == NULL || rhs->min == NULL) {
        new_pq->min = lhs->min ? rhs->min : lhs->min;
        return new_pq;
    }

    // Splice the two circular lists together directly
    FibHeapNode *lhs_last = lhs->min->left;
    FibHeapNode *rhs_last = rhs->min->left;

    lhs_last->right = rhs->min;
    rhs->min->left = lhs_last;
    rhs_last->right = new_pq->min;
    new_pq->min->left = rhs_last;

    if (rhs->min != NULL &&
        (new_pq->min == NULL || rhs->min->priority < new_pq->min->priority)) {
        new_pq->min = rhs->min;
    }

    return new_pq;
}

void fh_free(FibHeapPQ *pq) {
    _free_node_list(pq->min);
    free(pq);
}
