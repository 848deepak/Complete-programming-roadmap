# DSA — Data Structures & Algorithms

Comprehensive DSA coverage in **C++** and **Java**, structured for both university study and technical interview preparation.

---

## 📁 Directory Structure

```
dsa/
├── 01-basic-to-intermediate/
│   ├── arrays/           ← Array algorithms
│   ├── linked-list/      ← Singly, Doubly, Circular LL
│   ├── stack/            ← Stack implementations + applications
│   ├── queue/            ← Queue variants
│   ├── hashing/          ← HashMap, HashSet, interview problems
│   └── searching-sorting/← All sorting algorithms
└── 02-advanced/
    ├── trees/            ← Binary Tree, BST, AVL
    ├── heap/             ← Min/Max Heap, Priority Queue
    ├── graphs/           ← BFS, DFS, Dijkstra, MST
    ├── dp/               ← Dynamic Programming
    └── tries/            ← Trie data structure
```

---

## 📂 Arrays

| File | Topics Covered | Complexity |
|------|----------------|------------|
| `01_array_traversal.cpp` | Basic traversal and access | O(n) |
| `03_array_deletion.cpp` | Delete by index, by value, remove duplicates | O(n) |
| `04_linear_binary_search.cpp` | Linear search, binary search, rotated array | O(n) / O(log n) |
| `05_prefix_sum.cpp` | Prefix sums, range queries in O(1) | O(n) prep + O(1) query |
| `07_two_pointer.cpp` | Two-sum, remove dups, rain water, 3-sum | O(n) |
| `08_kadane.cpp` | Max subarray, circular variant, max product | O(n) |
| `09_matrix_operations.cpp` | Transpose, rotate, spiral, sorted matrix search | O(n²) / O(m+n) |

### Key Techniques

- **Prefix Sum**: Precompute cumulative sums for O(1) range queries
- **Two Pointer**: Reduce O(n²) brute-force to O(n) by moving two indices
- **Sliding Window**: Fixed or variable-size window sliding through array
- **Kadane's Algorithm**: DP-based max subarray in O(n)

---

## 📂 Linked List

| File | Topics Covered |
|------|----------------|
| `01_linked_list.cpp` | Singly LL: insert/delete (start, end, position), reverse, search |
| `09_doubly_linked_list.cpp` | DLL: O(1) delete by pointer, backward traversal |
| `10_circular_linked_list.cpp` | CLL: tail pointer, Josephus problem |
| `11_detect_cycle.cpp` | Floyd's Cycle Detection, find start, remove cycle |
| `12_merge_two_lists.cpp` | Merge two sorted lists, merge K lists, merge sort |
| `13_insert_at_position.cpp` | Insert at any valid index in singly linked list |
| `14_delete_from_position.cpp` | Delete from any valid index in singly linked list |

### Singly vs Doubly vs Circular

| Feature | Singly LL | Doubly LL | Circular LL |
|---------|-----------|-----------|-------------|
| Extra pointer | — | prev | tail.next = head |
| Memory | O(1) | +1 pointer/node | same as singly |
| Delete by pointer | O(n) | **O(1)** | O(n) |
| Backward traversal | No | Yes | No |

---

## 📂 Stack

| File | Topics Covered |
|------|----------------|
| `01_stack_array.cpp` | Stack with array, push/pop/peek |
| `02_stack_linked_list.cpp` | Stack with linked list, applications |
| `03_balanced_parentheses.cpp` | Matching brackets, min reversals, score, longest valid |
| `04_next_greater_element.cpp` | NGE, PGE, NSE, stock span, largest histogram rect |

### Monotonic Stack Pattern
For each element, pop elements from the stack that the current element answers:
```
while (!stack.empty() && arr[i] > arr[stack.top()]):
    result[stack.pop()] = arr[i]
stack.push(i)
```
Time: **O(n)** — each element pushed and popped at most once.

---

## 📂 Queue

| File | Topics Covered |
|------|----------------|
| `01_queue_array.cpp` | Queue with array |
| `02_circular_deque_priority_queue.cpp` | Circular Queue, Deque, sliding window max, Min Heap PQ |

---

## 📂 Hashing

| File | Topics Covered |
|------|----------------|
| `01_hashmap_hashset.cpp` | HashMap, HashSet, custom hash, chaining, interview problems |

### Interview Problems Solved with Hashing (O(n))
- **Two Sum** — complement lookup
- **Longest Consecutive Sequence** — set membership
- **Group Anagrams** — sorted key
- **Subarray Sum = K** — prefix sum + frequency map

---

## 📂 Searching & Sorting

| File | Algorithm | Time | Space | Stable |
|------|-----------|------|-------|--------|
| `01_binary_search.cpp` | Binary Search variants | O(log n) | O(1) | — |
| `02_all_sorting_algorithms.cpp` | All 8 algorithms | — | — | — |

### Sorting Complexity Table

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | ❌ |
| Insertion | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) | ✅ |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) | ❌ |
| Heap | O(n log n) | O(n log n) | O(n log n) | O(1) | ❌ |
| Counting | O(n+k) | O(n+k) | O(n+k) | O(k) | ✅ |
| Radix | O(dn) | O(dn) | O(dn) | O(n) | ✅ |

---

## 📂 Trees (Advanced)

| File | Topics Covered |
|------|----------------|
| `01_binary_tree.cpp` | BT traversals, height, count, leaf check |
| `02_bst.cpp` | BST insert, search, delete, validate, LCA |
| `03_avl_tree.cpp` | Self-balancing BST with rotations |
| `04_tree_extras.cpp` | Level-order, zigzag, diameter, balance, path sum |

---

## 📂 Heap (Advanced)

| File | Topics Covered |
|------|----------------|
| `01_min_max_heap.cpp` | Min/Max heap, build O(n), heap sort, K-th largest |

### Heap Operations
| Operation | Time |
|-----------|------|
| insert | O(log n) |
| extractMin/Max | O(log n) |
| peek | O(1) |
| buildHeap | **O(n)** (bottom-up) |

---

## 📂 Graphs (Advanced)

| File | Topics Covered |
|------|----------------|
| `01_bfs_dfs.cpp` | BFS, DFS, connected components |
| `02_cycle_detection.cpp` | Undirected/directed cycle detection |
| `03_topological_sort.cpp` | Kahn's BFS + DFS topo sort for DAGs |
| `04_shortest_path.cpp` | Dijkstra, Bellman-Ford, Floyd-Warshall |
| `05_minimum_spanning_tree.cpp` | Kruskal (Union-Find), Prim (min-heap) |

### Algorithm Comparison

| Problem | Algorithm | Time | Constraint |
|---------|-----------|------|------------|
| Shortest path (unweighted) | BFS | O(V+E) | — |
| Shortest path (non-neg weights) | Dijkstra | O((V+E) log V) | weight ≥ 0 |
| Shortest path (neg weights) | Bellman-Ford | O(VE) | detects neg cycles |
| All-pairs shortest | Floyd-Warshall | O(V³) | no neg cycles |
| MST | Kruskal / Prim | O(E log E) | undirected |

---

## 🎯 Interview Quick Reference

### Array Patterns
- **Sliding Window** → variable size, fixed size
- **Two Pointer** → sorted pairs, palindrome, container water
- **Prefix Sum** → range queries, subarray sum = k

### Linked List Tricks
- Use **dummy node** for cleaner insert/delete at head
- **Slow/fast pointer** → middle, cycle detection
- **Two-pass** → find n-th from end

### Stack Patterns
- **Monotonic Stack** → NGE, Stock Span, Histogram
- **Two stacks** → implement queue, min-stack in O(1)

### Tree Patterns
- **DFS** (recursion) → height, diameter, path sum
- **BFS** (queue) → level-order, zigzag, right-view
- **Post-order** → bottom-up computation (LCA, balanced check)

### Graph Patterns
- **BFS** → shortest path (unweighted), level exploration
- **DFS** → connected components, cycle detection, topo sort
- **Union-Find** → Kruskal MST, number of components

---

## ⚙️ How to Compile & Run

**C++**
```bash
g++ -std=c++17 -O2 filename.cpp -o out && ./out
```

**Java**
```bash
javac Filename.java && java Filename
```
