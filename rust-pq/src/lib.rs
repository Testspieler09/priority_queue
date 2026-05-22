pub mod fib_heap_pq;
pub mod min_heap_pq;
pub mod native_heap_pq;

pub trait PriorityQueue<T> {
    type NodeIdentifier: Copy;

    /// Creates a new empty priority queue with default capacity.
    fn new() -> Self
    where
        Self: Sized;

    /// Creates a new empty priority queue with a specific capacity.
    fn with_capacity(capacity: usize) -> Self
    where
        Self: Sized;

    /// Inserts a new element with the given priority.
    fn insert(&mut self, data: T, priority: usize) -> Self::NodeIdentifier;

    /// Extracts and removes the element with the minimum priority.
    fn extract_min(&mut self) -> Option<T>;

    /// Returns true if the queue is empty.
    fn is_empty(&self) -> bool;

    /// Removes a specific element by some identifier (if available).
    fn remove(&mut self, node: Self::NodeIdentifier) -> Option<T>;

    /// Decreases the priority of a specific element.
    fn decrease_key(&mut self, node: Self::NodeIdentifier, new_priority: usize);

    /// Returns a reference to the element with the minimum priority without removing it.
    fn peek(&self) -> Option<&T>;

    /// Merges another priority queue into a new one.
    fn merge(self, other: Self) -> Self
    where
        Self: Sized;
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{fib_heap_pq::FibHeapPQ, min_heap_pq::MinHeapPQ, native_heap_pq::BinHeapPQ};

    fn test_insert_and_peek_impl<P>()
    where
        P: PriorityQueue<&'static str>,
    {
        let mut pq = P::new();

        let idx_1 = pq.insert("a", 5);
        // assert!(idx_1 == 0);

        let idx_2 = pq.insert("b", 2);
        // assert!(idx_1 == 1);
        // assert!(idx_2 == 0);

        let idx_3 = pq.insert("c", 8);
        // assert!(idx_1 == 1);
        // assert!(idx_2 == 0);
        // assert!(idx_3 == 2);

        assert_eq!(pq.peek(), Some(&"b"));
    }

    fn test_extract_min_impl<P>()
    where
        P: PriorityQueue<&'static str>,
    {
        let mut pq = P::new();

        pq.insert("x", 10);
        pq.insert("y", 3);
        pq.insert("z", 7);

        assert_eq!(pq.extract_min(), Some("y"));
        assert_eq!(pq.extract_min(), Some("z"));
        assert_eq!(pq.extract_min(), Some("x"));
        assert!(pq.extract_min().is_none());
    }

    fn test_is_empty_impl<P>()
    where
        P: PriorityQueue<&'static str>,
    {
        let mut pq = P::new();

        assert!(pq.is_empty());

        pq.insert("hello", 1);
        assert!(!pq.is_empty());

        pq.extract_min();
        assert!(pq.is_empty());
    }

    fn test_remove_impl<P>()
    where
        P: PriorityQueue<&'static str>,
    {
        let mut pq = P::new();

        let handle_one = pq.insert("one", 5);
        let _handle_two = pq.insert("two", 2);
        let _handle_three = pq.insert("three", 8);

        assert_eq!(pq.remove(handle_one), Some("one"));
        assert_eq!(pq.peek(), Some(&"two"));
    }

    fn test_decrease_key_impl<P>()
    where
        P: PriorityQueue<&'static str>,
    {
        let mut pq = P::new();

        let _handle_low = pq.insert("low", 10);
        let handle_high = pq.insert("high", 20);

        // Copy means handle_high is copied into the call, not moved
        pq.decrease_key(handle_high, 25); // ignored: 25 > 20
        assert_eq!(pq.peek(), Some(&"low"));

        pq.decrease_key(handle_high, 5); // valid: 5 < 20
        assert_eq!(pq.peek(), Some(&"high"));
    }

    fn test_merge_impl<P>()
    where
        P: PriorityQueue<&'static str>,
    {
        let mut pq1 = P::new();

        pq1.insert("a", 3);
        pq1.insert("b", 1);

        let mut pq2 = P::new();

        pq2.insert("c", 2);
        pq2.insert("d", 4);

        let mut pq3 = pq1.merge(pq2);

        assert_eq!(pq3.extract_min(), Some("b"));
        assert_eq!(pq3.extract_min(), Some("c"));
        assert_eq!(pq3.extract_min(), Some("a"));
        assert_eq!(pq3.extract_min(), Some("d"));
    }

    macro_rules! pq_tests {
        ($module:ident, $pq:ty) => {
            pq_tests!($module, $pq, supported);
        };
        ($module:ident, $pq:ty, unsupported_index_ops) => {
            mod $module {
                use super::*;
                #[test]
                fn insert_and_peek() {
                    test_insert_and_peek_impl::<$pq>();
                }
                #[test]
                fn extract_min() {
                    test_extract_min_impl::<$pq>();
                }
                #[test]
                fn is_empty() {
                    test_is_empty_impl::<$pq>();
                }
                #[test]
                #[should_panic]
                fn remove() {
                    test_remove_impl::<$pq>();
                }
                #[test]
                #[should_panic]
                fn decrease_key() {
                    test_decrease_key_impl::<$pq>();
                }
                #[test]
                fn merge() {
                    test_merge_impl::<$pq>();
                }
            }
        };
        ($module:ident, $pq:ty, supported) => {
            mod $module {
                use super::*;
                #[test]
                fn insert_and_peek() {
                    test_insert_and_peek_impl::<$pq>();
                }
                #[test]
                fn extract_min() {
                    test_extract_min_impl::<$pq>();
                }
                #[test]
                fn is_empty() {
                    test_is_empty_impl::<$pq>();
                }
                #[test]
                fn remove() {
                    test_remove_impl::<$pq>();
                }
                #[test]
                fn decrease_key() {
                    test_decrease_key_impl::<$pq>();
                }
                #[test]
                fn merge() {
                    test_merge_impl::<$pq>();
                }
            }
        };
    }

    pq_tests!(minheap, MinHeapPQ<&'static str>);
    pq_tests!(binheap, BinHeapPQ<&'static str>, unsupported_index_ops);
    pq_tests!(fibheap, FibHeapPQ<&'static str>);
}
