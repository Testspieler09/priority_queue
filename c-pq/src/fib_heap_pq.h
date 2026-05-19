#include <stddef.h>
#include <stdbool.h>

#ifndef FIB_HEAP_PRIORITY_QUEUE
#define FIB_HEAP_PRIORITY_QUEUE

// TODO: documentation

typedef struct FibHeapNode {
    size_t priority;
    size_t degree;
    bool marked;

    struct FibHeapNode* parent;
    struct FibHeapNode* child;
    struct FibHeapNode* left;
    struct FibHeapNode* right;

    void *data;
} FibHeapNode;

typedef struct FibHeapPQ {
    FibHeapNode *min;
    FibHeapNode *root_list_first_node;
    size_t size;
} FibHeapPQ;

FibHeapPQ *fh_new(void);

FibHeapNode *fh_insert(FibHeapPQ *pq, void *data, size_t priority);

void *fh_extractMin(FibHeapPQ *pq);

bool fh_isEmpty(FibHeapPQ *pq);

void *fh_remove(FibHeapPQ *pq, FibHeapNode *node_ptr);

void fh_decreaseKey(FibHeapPQ *pq, FibHeapNode *node_ptr, size_t new_priority);

FibHeapNode *fh_peek(FibHeapPQ *pq);

FibHeapPQ *fh_merge(FibHeapPQ *lhs, FibHeapPQ *rhs);

void fh_free(FibHeapPQ *pq);

#endif // !FIB_HEAP_PRIORITY_QUEUE
