use std::ptr::NonNull;

use crate::PriorityQueue;

type FibNodePtr<T> = NonNull<FibHeapNode<T>>;

pub struct FibHeapNode<T> {
    priority: usize,
    degree: usize,
    marked: bool,

    parent: Option<FibNodePtr<T>>,
    child: Option<FibNodePtr<T>>,
    left: FibNodePtr<T>,
    right: FibNodePtr<T>,

    data: T,
}

pub struct FibHeapPQ<T> {
    root_list: Option<FibNodePtr<T>>,
    min: Option<FibNodePtr<T>>,
    size: usize,
}

impl<T> FibHeapPQ<T> {
    fn merge_with_root_list(&mut self, node_ptr: FibNodePtr<T>) {
        unsafe {
            if let Some(root) = self.root_list {
                let root_left = (*root.as_ptr()).left;

                (*node_ptr.as_ptr()).right = root;
                (*node_ptr.as_ptr()).left = root_left;
                (*root_left.as_ptr()).right = node_ptr;
                (*root.as_ptr()).left = node_ptr;
            } else {
                self.root_list = Some(node_ptr);
            }

            let is_new_min = self.min.map_or(true, |min| {
                (*node_ptr.as_ptr()).priority < (*min.as_ptr()).priority
            });

            if is_new_min {
                self.min = Some(node_ptr);
            }
        }
    }

    fn remove_from_child_list(&mut self, parent_ptr: FibNodePtr<T>, node_ptr: FibNodePtr<T>) {}

    fn cut(&mut self, l_node_ptr: FibNodePtr<T>, r_node_ptr: FibNodePtr<T>) {}

    fn cascading_cut(&mut self, node_ptr: FibNodePtr<T>) {}

    fn heap_link(&mut self, l_node_ptr: FibNodePtr<T>, r_node_ptr: FibNodePtr<T>) {}

    fn consolidate(&mut self) {}

    fn free_node_list(start: Option<FibNodePtr<T>>) {
        //      static void _free_node_list(FibHeapNode *start) {
        //     if (start == NULL) return;
        //     FibHeapNode *cur = start;
        //     do {
        //         FibHeapNode *next = cur->right;
        //         _free_node_list(cur->child);
        //         free(cur);
        //         cur = next;
        //     } while (cur != start);
        // }
    }
}

impl<T> PriorityQueue<T> for FibHeapPQ<T> {
    type NodeIdentifier = FibNodePtr<T>;

    fn new() -> Self {
        Self {
            root_list: None,
            min: None,
            size: 0,
        }
    }

    // NOTE: with_capacity does not make sense for a fibonacci heap
    fn with_capacity(_capacity: usize) -> Self {
        PriorityQueue::new()
    }

    fn insert(&mut self, data: T, priority: usize) -> Self::NodeIdentifier {
        todo!()
    }

    fn extract_min(&mut self) -> Option<T> {
        todo!()
    }

    #[inline]
    fn is_empty(&self) -> bool {
        self.size == 0
    }

    fn remove(&mut self, node: Self::NodeIdentifier) -> Option<T> {
        todo!()
    }

    fn decrease_key(&mut self, node: Self::NodeIdentifier, new_priority: usize) {
        todo!()
    }

    fn peek(&self) -> Option<&T> {
        self.min
            .as_ref()
            .map(|node| unsafe { &(*node.as_ptr()).data })
    }

    fn merge(mut self, other: Self) -> Self {
        todo!()
    }
}

impl<T> Drop for FibHeapPQ<T> {
    fn drop(&mut self) {
        let Some(start) = self.root_list else {
            return;
        };
        let mut cur = start;
        unsafe {
            loop {
                let next = (*cur.as_ptr()).right;
                FibHeapPQ::<T>::free_node_list((*cur.as_ptr()).child);
                drop(Box::from_raw(cur.as_ptr()));
                cur = next;
                if cur == start {
                    break;
                }
            }
        }
    }
}
