# C++ Data Structures & Algorithms: Queue

> **Folder:** `cpp/dsa/01-basic-to-intermediate/queue/` | **Level:** Basic to Intermediate  
> **Files:** `01_queue_array.cpp` · `02_circular_deque_priority_queue.cpp`

---

## 1. Introduction

A Queue is a linear data structure that follows the **FIFO (First In, First Out)** principle. Think of it like a line at a ticket counter: the first person to join the line is the first person to be served.

Queues are essential for scheduling algorithms, breadth-first search (BFS) in graphs/trees, handling asynchronous requests, and buffering data.

> **Compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Core Operations

A standard queue supports these constant-time O(1) operations:

- `enqueue(x)` / `push(x)`: Add element `x` to the **rear** (back) of the queue.
- `dequeue()` / `pop()`: Remove the element from the **front** of the queue.
- `front()` / `peek()`: Look at the front element without removing it.
- `empty()`: Check if the queue has no elements.
- `full()`: Check if the queue is full (applicable for fixed-size arrays).

---

## 3. Implementations & Variations

### 3.1 Simple Queue using Array (`01_queue_array.cpp`)
- **Mechanism:** Uses a fixed-size array with `front` and `rear` pointers.
- **Problem:** In a naive array implementation, popping from the front leaves unused space at the beginning of the array. Even if there is space, `rear` might reach the end, preventing new insertions ("false full" condition).
- **Solution:** Shift elements (O(n) - bad) or use a **Circular Queue**.

### 3.2 Circular Queue (`02_circular_deque_priority_queue.cpp`)
Connects the end of the array back to the beginning to efficiently reuse space.
- **Mechanism:** Uses modulo arithmetic for index wrapping: `rear = (rear + 1) % capacity`.
- **Advantage:** Solves the "false full" problem of linear array queues, making all operations strictly O(1) without shifting elements.

### 3.3 Deque (Double-Ended Queue)
A deque generalizes a queue by allowing insertion and deletion at **both ends** (front and rear).
- **C++ STL:** `std::deque` (often pronounced "deck").
- **Use cases:** Sliding window maximum, palidrome checking, undo/redo buffers.

### 3.4 Priority Queue
Elements are dequeued based on **priority**, not insertion order.
- **Mechanism:** Typically implemented using a **Heap** data structure (Binary Max-Heap or Min-Heap).
- **Complexities:** Insertion `push()` is O(log n), removal `pop()` is O(log n), viewing top `top()` is O(1).
- **C++ STL:** `std::priority_queue` (Max-Heap by default). Use `greater<T>` comparator for a Min-Heap.
- **Use cases:** Dijkstra's Shortest Path, Huffman Coding, scheduling tasks with urgent priorities.

---

## 4. Time & Space Complexity

| Data Structure | Enqueue | Dequeue | Front/Top | Notes |
|----------------|---------|---------|-----------|-------|
| Array Queue | O(1) | O(1) | O(1) | "False full" issue |
| Circular Queue | O(1) | O(1) | O(1) | Solves space reuse |
| Linked List Queue| O(1) | O(1) | O(1) | Dynamic size, extra pointer mem |
| `std::deque` | O(1) ends | O(1) ends | O(1) | Random access O(1) supported |
| Priority Queue | O(log n) | O(log n) | O(1) | Maintains heap property |

---

## 5. Interview Relevance

Queues usually appear as the underlying mechanism for algorithms traversing level-by-level (BFS) or prioritizing elements (Heap/Priority Queue).

| Problem Pattern | Classic Examples |
|-----------------|------------------|
| **Breadth-First Search (BFS)** | Binary Tree Level Order Traversal, Rotten Oranges, Shortest Path in Binary Matrix, Word Ladder |
| **Priority Queue / Heap** | Kth Largest Element, Merge K Sorted Lists, Top K Frequent Elements, Find Median from Data Stream |
| **Deque / Monotonic Queue** | Sliding Window Maximum (O(n) using Deque) |
| **Design** | Implement Queue using Stacks, Design Circular Queue |

---

> **Next Steps:** Proceed to `trees/` and `graphs/` to see how Queues power complex BFS traversals.
