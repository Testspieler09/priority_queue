#include <stddef.h>
#include <stdbool.h>

#ifndef FIB_HEAP_PRIORITY_QUEUE
#define FIB_HEAP_PRIORITY_QUEUE

typedef struct FibHeapNode {
    size_t key;
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
    FibHeapNode **root_list;
    size_t size;
    size_t capacity;
} FibHeapPQ;

/**
 * @brief Creates a new empty min-heap priority queue with default capacity.
 *
 * @return FibHeapPQ* Pointer to the newly allocated priority queue.
 */
FibHeapPQ *mh_new(void);

/**
 * @brief Creates a new empty min-heap priority queue with a specific capacity.
 *
 * @param capacity Initial capacity of the heap.
 * @return FibHeapPQ* Pointer to the newly allocated priority queue.
 */
FibHeapPQ *mh_with_capacity(size_t capacity);

/**
 * @brief Inserts a new element into the min-heap priority queue.
 *
 * Allocates a new node and places it in the correct position in the heap
 * to maintain the heap property.
 *
 * @param pq Pointer to the priority queue.
 * @param data Pointer to the user data to store.
 * @param priority Priority value for the new node.
 * @return FibHeapNode* Pointer to the newly inserted node.
 */
FibHeapNode *mh_insert(FibHeapPQ *pq, void *data, size_t priority);

/**
 * @brief Extracts and removes the node with the minimum priority from the heap.
 *
 * Restores the heap property after removal.
 *
 * @param pq Pointer to the priority queue.
 * @return void* Pointer to the user data stored in the extracted node.
 */
void *mh_extractMin(FibHeapPQ *pq);

/**
 * @brief Checks if the priority queue is empty.
 *
 * @param pq Pointer to the priority queue.
 * @return true if the queue is empty, false otherwise.
 */
bool mh_isEmpty(FibHeapPQ *pq);

/**
 * @brief Removes a specific node from the min-heap.
 *
 * Removes the given node from the heap, restores heap property,
 * and returns the user data stored in the node.
 *
 * @param pq Pointer to the min-heap priority queue.
 * @param node_ptr Pointer to the node to remove.
 * @return void* The user data stored in the removed node.
 */
void *mh_remove(FibHeapPQ *pq, FibHeapNode *node_ptr);

/**
 * @brief Decreases the priority of a node in the min-heap.
 *
 * Updates the priority of the specified node to a new, lower value
 * and restores the min-heap property.
 *
 * @param pq Pointer to the min-heap priority queue.
 * @param node_ptr Pointer to the node whose priority is decreased.
 * @param new_priority The new lower priority value.
 */
void mh_decreaseKey(FibHeapPQ *pq, FibHeapNode *node_ptr, size_t new_priority);

/**
 * @brief Returns the node with the minimum priority without removing it.
 *
 * @param pq Pointer to the min-heap priority queue.
 * @return FibHeapNode* Pointer to the node with the minimum priority (root).
 */
FibHeapNode *mh_peek(FibHeapPQ *pq);

/**
 * @brief Merges two min-heaps into a new min-heap.
 *
 * Allocates a new heap, copies all elements from both lhs and rhs heaps,
 * and performs a heapify operation to maintain heap order.
 *
 * @param lhs Pointer to the first min-heap.
 * @param rhs Pointer to the second min-heap.
 * @return FibHeapPQ* Pointer to the newly created merged heap.
 */
FibHeapPQ *mh_merge(FibHeapPQ *lhs, FibHeapPQ *rhs);

/**
 * @brief Frees the memory used by the priority queue and its nodes.
 *
 * This function does not free the user data stored in the nodes, as
 * the priority queue does not own the data. It only frees the heap nodes
 * and the priority queue itself.
 *
 * NOTE: This is optional at program termination, as modern operating
 * systems automatically free process memory.
 *
 * @param pq Pointer to the priority queue to free.
 */
void mh_free(FibHeapPQ *pq);

#endif // !FIB_HEAP_PRIORITY_QUEUE
