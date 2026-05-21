fn main() {
    use rust_pq::{PriorityQueue, native_heap_pq::BinHeapPQ};

    // Create a new MinHeap Priority Queue
    let mut pq = BinHeapPQ::new();

    // Insert elements with priorities
    pq.insert("task1", 5);
    pq.insert("task2", 2);
    pq.insert("task3", 8);
    pq.insert("task4", 1);

    // Peek at the element with the smallest priority
    // NOTE: call [`peek`] on the trait [`PriorityQueue`] as it otherwise will conflict with the
    // [`BinaryHeap`] [`peek`] implementation
    if let Some(min) = PriorityQueue::peek(&pq) {
        println!("Minimum element: {}", min); // Should print "task4"
        assert!(*min == "task4");
    }

    // Extract elements in order of priority
    while let Some(task) = pq.extract_min() {
        println!("Processing: {}", task);
    }

    // Output should be:
    // Processing: task4
    // Processing: task2
    // Processing: task1
    // Processing: task3

    // WARN: [`decrease_key`] and [`remove`] are unimplemented for the priority queue
    // implementation.

    // Merging two priority queues
    let mut pq1 = BinHeapPQ::new();
    pq1.insert("a", 3);
    pq1.insert("b", 1);

    let mut pq2 = BinHeapPQ::new();
    pq2.insert("c", 2);
    pq2.insert("d", 5);

    let mut pq_merged = pq1.merge(pq2);

    println!("Merged queue:");
    while let Some(task) = pq_merged.extract_min() {
        println!("Processing: {}", task);
    }
}
