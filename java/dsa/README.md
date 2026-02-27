# DSA — Java Implementation

Java implementations of all major Data Structures and Algorithms, organized to mirror the C++ structure for easy cross-language comparison.

---

## 📁 Directory Structure

```
java/dsa/
├── 01-basic-to-intermediate/
│   ├── arrays/          ← Arrays.java
│   ├── linked-list/     ← LinkedList.java
│   ├── stack/           ← StackAndQueue.java
│   ├── hashing/         ← Hashing.java
│   └── searching-sorting/ ← SortingAlgorithms.java
└── 02-advanced/
    ├── trees/           ← Trees.java
    ├── heap/            ← Heap.java
    └── graphs/          ← Graphs.java
```

---

## 📂 Arrays.java
Covers all fundamental array techniques:
- Insert / Delete with index shifting
- Binary Search (iterative) + First/Last Occurrence
- Prefix Sum + range queries + subarray sum = k
- Two Pointer: two-sum, remove duplicates, trap rain water
- **Kadane's Algorithm**: max subarray sum with indices
- Sliding Window: max sum window, longest subarray
- Matrix: transpose, rotate 90°, spiral, set zeroes

---

## 📂 LinkedList.java
- **Singly LL**: addFront/Back, delete, reverse (iterative + recursive), middle, palindrome check, merge sort
- **Floyd's Cycle Detection**: detect, find start, remove cycle
- **Doubly LL**: addFront/Back, popFront/Back, forward + backward print

---

## 📂 StackAndQueue.java
- **Array Stack** — push/pop/peek with overflow/underflow handling
- **Linked Stack** — unbounded, O(1) ops
- **Applications**:
  - Balanced parentheses check
  - Postfix expression evaluation
  - Next Greater Element (monotonic stack)
  - Largest Rectangle in Histogram
- **Queue** with `ArrayDeque`
- **Sliding Window Maximum** using `Deque`
- **Priority Queue** — min heap, max heap, K-th largest, merge K sorted arrays

---

## 📂 Hashing.java
- **HashMap** basics: `merge`, `getOrDefault`, `putIfAbsent`, `computeIfAbsent`
- **HashSet** basics: add, contains, remove
- **Custom Key** — overriding `hashCode()` and `equals()`
- **Interview Problems**: Two Sum, Longest Consecutive, Group Anagrams, Subarray Sum K, First Unique, Distinct in Window, Isomorphic Strings

---

## 📂 SortingAlgorithms.java
All 8 algorithms implemented with edge case testing:
Bubble → Selection → Insertion → Merge → Quick → Heap → Counting → Radix

---

## 📂 Trees.java (Advanced)
- **Traversals**: Inorder (recursive + iterative), Preorder, Level-order, Zigzag, Right View
- **Properties**: Height, Diameter, Balanced check, Max Path Sum
- **BST**: Insert, Search, Validate, LCA (BST)
- **Binary Tree LCA** — works on any tree

---

## 📂 Graphs.java (Advanced)
- **BFS**: shortest path (hops), path reconstruction
- **DFS**: connected components
- **Cycle Detection**: undirected + directed graphs
- **Topological Sort**: Kahn's BFS algorithm
- **Dijkstra**: weighted shortest path with `PriorityQueue`
- **Kruskal's MST**: Union-Find with path compression + union by rank

---

## ⚙️ Java-Specific Notes

### Useful Java Collections
```java
// Stack behavior
Deque<Integer> stk = new ArrayDeque<>();
stk.push(x); stk.pop(); stk.peek();

// Queue behavior
Deque<Integer> q = new ArrayDeque<>();
q.offer(x); q.poll(); q.peek();

// Min Heap
PriorityQueue<Integer> minPQ = new PriorityQueue<>();

// Max Heap
PriorityQueue<Integer> maxPQ = new PriorityQueue<>(Collections.reverseOrder());

// HashMap with safe default
map.getOrDefault(key, 0);
map.merge(key, 1, Integer::sum);      // increment count
map.computeIfAbsent(key, k -> new ArrayList<>()).add(value);
```

### Compile & Run
```bash
javac Filename.java && java Filename
```
