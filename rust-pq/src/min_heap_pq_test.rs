use super::*;

#[test]
fn test_insert_and_peek() {
    let mut pq = MinHeapPQ::new();
    pq.insert("a", 5);
    pq.insert("b", 2);
    pq.insert("c", 8);

    assert_eq!(pq.peek(), Some(&"b"));
}

#[test]
fn test_extract_min() {
    let mut pq = MinHeapPQ::new();
    pq.insert("x", 10);
    pq.insert("y", 3);
    pq.insert("z", 7);

    assert_eq!(pq.extract_min(), Some("y"));
    assert_eq!(pq.extract_min(), Some("z"));
    assert_eq!(pq.extract_min(), Some("x"));
    assert!(pq.extract_min().is_none());
}

#[test]
fn test_is_empty() {
    let mut pq: MinHeapPQ<&str> = MinHeapPQ::new();
    assert!(pq.is_empty());

    pq.insert("hello", 1);
    assert!(!pq.is_empty());

    pq.extract_min();
    assert!(pq.is_empty());
}

#[test]
fn test_remove() {
    let mut pq = MinHeapPQ::new();
    pq.insert("one", 5);
    pq.insert("two", 2);
    pq.insert("three", 8);

    assert_eq!(pq.remove(1), Some("one"));
    assert_eq!(pq.peek(), Some(&"two"));
}

#[test]
fn test_decrease_key() {
    let mut pq = MinHeapPQ::new();
    pq.insert("low", 10);
    pq.insert("high", 20);

    pq.decrease_key(1, 5);
    assert_eq!(pq.peek(), Some(&"high"));
}

#[test]
fn test_merge() {
    let mut pq1 = MinHeapPQ::new();
    pq1.insert("a", 3);
    pq1.insert("b", 1);

    let mut pq2 = MinHeapPQ::new();
    pq2.insert("c", 2);
    pq2.insert("d", 4);

    let mut pq3 = pq1.merge(&pq2);
    assert_eq!(pq3.extract_min(), Some("b"));
    assert_eq!(pq3.extract_min(), Some("c"));
    assert_eq!(pq3.extract_min(), Some("a"));
    assert_eq!(pq3.extract_min(), Some("d"));
}
