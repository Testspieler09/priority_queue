#ifndef FIB_HEAP_PRIORITY_QUEUE
#define FIB_HEAP_PRIORITY_QUEUE

typedef struct DoubleCircularLinkedListNode {
    void *data;
    struct DoubleCircularLinkedListNode *next;
    struct DoubleCircularLinkedListNode *prev;
} DoubleCircularLinkedListNode;

typedef struct DoubleCircularLinkedList {
    DoubleCircularLinkedListNode *current;
} DoubleCircularLinkedList;

#endif // !FIB_HEAP_PRIORITY_QUEUE
