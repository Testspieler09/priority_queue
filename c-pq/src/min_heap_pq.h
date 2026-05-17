#include <stddef.h>
#include <stdbool.h>

#ifndef MIN_HEAP_PRIORITY_QUEUE
#define MIN_HEAP_PRIORITY_QUEUE

/**
 * @struct MinHeapNode
 * @brief Represents a node in the min-heap priority queue.
 *
 * Each node stores a priority, its index in the heap array, and
 * a pointer to user data.
 */
typedef struct MinHeapNode {
    size_t priority;   /**< The priority value for heap ordering */
    size_t heap_idx;   /**< Index of this node in the heap array */
    void *data;        /**< Pointer to the user data */
} MinHeapNode;

/**
 * @struct MinHeapPQ
 * @brief Min-heap priority queue.
 *
 * Maintains a dynamic array of MinHeapNode pointers and the current
 * size and capacity of the heap.
 */
typedef struct MinHeapPQ {
    MinHeapNode **elements; /**< Array of pointers to heap nodes */
    size_t size;            /**< Number of elements currently in the heap */
    size_t capacity;        /**< Maximum capacity of the heap array */
} MinHeapPQ;

/**
 * @brief Creates a new empty min-heap priority queue with default capacity.
 *
 * @return MinHeapPQ* Pointer to the newly allocated priority queue.
 */
MinHeapPQ *mh_new(void);

/**
 * @brief Creates a new empty min-heap priority queue with a specific capacity.
 *
 * @param capacity Initial capacity of the heap.
 * @return MinHeapPQ* Pointer to the newly allocated priority queue.
 */
MinHeapPQ *mh_with_capacity(size_t capacity);

/**
 * @brief Inserts a new element into the min-heap priority queue.
 *
 * Allocates a new node and places it in the correct position in the heap
 * to maintain the heap property.
 *
 * @param pq Pointer to the priority queue.
 * @param data Pointer to the user data to store.
 * @param priority Priority value for the new node.
 * @return MinHeapNode* Pointer to the newly inserted node.
 */
MinHeapNode *mh_insert(MinHeapPQ *pq, void *data, size_t priority);

/**
 * @brief Extracts and removes the node with the minimum priority from the heap.
 *
 * Restores the heap property after removal.
 *
 * @param pq Pointer to the priority queue.
 * @return void* Pointer to the user data stored in the extracted node.
 */
void *mh_extractMin(MinHeapPQ *pq);

/**
 * @brief Checks if the priority queue is empty.
 *
 * @param pq Pointer to the priority queue.
 * @return true if the queue is empty, false otherwise.
 */
bool mh_isEmpty(MinHeapPQ *pq);

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
void *mh_remove(MinHeapPQ *pq, MinHeapNode *node_ptr);

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
void mh_decreaseKey(MinHeapPQ *pq, MinHeapNode *node_ptr, size_t new_priority);

/**
 * @brief Returns the node with the minimum priority without removing it.
 *
 * @param pq Pointer to the min-heap priority queue.
 * @return MinHeapNode* Pointer to the node with the minimum priority (root).
 */
MinHeapNode *mh_peek(MinHeapPQ *pq);

/**
 * @brief Merges two min-heaps into a new min-heap.
 *
 * Allocates a new heap, copies all elements from both lhs and rhs heaps,
 * and performs a heapify operation to maintain heap order.
 *
 * @param lhs Pointer to the first min-heap.
 * @param rhs Pointer to the second min-heap.
 * @return MinHeapPQ* Pointer to the newly created merged heap.
 */
MinHeapPQ *mh_merge(MinHeapPQ *lhs, MinHeapPQ *rhs);

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
void mh_free(MinHeapPQ *pq);

#endif // !MIN_HEAP_PRIORITY_QUEUE
