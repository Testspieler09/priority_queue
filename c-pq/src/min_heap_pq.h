#include <stddef.h>
#include <stdbool.h>

#ifndef MIN_HEAP_PRIORITY_QUEUE

typedef struct MinHeapNode {
    size_t priority;
    // size_t heap_idx;
    void *data;
} MinHeapNode;

typedef struct MinHeapPQ {
    MinHeapNode *first_element;
    size_t size;
    size_t capacity;
} MinHeapPQ;

MinHeapPQ *mh_new();
MinHeapPQ *mh_with_capacity(size_t capacity);

MinHeapNode *mh_insert(MinHeapPQ *pq, void *data, size_t priority);
void *mh_extractMin(MinHeapPQ *pq);
bool mh_isEmpty(MinHeapPQ *pq);
void *mh_remove(MinHeapPQ *pq, MinHeapNode *node_ptr);
void mh_decreaseKey(MinHeapPQ *pq, MinHeapNode *node_ptr, size_t new_priority);
MinHeapNode *mh_peek(MinHeapPQ *pq);
MinHeapPQ *mh_merge(MinHeapPQ *lhs, MinHeapPQ *rhs);

/**
 * This does not need to be called on modern operating systems if it is at
 * the end of the program, as it will free the occupied memory automatically
 * and thus it would only create more overhead.
 *
 * NOTE: This does not free the data itself as the priority queue does not own
 * the data. It only frees the heap nodes and the priority queue itself.
 */
void mh_free(MinHeapPQ *pq);

#endif // !MIN_HEAP_PRIORITY_QUEUE
