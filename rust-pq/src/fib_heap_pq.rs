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
    fn merge_with_root_list(&mut self, node: FibNodePtr<T>) {
        unsafe {
            if let Some(min) = self.min {
                let min_left = (*min.as_ptr()).left;

                (*node.as_ptr()).right = min;
                (*node.as_ptr()).left = min_left;
                (*min_left.as_ptr()).right = node;
                (*min.as_ptr()).left = node;
            } else {
                self.min = Some(node);
            }

            let is_new_min = self
                .min
                .is_none_or(|min| (*node.as_ptr()).priority < (*min.as_ptr()).priority);

            if is_new_min {
                self.min = Some(node);
            }
        }
    }

    fn remove_from_child_list(&mut self, parent: FibNodePtr<T>, node: FibNodePtr<T>) {
        unsafe {
            if (*parent.as_ptr()).child == Some(node) {
                (*parent.as_ptr()).child = if (*node.as_ptr()).right == node {
                    None
                } else {
                    Some((*node.as_ptr()).right)
                };
            }
            (*(*node.as_ptr()).left.as_ptr()).right = (*node.as_ptr()).right;
            (*(*node.as_ptr()).right.as_ptr()).left = (*node.as_ptr()).left;
            (*node.as_ptr()).left = node;
            (*node.as_ptr()).right = node;
            (*parent.as_ptr()).degree -= 1;
        }
    }

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

    fn cut(&mut self, l_node: FibNodePtr<T>, r_node: FibNodePtr<T>) {
        self.remove_from_child_list(r_node, l_node);
        self.merge_with_root_list(l_node);
        unsafe {
            (*l_node.as_ptr()).parent = None;
            (*l_node.as_ptr()).marked = false;
        }
    }

    fn cascading_cut(&mut self, node: FibNodePtr<T>) {
        unsafe {
            let ref_node = (*node.as_ptr()).parent;

            let Some(ref_node) = ref_node else {
                return;
            };
            if !(*node.as_ptr()).marked {
                (*node.as_ptr()).marked = true;
            } else {
                self.cut(node, ref_node);
                self.cascading_cut(ref_node);
            }
        }
    }

    fn heap_link(&mut self, l_node: FibNodePtr<T>, r_node: FibNodePtr<T>) {
        self.remove_from_root_list(l_node);
        unsafe {
            (*l_node.as_ptr()).left = l_node;
            (*l_node.as_ptr()).right = l_node;
            (*l_node.as_ptr()).parent = Some(r_node);
            (*l_node.as_ptr()).marked = false;

            if let Some(r_node_child) = (*r_node.as_ptr()).child {
                (*l_node.as_ptr()).left = r_node_child;
                (*l_node.as_ptr()).right = (*r_node_child.as_ptr()).left;
                (*(*r_node_child.as_ptr()).left.as_ptr()).right = l_node;
                (*r_node_child.as_ptr()).left = l_node;
            } else {
                (*r_node.as_ptr()).child = Some(l_node);
            }
            (*r_node.as_ptr()).degree += 1;
        }
    }

    fn consolidate(&mut self) {
        let Some(min) = self.min else {
            return;
        };
        if unsafe { (*min.as_ptr()).right == min } {
            return;
        }

        let max_degree = (self.size as f32).log2() as usize * 2 + 1;
        let mut degree_table: Vec<Option<FibNodePtr<T>>> = vec![None; max_degree];

        let mut roots = Vec::new();
        let mut cur = min;
        unsafe {
            loop {
                roots.push(cur);
                cur = (*cur.as_ptr()).right;
                if cur == min {
                    break;
                }
            }

            for x_ptr in roots {
                let mut x = x_ptr;
                let mut d = (*x.as_ptr()).degree;

                while let Some(y) = degree_table[d] {
                    let mut y = y;
                    if (*x.as_ptr()).priority > (*y.as_ptr()).priority {
                        std::mem::swap(&mut x, &mut y);
                    }
                    self.heap_link(y, x);
                    degree_table[d] = None;
                    d += 1;
                }
                degree_table[d] = Some(x);
            }

            self.min = None;
            for slot in degree_table.iter().flatten() {
                let node = slot.as_ptr();
                (*node).left = *slot;
                (*node).right = *slot;

                if let Some(cur_min) = self.min {
                    (*node).right = cur_min;
                    (*node).left = (*cur_min.as_ptr()).left;
                    (*(*cur_min.as_ptr()).left.as_ptr()).right = *slot;
                    (*cur_min.as_ptr()).left = *slot;

                    if (*node).priority < (*cur_min.as_ptr()).priority {
                        self.min = Some(*slot);
                    }
                } else {
                    self.min = Some(*slot);
                }
            }
        }
    }

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
        Self::new()
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

    fn merge(self, other: Self) -> Self {
        let mut new_pq = FibHeapPQ::<T> {
            min: self.min,
            size: self.size + other.size,
        };

        let (Some(lhs_min), Some(rhs_min)) = (self.min, other.min) else {
            new_pq.min = if self.min.is_some() {
                other.min
            } else {
                self.min
            };
            std::mem::forget(self);
            std::mem::forget(other);
            return new_pq;
        };

        unsafe {
            let lhs_last = (*lhs_min.as_ptr()).left;
            let rhs_last = (*rhs_min.as_ptr()).left;

            (*lhs_last.as_ptr()).right = rhs_min;
            (*rhs_min.as_ptr()).left = lhs_last;
            (*rhs_last.as_ptr()).right = lhs_min;
            (*lhs_min.as_ptr()).left = rhs_last;

            if (*rhs_min.as_ptr()).priority < (*lhs_min.as_ptr()).priority {
                new_pq.min = Some(rhs_min);
            }
        }

        std::mem::forget(self);
        std::mem::forget(other);
        new_pq
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
