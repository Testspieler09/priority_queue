use crate::PriorityQueue;

#[cfg(test)]
#[path = "./min_heap_pq_test.rs"]
mod tests;

#[derive(Clone)]
pub struct MinHeapNode<T> {
    data: T,
    priority: usize,
}

pub struct MinHeapPQ<T> {
    nodes: Vec<MinHeapNode<T>>,
}

impl<T> MinHeapPQ<T> {
    #[inline]
    fn bubble_down(&mut self, idx: usize) {
        let mut smallest = idx;
        let mut i = idx;

        loop {
            let lh_idx = (2 * i) + 1;
            let rh_idx = (2 * i) + 2;

            if lh_idx < self.nodes.len()
                && self.nodes[lh_idx].priority < self.nodes[smallest].priority
            {
                smallest = lh_idx;
            }

            if rh_idx < self.nodes.len()
                && self.nodes[rh_idx].priority < self.nodes[smallest].priority
            {
                smallest = rh_idx;
            }

            if smallest != i {
                self.nodes.swap(i, smallest);
                i = smallest;
            } else {
                break;
            }
        }
    }
}

impl<T: Clone> PriorityQueue<T> for MinHeapPQ<T> {
    fn new() -> Self {
        Self {
            nodes: Vec::<MinHeapNode<T>>::new(),
        }
    }

    fn with_capacity(capacity: usize) -> Self {
        Self {
            nodes: Vec::<MinHeapNode<T>>::with_capacity(capacity),
        }
    }

    fn insert(&mut self, data: T, priority: usize) {
        let new_node = MinHeapNode::<T> { data, priority };
        self.nodes.push(new_node);

        let mut idx = self.nodes.len() - 1;
        while idx > 0 {
            let parent_idx = (idx - 1) / 2;
            if self.nodes[parent_idx].priority > priority {
                self.nodes.swap(parent_idx, idx);
                idx = parent_idx;
            } else {
                break;
            }
        }
    }

    fn extract_min(&mut self) -> Option<T> {
        if self.is_empty() {
            return None;
        }
        let data = self.nodes.swap_remove(0).data;

        if self.nodes.len() > 1 {
            self.bubble_down(0);
        }

        Some(data)
    }

    #[inline]
    fn is_empty(&self) -> bool {
        self.nodes.is_empty()
    }

    fn remove(&mut self, index: usize) -> Option<T> {
        if index >= self.nodes.len() {
            return None;
        }
        let data = self.nodes.swap_remove(index).data;

        if index < self.nodes.len() {
            self.bubble_down(index);
        }

        Some(data)
    }

    fn decrease_key(&mut self, index: usize, new_priority: usize) {
        let Some(node) = self.nodes.get_mut(index) else {
            return;
        };

        node.priority = new_priority;

        let mut idx = index;
        while idx > 0 {
            let parent_idx = (idx - 1) / 2;
            if self.nodes[parent_idx].priority > self.nodes[idx].priority {
                self.nodes.swap(parent_idx, idx);
                idx = parent_idx;
            } else {
                break;
            }
        }
    }

    fn peek(&self) -> Option<&T> {
        self.nodes.get(0).map(|node| &node.data)
    }

    fn merge(&self, other: &Self) -> Self {
        let mut new_pq = MinHeapPQ {
            nodes: [self.nodes.as_slice(), other.nodes.as_slice()].concat(),
        };

        if new_pq.nodes.len() <= 1 {
            return new_pq;
        }

        for i in (0..=(new_pq.nodes.len() / 2).saturating_sub(1)).rev() {
            new_pq.bubble_down(i);
        }

        new_pq
    }
}
