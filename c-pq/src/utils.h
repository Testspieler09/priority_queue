#ifndef UTILS

const static char *ALLOCATION_ERROR = "Could not allocate enough space";

typedef struct DoubleCircularLinkedListNode {
    void *data;
    struct DoubleCircularLinkedListNode *next;
    struct DoubleCircularLinkedListNode *prev;
} DoubleCircularLinkedListNode;

typedef struct DoubleCircularLinkedList {
    DoubleCircularLinkedListNode *current;
} DoubleCircularLinkedList;

#endif // !UTILS
