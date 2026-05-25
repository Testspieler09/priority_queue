#include <stddef.h>
#include <stdbool.h>

#ifndef FIB_HEAP_PRIORITY_QUEUE
#define FIB_HEAP_PRIORITY_QUEUE

/**
 * @struct FibHeapNode
 * @brief Represents a node in the Fibonacci heap priority queue.
 *
 * Nodes form a forest of heap-ordered trees. Siblings are linked in a
 * circular doubly-linked list via @c left / @c right, and each node
 * points to one arbitrary child in its own circular child list.
 */
typedef struct FibHeapNode {
    size_t priority;            /**< The priority value for heap ordering (lower = higher priority) */
    size_t degree;              /**< Number of children */
    bool marked;                /**< Whether this node has lost a child since becoming a non-root */

    struct FibHeapNode *parent; /**< Pointer to parent node, or NULL if this is a root */
    struct FibHeapNode *child;  /**< Pointer to one arbitrary child, or NULL if childless */
    struct FibHeapNode *left;   /**< Left sibling in circular doubly-linked list */
    struct FibHeapNode *right;  /**< Right sibling in circular doubly-linked list */

    void *data;                 /**< Pointer to user-owned data */
} FibHeapNode;

/**
 * @struct FibHeapPQ
 * @brief Fibonacci heap priority queue.
 *
 * Maintains a forest of heap-ordered trees. Provides O(1) amortized
 * insert, peek, decrease-key and merge, and O(log n) amortized extract-min.
 */
typedef struct FibHeapPQ {
    FibHeapNode *min; /**< Pointer to the node with the lowest priority, or NULL if empty and entry point into the circular root list, or NULL if empty */
    size_t size;                       /**< Total number of nodes in the heap */
} FibHeapPQ;

/**
 * @brief Allocates and initialises an empty Fibonacci heap.
 * @return Pointer to the new heap. Exits on allocation failure.
 */
FibHeapPQ *fh_new(void);

/**
 * @brief Inserts a new node with the given data and priority.
 * @param pq       The heap to insert into.
 * @param data     User-owned pointer stored in the node.
 * @param priority Priority value; lower values are extracted first.
 * @return Pointer to the newly created node (retain it for @c fh_decreaseKey / @c fh_remove).
 *         Exits on allocation failure.
 */
FibHeapNode *fh_insert(FibHeapPQ *pq, void *data, size_t priority);

/**
 * @brief Removes and returns the node with the lowest priority.
 * @param pq The heap to extract from.
 * @return Pointer to the extracted @c FibHeapNode, or NULL if the heap is empty.
 *         The caller is responsible for freeing the node and its data.
 */
void *fh_extractMin(FibHeapPQ *pq);

/**
 * @brief Returns whether the heap contains no nodes.
 * @param pq The heap to query.
 * @return @c true if empty, @c false otherwise.
 */
bool fh_isEmpty(FibHeapPQ *pq);

/**
 * @brief Removes an arbitrary node from the heap.
 * @param pq   The heap to remove from.
 * @param node The node to remove (must belong to @p pq).
 * @return Pointer to the removed @c FibHeapNode.
 *         The caller is responsible for freeing the node and its data.
 * @warning Implemented by decreasing the node's priority to 0 and calling
 *          @c fh_extractMin. This is incorrect if any node in the heap
 *          legitimately holds priority 0; prefer a signed priority type
 *          and @c INT64_MIN as a sentinel in that case.
 */
void *fh_remove(FibHeapPQ *pq, FibHeapNode *node);

/**
 * @brief Decreases the priority of an existing node.
 * @param pq           The heap that owns @p node.
 * @param node         The node to update (must belong to @p pq).
 * @param new_priority The new priority; must be <= the current priority.
 *                     The call is a no-op if @p new_priority is greater.
 */
void fh_decreaseKey(FibHeapPQ *pq, FibHeapNode *node, size_t new_priority);

/**
 * @brief Returns the minimum node without removing it.
 * @param pq The heap to peek at.
 * @return Pointer to the node with the lowest priority, or NULL if empty.
 */
FibHeapNode *fh_peek(FibHeapPQ *pq);

/**
 * @brief Merges two heaps into a new heap in O(1).
 * @param lhs The first heap.
 * @param rhs The second heap.
 * @return Pointer to a new @c FibHeapPQ containing all nodes from both heaps.
 *         Exits on allocation failure.
 * @warning This operation is destructive: the root lists of @p lhs and @p rhs
 *          are spliced directly into the new heap. Both source structs must be
 *          treated as invalid after this call — free them with @c free() (not
 *          @c fh_free()), as their nodes are now owned by the returned heap.
 */
FibHeapPQ *fh_merge(FibHeapPQ *lhs, FibHeapPQ *rhs);

/**
 * @brief Frees the heap and all of its nodes.
 * @param pq The heap to free.
 * @note Does not free @c node->data — the caller owns that memory.
 *       If the heap owns its data pointers, free them before calling this.
 */
void fh_free(FibHeapPQ *pq);

#endif // !FIB_HEAP_PRIORITY_QUEUE
