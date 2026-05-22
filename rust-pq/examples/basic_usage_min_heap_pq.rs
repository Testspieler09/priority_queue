fn main() {
    use rust_pq::{PriorityQueue, min_heap_pq::MinHeapPQ};

    // Create a new MinHeap Priority Queue
    let mut pq = MinHeapPQ::new();

    // Insert elements with priorities
    pq.insert("task1", 5);
    pq.insert("task2", 2);
    pq.insert("task3", 8);
    pq.insert("task4", 1);

    // Peek at the element with the smallest priority
    if let Some(min) = pq.peek() {
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

    // Demonstrating decrease_key
    pq.insert("task5", 10);
    let node_6 = pq.insert("task6", 15);
    pq.decrease_key(node_6, 3); // Decrease priority of "task6" to 3

    println!("After decreasing key:");
    while let Some(task) = pq.extract_min() {
        println!("Processing: {}", task);
    }

    // Merging two priority queues
    let mut pq1 = MinHeapPQ::new();
    pq1.insert("a", 3);
    pq1.insert("b", 1);

    let mut pq2 = MinHeapPQ::new();
    pq2.insert("c", 2);
    pq2.insert("d", 4);

    let mut pq_merged = pq1.merge(pq2);

    println!("Merged queue:");
    while let Some(task) = pq_merged.extract_min() {
        println!("Processing: {}", task);
    }
}
