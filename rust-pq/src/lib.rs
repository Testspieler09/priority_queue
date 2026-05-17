pub mod fib_heap_pq;
pub mod min_heap_pq;
pub mod native_heap_pq;

pub trait PriorityQueue<T: Clone> {
    /// Creates a new empty priority queue with default capacity.
    fn new() -> Self
    where
        Self: Sized;

    /// Creates a new empty priority queue with a specific capacity.
    fn with_capacity(capacity: usize) -> Self
    where
        Self: Sized;

    /// Inserts a new element with the given priority.
    fn insert(&mut self, data: T, priority: usize);

    /// Extracts and removes the element with the minimum priority.
    fn extract_min(&mut self) -> Option<T>;

    /// Returns true if the queue is empty.
    fn is_empty(&self) -> bool;

    /// Removes a specific element by some identifier (if available).
    /// In Rust, usually we don't remove by pointer, so this could be
    /// adapted to remove by value or index.
    fn remove(&mut self, index: usize) -> Option<T>;

    /// Decreases the priority of a specific element.
    fn decrease_key(&mut self, index: usize, new_priority: usize);

    /// Returns a reference to the element with the minimum priority without removing it.
    fn peek(&self) -> Option<&T>;

    /// Merges another priority queue into a new one.
    fn merge(&self, other: &Self) -> Self
    where
        Self: Sized;
}
