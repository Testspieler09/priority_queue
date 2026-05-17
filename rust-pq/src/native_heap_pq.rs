use std::collections::BinaryHeap;

use crate::PriorityQueue;

#[cfg(test)]
#[path = "./native_heap_pq_test.rs"]
mod tests;

pub struct BinHeapNode<T> {
    data: T,
    priority: usize,
}

impl<T: PartialEq> PartialEq for BinHeapNode<T> {
    fn eq(&self, other: &Self) -> bool {
        self.data == other.data && self.priority == other.priority
    }
}

impl<T: PartialOrd> PartialOrd for BinHeapNode<T> {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        match self.data.partial_cmp(&other.data) {
            Some(core::cmp::Ordering::Equal) => {}
            ord => return ord,
        }
        self.priority.partial_cmp(&other.priority)
    }
}

impl<T: PartialEq> Eq for BinHeapNode<T> {}

impl<T: PartialOrd> Ord for BinHeapNode<T> {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.priority.cmp(&other.priority)
    }
}

pub type BinHeapPQ<T> = BinaryHeap<BinHeapNode<T>>;

impl<T: Clone + PartialOrd> PriorityQueue<T> for BinHeapPQ<T> {
    fn new() -> Self {
        BinaryHeap::new()
    }

    fn with_capacity(capacity: usize) -> Self {
        BinaryHeap::with_capacity(capacity)
    }

    fn insert(&mut self, data: T, priority: usize) {
        let new_node = BinHeapNode { data, priority };
        self.push(new_node);
    }

    fn extract_min(&mut self) -> Option<T> {
        self.pop().map(|node| node.data)
    }

    fn is_empty(&self) -> bool {
        self.is_empty()
    }

    fn remove(&mut self, index: usize) -> Option<T> {
        todo!()
    }

    fn decrease_key(&mut self, index: usize, new_priority: usize) {
        todo!()
    }

    fn peek(&self) -> Option<&T> {
        self.peek().map(|node_ref| &node_ref.data)
    }

    fn merge(&self, other: &Self) -> Self {
        todo!()
    }
}
