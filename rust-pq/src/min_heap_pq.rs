use crate::PriorityQueue;
use std::ptr::NonNull;

pub struct MinHeapNode<T> {
    data: T,
    priority: usize,
    heap_idx: usize,
}

pub struct MinHeapPQ<T> {
    nodes: Vec<NonNull<MinHeapNode<T>>>,
}

impl<T> MinHeapPQ<T> {
    fn swap_nodes(&mut self, i: usize, j: usize) {
        self.nodes.swap(i, j);
        unsafe {
            self.nodes[i].as_mut().heap_idx = i;
            self.nodes[j].as_mut().heap_idx = j;
        }
    }

    fn bubble_down(&mut self, mut i: usize) {
        loop {
            let mut smallest = i;
            let lh_idx = 2 * i + 1;
            let rh_idx = 2 * i + 2;
            unsafe {
                if lh_idx < self.nodes.len()
                    && self.nodes[lh_idx].as_ref().priority < self.nodes[smallest].as_ref().priority
                {
                    smallest = lh_idx;
                }
                if rh_idx < self.nodes.len()
                    && self.nodes[rh_idx].as_ref().priority < self.nodes[smallest].as_ref().priority
                {
                    smallest = rh_idx;
                }
            }
            if smallest != i {
                self.swap_nodes(i, smallest);
                i = smallest;
            } else {
                break;
            }
        }
    }

    fn bubble_up(&mut self, mut i: usize) {
        while i > 0 {
            let parent = (i - 1) / 2;
            unsafe {
                if self.nodes[parent].as_ref().priority > self.nodes[i].as_ref().priority {
                    self.swap_nodes(parent, i);
                    i = parent;
                } else {
                    break;
                }
            }
        }
    }
}

impl<T> PriorityQueue<T> for MinHeapPQ<T> {
    type NodeIdentifier = NonNull<MinHeapNode<T>>;

    fn new() -> Self {
        Self { nodes: Vec::new() }
    }

    fn with_capacity(capacity: usize) -> Self {
        Self {
            nodes: Vec::with_capacity(capacity),
        }
    }

    fn insert(&mut self, data: T, priority: usize) -> Self::NodeIdentifier {
        let idx = self.nodes.len();
        let ptr = NonNull::from(Box::leak(Box::new(MinHeapNode {
            data,
            priority,
            heap_idx: idx,
        })));
        self.nodes.push(ptr);
        self.bubble_up(idx);
        ptr
    }

    fn extract_min(&mut self) -> Option<T> {
        if self.is_empty() {
            return None;
        }
        let min_ptr = self.nodes[0];
        // SAFETY: reclaiming the Box we leaked in insert
        let data = unsafe { Box::from_raw(min_ptr.as_ptr()) }.data;

        let last = *self.nodes.last().unwrap();
        self.nodes[0] = last;
        self.nodes.pop();

        if !self.nodes.is_empty() {
            unsafe {
                self.nodes[0].as_mut().heap_idx = 0;
            }
            self.bubble_down(0);
        }
        Some(data)
    }

    fn is_empty(&self) -> bool {
        self.nodes.is_empty()
    }

    fn remove(&mut self, handle: Self::NodeIdentifier) -> Option<T> {
        // SAFETY: caller guarantees handle is live and belongs to this heap
        let node_idx = unsafe { handle.as_ref().heap_idx };
        let data = unsafe { Box::from_raw(handle.as_ptr()) }.data;

        let last = *self.nodes.last().unwrap();
        self.nodes[node_idx] = last;
        self.nodes.pop();

        if node_idx < self.nodes.len() {
            unsafe {
                self.nodes[node_idx].as_mut().heap_idx = node_idx;
            }
            self.bubble_down(node_idx);
        }
        Some(data)
    }

    fn decrease_key(&mut self, mut handle: Self::NodeIdentifier, new_priority: usize) {
        unsafe {
            let node = handle.as_mut();
            if new_priority >= node.priority {
                return;
            }
            node.priority = new_priority;
            self.bubble_up(node.heap_idx);
        }
    }

    fn peek(&self) -> Option<&T> {
        self.nodes.first().map(|ptr| unsafe { &ptr.as_ref().data })
    }

    fn merge(mut self, other: Self) -> Self {
        for ptr in &other.nodes {
            self.nodes.push(*ptr);
        }
        std::mem::forget(other);

        let len = self.nodes.len();
        if len > 1 {
            for i in (0..len / 2).rev() {
                self.bubble_down(i);
            }
            for (i, ptr) in self.nodes.iter_mut().enumerate() {
                unsafe {
                    ptr.as_mut().heap_idx = i;
                }
            }
        }
        self
    }
}

impl<T> Drop for MinHeapPQ<T> {
    fn drop(&mut self) {
        for ptr in self.nodes.drain(..) {
            unsafe {
                drop(Box::from_raw(ptr.as_ptr()));
            }
        }
    }
}
