use std::{cmp::Ordering, collections::BinaryHeap};

use crate::PriorityQueue;

#[derive(Clone, PartialEq, Eq)]
pub struct BinHeapNode<T> {
    data: T,
    priority: usize,
}

impl<T: PartialOrd + Eq> Ord for BinHeapNode<T> {
    fn cmp(&self, other: &Self) -> Ordering {
        other.priority.cmp(&self.priority)
    }
}

impl<T: PartialOrd + Eq> PartialOrd for BinHeapNode<T> {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

pub type BinHeapPQ<T> = BinaryHeap<BinHeapNode<T>>;

impl<T: Clone + PartialOrd + Eq> PriorityQueue<T> for BinHeapPQ<T> {
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

    fn remove(&mut self, _index: usize) -> Option<T> {
        unimplemented!("This function can not be natively implemented for BinaryHeap")
    }

    fn decrease_key(&mut self, _index: usize, _new_priority: usize) {
        unimplemented!("This function can not be natively implemented for BinaryHeap")
    }

    fn peek(&self) -> Option<&T> {
        BinaryHeap::peek(self).map(|node_ref| &node_ref.data)
    }

    fn merge(&self, other: &Self) -> Self {
        let new_pq = [self.as_slice(), other.as_slice()].concat();
        BinaryHeap::from(new_pq)
    }
}
