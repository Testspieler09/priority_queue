#include <stddef.h>
#include <stdbool.h>

#ifndef PRIORITY_QUEUE

typedef struct MinHeapNode {
    char priority;
    void *data;
} MinHeapNode;

typedef struct MinHeapPQ {
    MinHeapNode *first_element;
    size_t size;
    size_t capacity;
} MinHeapPQ;

MinHeapPQ *mh_new();
MinHeapPQ *mh_with_capacity(size_t capacity);

void mh_insert(MinHeapPQ *pq, void *data);
void *mh_extractMin(MinHeapPQ *pq);
bool mh_isEmpty(MinHeapPQ *pq);
// TODO: need to adjust signature, a specific element gets removed
void mh_remove(MinHeapPQ *pq);
void mh_decreaseKey(MinHeapPQ *pq);
MinHeapNode *mh_peek(MinHeapPQ *pq);
MinHeapPQ *mh_merge(MinHeapPQ *lhs, MinHeapPQ *rhs);

void mh_free(MinHeapPQ *pq);

// struct FibHeapNode {
//     void *data;
//     struct FibHeapNode *next;
// };
//
// struct FibHeapPQ {
//     void *root;
// };
// void fh_insert(FibHeapPQ *pq, void *data);
// void *fh_extractMin(FibHeapPQ *pq);
// bool fh_isEmpty(FibHeapPQ *pq);
// void fh_remove(FibHeapPQ *pq);
// void fh_decreaseKey(FibHeapPQ *pq);
// FibHeapPQ *fh_merge(FibHeapPQ *lhs, FibHeapPQ *rhs);

#endif // !PRIORITY_QUEUE
