use std::{cmp::Ordering, collections::BinaryHeap};

use crate::PriorityQueue;

#[derive(PartialEq, Eq)]
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

impl<T: PartialOrd + Eq> PriorityQueue<T> for BinHeapPQ<T> {
    type NodeIdentifier = ();

    #[inline]
    fn new() -> Self {
        BinaryHeap::new()
    }

    #[inline]
    fn with_capacity(capacity: usize) -> Self {
        BinaryHeap::with_capacity(capacity)
    }

    #[inline]
    fn insert(&mut self, data: T, priority: usize) -> Self::NodeIdentifier {
        self.push(BinHeapNode { data, priority });
    }

    #[inline]
    fn extract_min(&mut self) -> Option<T> {
        self.pop().map(|node| node.data)
    }

    #[inline]
    fn is_empty(&self) -> bool {
        BinaryHeap::is_empty(self)
    }

    /// Removes an element by index.
    ///
    /// # Panics
    ///
    /// Always panics because `BinaryHeap` does not support
    /// efficient arbitrary-index removal.
    ///
    /// Consider using a different priority queue implementation
    /// if indexed removal is required.
    fn remove(&mut self, _node: Self::NodeIdentifier) -> Option<T> {
        unimplemented!("This function can not be natively implemented for BinaryHeap")
    }

    /// Decreases the priority of an element at a given index.
    ///
    /// # Panics
    ///
    /// Always panics because `BinaryHeap` does not expose stable
    /// element indices or native decrease-key operations.
    ///
    /// Typical alternatives:
    /// - Reinsert the element with a new priority
    /// - Use a custom heap implementation with handles/indices
    fn decrease_key(&mut self, _node: Self::NodeIdentifier, _new_priority: usize) {
        unimplemented!("This function can not be natively implemented for BinaryHeap")
    }

    #[inline]
    fn peek(&self) -> Option<&T> {
        BinaryHeap::peek(self).map(|node| &node.data)
    }

    fn merge(mut self, other: Self) -> Self {
        self.extend(other);
        self
    }
}
