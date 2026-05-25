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
    min: Option<FibNodePtr<T>>,
    size: usize,
}

impl<T> FibHeapPQ<T> {
    fn merge_with_root_list(&mut self, node_ptr: FibNodePtr<T>) {
        unsafe {
            if let Some(min) = self.min {
                let min_left = (*min.as_ptr()).left;

                (*node_ptr.as_ptr()).right = min;
                (*node_ptr.as_ptr()).left = min_left;
                (*min_left.as_ptr()).right = node_ptr;
                (*min.as_ptr()).left = node_ptr;
            } else {
                self.min = Some(node_ptr);
            }

            let is_new_min = self
                .min
                .is_none_or(|min| (*node_ptr.as_ptr()).priority < (*min.as_ptr()).priority);

            if is_new_min {
                self.min = Some(node_ptr);
            }
        }
    }

    fn remove_from_child_list(&mut self, parent_ptr: FibNodePtr<T>, node_ptr: FibNodePtr<T>) {}

    fn remove_from_root_list(&mut self, node: FibNodePtr<T>) {
        unsafe {
            let left = (*node.as_ptr()).left;
            let right = (*node.as_ptr()).right;

            if right == node {
                self.min = None;
            } else {
                if self.min == Some(node) {
                    self.min = Some(right);
                }

                (*left.as_ptr()).right = right;
                (*right.as_ptr()).left = left;
            }

            (*node.as_ptr()).left = node;
            (*node.as_ptr()).right = node;
        }
    }

    fn cut(&mut self, l_node_ptr: FibNodePtr<T>, r_node_ptr: FibNodePtr<T>) {}

    fn cascading_cut(&mut self, node_ptr: FibNodePtr<T>) {}

    fn heap_link(&mut self, l_node_ptr: FibNodePtr<T>, r_node_ptr: FibNodePtr<T>) {}

    fn consolidate(&mut self) {}

    fn free_node_list(start: Option<FibNodePtr<T>>) {
        let Some(start_ptr) = start else {
            return;
        };

        let mut cur = start_ptr;
        unsafe {
            loop {
                let next = (*cur.as_ptr()).right;
                let child = (*cur.as_ptr()).child;
                Self::free_node_list(child);
                drop(Box::from_raw(cur.as_ptr()));
                if next == start_ptr {
                    break;
                }
                cur = next;
            }
        }
    }
}

impl<T> PriorityQueue<T> for FibHeapPQ<T> {
    type NodeIdentifier = FibNodePtr<T>;

    fn new() -> Self {
        Self { min: None, size: 0 }
    }

    // NOTE: with_capacity does not make sense for a fibonacci heap
    fn with_capacity(_capacity: usize) -> Self {
        PriorityQueue::new()
    }

    fn insert(&mut self, data: T, priority: usize) -> Self::NodeIdentifier {
        let boxed = Box::new(FibHeapNode {
            priority,
            degree: 0,
            marked: false,
            parent: None,
            child: None,

            left: NonNull::dangling(),
            right: NonNull::dangling(),

            data,
        });

        let ptr = NonNull::new(Box::into_raw(boxed)).expect("Box::into_raw never returns null");

        unsafe {
            (*ptr.as_ptr()).left = ptr;
            (*ptr.as_ptr()).right = ptr;
        }

        self.merge_with_root_list(ptr);
        self.size += 1;

        ptr
    }

    fn extract_min(&mut self) -> Option<T> {
        let min = self.min?;

        unsafe {
            if let Some(start_child) = (*min.as_ptr()).child {
                let mut child = start_child;

                loop {
                    let next = (*child.as_ptr()).right;

                    (*child.as_ptr()).left = child;
                    (*child.as_ptr()).right = child;
                    (*child.as_ptr()).parent = None;
                    (*child.as_ptr()).marked = false;

                    self.merge_with_root_list(child);

                    child = next;

                    if child == start_child {
                        break;
                    }
                }

                (*min.as_ptr()).child = None;
                (*min.as_ptr()).degree = 0;
            }

            let next_root = (*min.as_ptr()).right;
            let was_singleton = next_root == min;

            self.remove_from_root_list(min);

            if was_singleton {
                self.min = None;
            } else {
                self.min = Some(next_root);
                self.consolidate();
            }

            self.size -= 1;

            let boxed = Box::from_raw(min.as_ptr());

            Some(boxed.data)
        }
    }

    #[inline]
    fn is_empty(&self) -> bool {
        self.size == 0
    }

    fn remove(&mut self, node: Self::NodeIdentifier) -> Option<T> {
        unsafe {
            (*node.as_ptr()).priority = 0;

            let parent = (*node.as_ptr()).parent;
            if let Some(parent) = parent {
                self.cut(node, parent);
                self.cascading_cut(parent);
            }
            self.min = Some(node);
        }

        self.extract_min()
    }

    fn decrease_key(&mut self, node: Self::NodeIdentifier, new_priority: usize) {
        unsafe {
            let node_ptr = node.as_ptr();

            if new_priority > (*node_ptr).priority {
                return;
            }

            (*node_ptr).priority = new_priority;

            if let Some(parent) = (*node_ptr).parent {
                let parent_ptr = parent.as_ptr();

                if (*node_ptr).priority < (*parent_ptr).priority {
                    self.cut(node, parent);
                    self.cascading_cut(parent);
                }
            }

            match self.min {
                Some(min) => {
                    if (*node_ptr).priority < (*min.as_ptr()).priority {
                        self.min = Some(node);
                    }
                }
                None => {
                    self.min = Some(node);
                }
            }
        }
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
        let Some(start) = self.min else {
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
