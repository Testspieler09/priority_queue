use crate::PriorityQueue;

pub struct FibHeapPQ<T> {
    dummy: T,
}

impl<T: Clone> PriorityQueue<T> for FibHeapPQ<T> {
    fn new() -> Self {
        todo!()
    }

    fn with_capacity(capacity: usize) -> Self {
        todo!()
    }

    fn insert(&mut self, data: T, priority: usize) {
        todo!()
    }

    fn extract_min(&mut self) -> Option<T> {
        todo!()
    }

    fn is_empty(&self) -> bool {
        todo!()
    }

    fn remove(&mut self, index: usize) -> Option<T> {
        todo!()
    }

    fn decrease_key(&mut self, index: usize, new_priority: usize) {
        todo!()
    }

    fn peek(&self) -> Option<&T> {
        todo!()
    }

    fn merge(mut self, other: Self) -> Self {
        todo!()
    }
}
