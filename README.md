# 🚀 Complete Programming Roadmap

> A production-ready, university-level learning resource for **C++** and **Java** — covering everything from basics to advanced DSA, OOP, and system-level programming.

[![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Java](https://img.shields.io/badge/Java-17-orange?logo=openjdk&logoColor=white)](https://openjdk.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Stars](https://img.shields.io/github/stars/848deepak/Complete-programming-roadmap?style=social)](https://github.com/848deepak/Complete-programming-roadmap)

---

## 📖 Table of Contents

1. [About This Repository](#-about-this-repository)
2. [Who Is This For?](#-who-is-this-for)
3. [Repository Structure](#-repository-structure)
4. [C++ Curriculum](#-c-curriculum)
   - [C++ Basics](#-c-basics)
   - [C++ Intermediate](#-c-intermediate)
   - [C++ OOP](#-c-oop)
   - [C++ DSA](#-c-dsa)
   - [C++ Advanced](#-c-advanced)
5. [Java Curriculum](#-java-curriculum)
   - [Java Basics](#-java-basics)
   - [Java Intermediate](#-java-intermediate)
   - [Java OOP](#-java-oop)
   - [Java DSA](#-java-dsa)
   - [Java Advanced](#-java-advanced)
6. [DSA Topic Index](#-dsa-topic-index)
7. [How to Use This Repo](#-how-to-use-this-repo)
8. [Complexity Quick Reference](#-complexity-quick-reference)
9. [Interview Patterns Cheat Sheet](#-interview-patterns-cheat-sheet)
10. [Contributing](#-contributing)
11. [License](#-license)

---

## 📌 About This Repository

**Complete Programming Roadmap** is a structured, hands-on coding curriculum built for students, self-learners, and interview candidates. Every topic is explained at textbook depth with:

- ✅ **Clean, commented code** — every line explained
- ✅ **Complexity analysis** — Time & Space for every algorithm
- ✅ **Interview-focused problems** — LeetCode-style problems solved from scratch
- ✅ **Dual-language coverage** — C++ and Java side by side
- ✅ **Beginner → Expert progression** — structured learning path

---

## 🎯 Who Is This For?

| Audience | Benefit |
|----------|---------|
| 🧑‍🎓 CS Students | Lecture-quality explanations alongside working code |
| 💼 Interview Prep | Comprehensive DSA with patterns & complexity analysis |
| 🔄 Language Switchers | See the same algorithm in C++ and Java |
| 🏫 Instructors | Ready-to-use teaching examples |
| 🔁 Self-Learners | Clear progressive structure from basics to advanced |

---

## 📁 Repository Structure

```
Complete-programming-roadmap/
│
├── cpp/                          ← C++ complete curriculum
│   ├── basics/                   ← Variables, control flow, functions, arrays
│   ├── intermediate/             ← Pointers, exceptions, file I/O, STL
│   ├── oops/                     ← Classes, inheritance, polymorphism
│   ├── dsa/                      ← Data Structures & Algorithms
│   │   ├── 01-basic-to-intermediate/
│   │   │   ├── arrays/
│   │   │   ├── linked-list/
│   │   │   ├── stack/
│   │   │   ├── queue/
│   │   │   ├── hashing/
│   │   │   └── searching-sorting/
│   │   └── 02-advanced/
│   │       ├── trees/
│   │       ├── heap/
│   │       ├── graphs/
│   │       ├── dynamic-programming/
│   │       └── tries/
│   └── advanced/                 ← Templates, move semantics, multithreading
│
└── java/                         ← Java complete curriculum
    ├── basics/                   ← Variables, control flow, methods, arrays
    ├── intermediate/             ← Generics, exceptions, collections, I/O
    ├── oops/                     ← Classes, interfaces, polymorphism
    ├── dsa/                      ← Data Structures & Algorithms (Java)
    │   ├── 01-basic-to-intermediate/
    │   │   ├── arrays/
    │   │   ├── linked-list/
    │   │   ├── stack/
    │   │   ├── hashing/
    │   │   └── searching-sorting/
    │   └── 02-advanced/
    │       ├── trees/
    │       ├── heap/
    │       ├── graphs/
    │       └── dynamic-programming/
    └── advanced/                 ← Concurrency, streams, functional programming
```

---

## 📘 C++ Curriculum

### 🔹 C++ Basics

| File | Topics | Key Concepts |
|------|--------|--------------|
| [`01_variables.cpp`](cpp/basics/01_variables.cpp) | Data types, type casting, constants | `int`, `float`, `char`, `sizeof`, `auto` |
| [`02_control_flow.cpp`](cpp/basics/02_control_flow.cpp) | If-else, switch, loops, patterns | `for`, `while`, `do-while`, nested loops |
| [`03_functions_and_recursion.cpp`](cpp/basics/03_functions_and_recursion.cpp) | Functions, overloading, recursion, lambdas | Default args, pass-by-ref, tail recursion |
| [`04_arrays_and_strings.cpp`](cpp/basics/04_arrays_and_strings.cpp) | Arrays, vectors, string methods | `std::vector`, `std::string`, stringstream |

### 🔹 C++ Intermediate

| File | Topics | Key Concepts |
|------|--------|--------------|
| [`01_pointers_references.cpp`](cpp/intermediate/01_pointers_references.cpp) | Pointers, references, dynamic memory | `*`, `&`, `new`, `delete`, pointer arithmetic |
| [`02_exception_handling.cpp`](cpp/intermediate/02_exception_handling.cpp) | Exceptions, custom exception classes | `try`/`catch`/`throw`, `noexcept`, RAII |
| [`03_file_handling.cpp`](cpp/intermediate/03_file_handling.cpp) | File I/O, binary files, CSV | `ifstream`, `ofstream`, `fstream` |
| [`04_stl.cpp`](cpp/intermediate/04_stl.cpp) | STL containers & algorithms | `vector`, `map`, `set`, `priority_queue`, `sort` |

### 🔹 C++ OOP

| File | Topics |
|------|--------|
| [`01_oop.cpp`](cpp/oops/01_oop.cpp) | Classes, inheritance, polymorphism, abstraction, encapsulation, operator overloading |

### 🔹 C++ DSA

#### Arrays
| File | Topics | Time Complexity |
|------|--------|-----------------|
| [`01_array_traversal.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/01_array_traversal.cpp) | Traversal, access | O(n) |
| [`03_array_deletion.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/03_array_deletion.cpp) | Delete by index/value, remove duplicates | O(n) |
| [`04_linear_binary_search.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/04_linear_binary_search.cpp) | Linear search, binary search, rotated array | O(n) / O(log n) |
| [`05_prefix_sum.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/05_prefix_sum.cpp) | Prefix sums, range queries | O(n) build + O(1) query |
| [`06_sliding_window.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/06_sliding_window.cpp) | Fixed & variable sliding window | O(n) |
| [`07_two_pointer.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/07_two_pointer.cpp) | Two-sum, rain water, 3-sum, container water | O(n) |
| [`08_kadane.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/08_kadane.cpp) | Max subarray (Kadane's), circular variant | O(n) |
| [`09_matrix_operations.cpp`](cpp/dsa/01-basic-to-intermediate/arrays/09_matrix_operations.cpp) | Transpose, rotate, spiral, sorted matrix search | O(n²) |

#### Linked Lists
| File | Topics |
|------|--------|
| [`01_create_print_linkedlist.cpp`](cpp/dsa/01-basic-to-intermediate/linked-list/01_create_print_linkedlist.cpp) | Singly LL creation and traversal |
| [`08_reverse_linkedlist.cpp`](cpp/dsa/01-basic-to-intermediate/linked-list/08_reverse_linkedlist.cpp) | Iterative and recursive reversal |
| [`09_doubly_linked_list.cpp`](cpp/dsa/01-basic-to-intermediate/linked-list/09_doubly_linked_list.cpp) | Full DLL with O(1) delete by pointer |
| [`10_circular_linked_list.cpp`](cpp/dsa/01-basic-to-intermediate/linked-list/10_circular_linked_list.cpp) | Circular LL, Josephus problem |
| [`11_detect_cycle.cpp`](cpp/dsa/01-basic-to-intermediate/linked-list/11_detect_cycle.cpp) | Floyd's cycle detection, find start, remove cycle |
| [`12_merge_two_lists.cpp`](cpp/dsa/01-basic-to-intermediate/linked-list/12_merge_two_lists.cpp) | Merge sorted lists, merge K lists (heap), merge sort on LL |

#### Stack
| File | Topics |
|------|--------|
| [`01_stack_array.cpp`](cpp/dsa/01-basic-to-intermediate/stack/01_stack_array.cpp) | Stack using array |
| [`02_stack_linked_list.cpp`](cpp/dsa/01-basic-to-intermediate/stack/02_stack_linked_list.cpp) | Stack using linked list, postfix evaluation |
| [`03_balanced_parentheses.cpp`](cpp/dsa/01-basic-to-intermediate/stack/03_balanced_parentheses.cpp) | Bracket matching, longest valid parentheses |
| [`04_next_greater_element.cpp`](cpp/dsa/01-basic-to-intermediate/stack/04_next_greater_element.cpp) | NGE, stock span, largest rectangle in histogram |

#### Queue, Hashing, Sorting
| File | Topics |
|------|--------|
| [`02_circular_deque_priority_queue.cpp`](cpp/dsa/01-basic-to-intermediate/queue/02_circular_deque_priority_queue.cpp) | Circular queue, deque, sliding window max, min-heap PQ |
| [`01_hashmap_hashset.cpp`](cpp/dsa/01-basic-to-intermediate/hashing/01_hashmap_hashset.cpp) | HashMap, HashSet, chaining, two-sum, group anagrams |
| [`02_all_sorting_algorithms.cpp`](cpp/dsa/01-basic-to-intermediate/searching-sorting/02_all_sorting_algorithms.cpp) | All 8 sorting algorithms |

#### Advanced DSA
| File | Category | Topics |
|------|----------|--------|
| [`04_tree_extras.cpp`](cpp/dsa/02-advanced/trees/04_tree_extras.cpp) | Trees | Level-order, zigzag, diameter, balanced check, max path sum |
| [`01_min_max_heap.cpp`](cpp/dsa/02-advanced/heap/01_min_max_heap.cpp) | Heap | Min/Max heap, build O(n), heap sort, K-th largest |
| [`04_shortest_path.cpp`](cpp/dsa/02-advanced/graphs/04_shortest_path.cpp) | Graphs | Dijkstra, Bellman-Ford, Floyd-Warshall |
| [`05_minimum_spanning_tree.cpp`](cpp/dsa/02-advanced/graphs/05_minimum_spanning_tree.cpp) | Graphs | Kruskal (Union-Find), Prim (min-heap) |
| [`01_trie.cpp`](cpp/dsa/02-advanced/tries/01_trie.cpp) | Trie | Insert, search, autocomplete, prefix count, delete |
| [`01_fibonacci_memoization.cpp`](cpp/dsa/02-advanced/dynamic-programming/01_fibonacci_memoization.cpp) | DP | Memoization, tabulation |
| [`02_lcs_tabulation.cpp`](cpp/dsa/02-advanced/dynamic-programming/02_lcs_tabulation.cpp) | DP | Longest Common Subsequence |
| [`03_01_knapsack.cpp`](cpp/dsa/02-advanced/dynamic-programming/03_01_knapsack.cpp) | DP | 0/1 Knapsack |

### 🔹 C++ Advanced

| File | Topics |
|------|--------|
| [`01_advanced.cpp`](cpp/advanced/01_advanced.cpp) | Templates, variadic templates, move semantics, smart pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`), lambdas, `std::optional`, `std::variant`, `constexpr`, multithreading |

---

## ☕ Java Curriculum

### 🔹 Java Basics

| File | Topics |
|------|--------|
| [`Variables.java`](java/basics/Variables.java) | Primitive types, wrapper classes, `var`, constants, String, StringBuilder |
| [`ControlFlow.java`](java/basics/ControlFlow.java) | If-else, switch, loops |
| [`ArraysAndStrings.java`](java/basics/ArraysAndStrings.java) | Arrays, ArrayList, String methods |
| [`FunctionsAndRecursion.java`](java/basics/FunctionsAndRecursion.java) | Methods, recursion, varargs |

### 🔹 Java Intermediate

| File | Topics |
|------|--------|
| [`Intermediate.java`](java/intermediate/Intermediate.java) | Generics, exceptions, collections, file I/O, streams |

### 🔹 Java OOP

| File | Topics |
|------|--------|
| [`OOP.java`](java/oops/OOP.java) | Abstract classes, interfaces, inheritance, polymorphism, encapsulation |

### 🔹 Java DSA

| File | Topics |
|------|--------|
| [`Arrays.java`](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) | Insert/delete, binary search, prefix sum, two-pointer, Kadane's, sliding window, matrix |
| [`LinkedList.java`](java/dsa/01-basic-to-intermediate/linked-list/LinkedList.java) | Singly/Doubly LL, Floyd's cycle detection, palindrome, merge sort |
| [`StackAndQueue.java`](java/dsa/01-basic-to-intermediate/stack/StackAndQueue.java) | Stack/Queue, balanced parens, NGE, sliding-window max, PriorityQueue |
| [`Hashing.java`](java/dsa/01-basic-to-intermediate/hashing/Hashing.java) | HashMap/HashSet, custom keys, 7 interview problems |
| [`SortingAlgorithms.java`](java/dsa/01-basic-to-intermediate/searching-sorting/SortingAlgorithms.java) | All 8 sorting algorithms |
| [`Trees.java`](java/dsa/02-advanced/trees/Trees.java) | All traversals, BST, diameter, balance check, LCA |
| [`Heap.java`](java/dsa/02-advanced/heap/Heap.java) | Min/Max heap, heap sort, K-th largest, top-K frequent, median stream |
| [`Graphs.java`](java/dsa/02-advanced/graphs/Graphs.java) | BFS, DFS, Dijkstra, topological sort, Kruskal MST |

### 🔹 Java Advanced

| File | Topics |
|------|--------|
| [`Advanced.java`](java/advanced/Advanced.java) | Generics, lambdas, Stream API, Optional, concurrency |

---

## 📊 DSA Topic Index

> Quick lookup — find any algorithm or data structure instantly.

### Arrays & Strings
| Topic | C++ | Java |
|-------|-----|------|
| Array traversal | [01_array_traversal.cpp](cpp/dsa/01-basic-to-intermediate/arrays/01_array_traversal.cpp) | [Arrays.java](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) |
| Binary search | [04_linear_binary_search.cpp](cpp/dsa/01-basic-to-intermediate/arrays/04_linear_binary_search.cpp) | [Arrays.java](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) |
| Prefix sum | [05_prefix_sum.cpp](cpp/dsa/01-basic-to-intermediate/arrays/05_prefix_sum.cpp) | [Arrays.java](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) |
| Two pointer | [07_two_pointer.cpp](cpp/dsa/01-basic-to-intermediate/arrays/07_two_pointer.cpp) | [Arrays.java](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) |
| Sliding window | [06_sliding_window.cpp](cpp/dsa/01-basic-to-intermediate/arrays/06_sliding_window.cpp) | [Arrays.java](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) |
| Kadane's algorithm | [08_kadane.cpp](cpp/dsa/01-basic-to-intermediate/arrays/08_kadane.cpp) | [Arrays.java](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) |
| Matrix rotation/spiral | [09_matrix_operations.cpp](cpp/dsa/01-basic-to-intermediate/arrays/09_matrix_operations.cpp) | [Arrays.java](java/dsa/01-basic-to-intermediate/arrays/Arrays.java) |

### Linked Lists
| Topic | C++ | Java |
|-------|-----|------|
| Singly linked list | [01_create_print_linkedlist.cpp](cpp/dsa/01-basic-to-intermediate/linked-list/01_create_print_linkedlist.cpp) | [LinkedList.java](java/dsa/01-basic-to-intermediate/linked-list/LinkedList.java) |
| Doubly linked list | [09_doubly_linked_list.cpp](cpp/dsa/01-basic-to-intermediate/linked-list/09_doubly_linked_list.cpp) | [LinkedList.java](java/dsa/01-basic-to-intermediate/linked-list/LinkedList.java) |
| Cycle detection | [11_detect_cycle.cpp](cpp/dsa/01-basic-to-intermediate/linked-list/11_detect_cycle.cpp) | [LinkedList.java](java/dsa/01-basic-to-intermediate/linked-list/LinkedList.java) |
| Merge sorted lists | [12_merge_two_lists.cpp](cpp/dsa/01-basic-to-intermediate/linked-list/12_merge_two_lists.cpp) | [LinkedList.java](java/dsa/01-basic-to-intermediate/linked-list/LinkedList.java) |

### Stack & Queue
| Topic | C++ | Java |
|-------|-----|------|
| Stack (array) | [01_stack_array.cpp](cpp/dsa/01-basic-to-intermediate/stack/01_stack_array.cpp) | [StackAndQueue.java](java/dsa/01-basic-to-intermediate/stack/StackAndQueue.java) |
| Monotonic stack / NGE | [04_next_greater_element.cpp](cpp/dsa/01-basic-to-intermediate/stack/04_next_greater_element.cpp) | [StackAndQueue.java](java/dsa/01-basic-to-intermediate/stack/StackAndQueue.java) |
| Circular queue | [02_circular_deque_priority_queue.cpp](cpp/dsa/01-basic-to-intermediate/queue/02_circular_deque_priority_queue.cpp) | [StackAndQueue.java](java/dsa/01-basic-to-intermediate/stack/StackAndQueue.java) |
| Priority queue | [02_circular_deque_priority_queue.cpp](cpp/dsa/01-basic-to-intermediate/queue/02_circular_deque_priority_queue.cpp) | [Heap.java](java/dsa/02-advanced/heap/Heap.java) |

### Hashing
| Topic | C++ | Java |
|-------|-----|------|
| HashMap / HashSet | [01_hashmap_hashset.cpp](cpp/dsa/01-basic-to-intermediate/hashing/01_hashmap_hashset.cpp) | [Hashing.java](java/dsa/01-basic-to-intermediate/hashing/Hashing.java) |
| Two sum | [01_hashmap_hashset.cpp](cpp/dsa/01-basic-to-intermediate/hashing/01_hashmap_hashset.cpp) | [Hashing.java](java/dsa/01-basic-to-intermediate/hashing/Hashing.java) |
| Group anagrams | [01_hashmap_hashset.cpp](cpp/dsa/01-basic-to-intermediate/hashing/01_hashmap_hashset.cpp) | [Hashing.java](java/dsa/01-basic-to-intermediate/hashing/Hashing.java) |

### Sorting
| Algorithm | Best | Average | Worst | Stable | C++ | Java |
|-----------|------|---------|-------|--------|-----|------|
| Bubble Sort | O(n) | O(n²) | O(n²) | ✅ | [02_all_sorting.cpp](cpp/dsa/01-basic-to-intermediate/searching-sorting/02_all_sorting_algorithms.cpp) | [SortingAlgorithms.java](java/dsa/01-basic-to-intermediate/searching-sorting/SortingAlgorithms.java) |
| Insertion Sort | O(n) | O(n²) | O(n²) | ✅ | same | same |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | ✅ | same | same |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | ❌ | same | same |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | ❌ | same | same |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | ✅ | same | same |
| Radix Sort | O(dn) | O(dn) | O(dn) | ✅ | same | same |

### Trees
| Topic | C++ | Java |
|-------|-----|------|
| Binary tree traversals | [01_binary_tree_traversal.cpp](cpp/dsa/02-advanced/trees/01_binary_tree_traversal.cpp) | [Trees.java](java/dsa/02-advanced/trees/Trees.java) |
| BST operations | [02_bst_insert_search.cpp](cpp/dsa/02-advanced/trees/02_bst_insert_search.cpp) | [Trees.java](java/dsa/02-advanced/trees/Trees.java) |
| Level-order / BFS | [04_tree_extras.cpp](cpp/dsa/02-advanced/trees/04_tree_extras.cpp) | [Trees.java](java/dsa/02-advanced/trees/Trees.java) |
| Diameter / balance check | [04_tree_extras.cpp](cpp/dsa/02-advanced/trees/04_tree_extras.cpp) | [Trees.java](java/dsa/02-advanced/trees/Trees.java) |
| Lowest Common Ancestor | [04_tree_extras.cpp](cpp/dsa/02-advanced/trees/04_tree_extras.cpp) | [Trees.java](java/dsa/02-advanced/trees/Trees.java) |

### Heap
| Topic | C++ | Java |
|-------|-----|------|
| Min / Max heap | [01_min_max_heap.cpp](cpp/dsa/02-advanced/heap/01_min_max_heap.cpp) | [Heap.java](java/dsa/02-advanced/heap/Heap.java) |
| Heap sort | [01_min_max_heap.cpp](cpp/dsa/02-advanced/heap/01_min_max_heap.cpp) | [Heap.java](java/dsa/02-advanced/heap/Heap.java) |
| K-th largest | [01_min_max_heap.cpp](cpp/dsa/02-advanced/heap/01_min_max_heap.cpp) | [Heap.java](java/dsa/02-advanced/heap/Heap.java) |
| Median from stream | [01_min_max_heap.cpp](cpp/dsa/02-advanced/heap/01_min_max_heap.cpp) | [Heap.java](java/dsa/02-advanced/heap/Heap.java) |

### Graphs
| Topic | C++ | Java |
|-------|-----|------|
| BFS | [01_graph_bfs.cpp](cpp/dsa/02-advanced/graphs/01_graph_bfs.cpp) | [Graphs.java](java/dsa/02-advanced/graphs/Graphs.java) |
| DFS | [02_graph_dfs.cpp](cpp/dsa/02-advanced/graphs/02_graph_dfs.cpp) | [Graphs.java](java/dsa/02-advanced/graphs/Graphs.java) |
| Cycle detection | [02_graph_dfs.cpp](cpp/dsa/02-advanced/graphs/02_graph_dfs.cpp) | [Graphs.java](java/dsa/02-advanced/graphs/Graphs.java) |
| Topological Sort | [02_graph_dfs.cpp](cpp/dsa/02-advanced/graphs/02_graph_dfs.cpp) | [Graphs.java](java/dsa/02-advanced/graphs/Graphs.java) |
| Dijkstra | [04_shortest_path.cpp](cpp/dsa/02-advanced/graphs/04_shortest_path.cpp) | [Graphs.java](java/dsa/02-advanced/graphs/Graphs.java) |
| Bellman-Ford | [04_shortest_path.cpp](cpp/dsa/02-advanced/graphs/04_shortest_path.cpp) | — |
| Floyd-Warshall | [04_shortest_path.cpp](cpp/dsa/02-advanced/graphs/04_shortest_path.cpp) | — |
| Kruskal MST | [05_minimum_spanning_tree.cpp](cpp/dsa/02-advanced/graphs/05_minimum_spanning_tree.cpp) | [Graphs.java](java/dsa/02-advanced/graphs/Graphs.java) |
| Prim MST | [05_minimum_spanning_tree.cpp](cpp/dsa/02-advanced/graphs/05_minimum_spanning_tree.cpp) | — |

### Dynamic Programming
| Topic | C++ | Java |
|-------|-----|------|
| Fibonacci (memoization) | [01_fibonacci_memoization.cpp](cpp/dsa/02-advanced/dynamic-programming/01_fibonacci_memoization.cpp) | [01_FibonacciMemoization.java](java/dsa/02-advanced/dynamic-programming/01_FibonacciMemoization.java) |
| Longest Common Subsequence | [02_lcs_tabulation.cpp](cpp/dsa/02-advanced/dynamic-programming/02_lcs_tabulation.cpp) | [02_LCSTabulation.java](java/dsa/02-advanced/dynamic-programming/02_LCSTabulation.java) |
| 0/1 Knapsack | [03_01_knapsack.cpp](cpp/dsa/02-advanced/dynamic-programming/03_01_knapsack.cpp) | [03_ZeroOneKnapsack.java](java/dsa/02-advanced/dynamic-programming/03_ZeroOneKnapsack.java) |

### Trie
| Topic | C++ | Java |
|-------|-----|------|
| Trie: insert, search, autocomplete | [01_trie.cpp](cpp/dsa/02-advanced/tries/01_trie.cpp) | — |

---

## ⚙️ How to Use This Repo

### Prerequisites

| Language | Requirement |
|----------|-------------|
| C++ | GCC 9+ or Clang 10+ with C++17 support |
| Java | JDK 11+ |

### Compile & Run

**C++**
```bash
g++ -std=c++17 -O2 filename.cpp -o output
./output
```

**Java**
```bash
javac Filename.java
java Filename
```

### Suggested Learning Path

```
Week 1–2:  Basics (variables, control flow, functions, arrays)
Week 3–4:  OOP (classes, inheritance, polymorphism)
Week 5–6:  Intermediate (pointers/refs, STL/collections, exceptions)
Week 7–8:  Arrays DSA (traversal, search, two-pointer, Kadane's)
Week 9–10: Linked Lists + Stack + Queue
Week 11:   Hashing + Sorting algorithms
Week 12:   Trees (binary tree, BST, traversals)
Week 13:   Heap + Priority Queue
Week 14:   Graphs (BFS, DFS, shortest path, MST)
Week 15:   Dynamic Programming
Week 16:   Trie + Advanced C++ / Java features
```

---

## ⏱️ Complexity Quick Reference

### Data Structures

| Data Structure | Access | Search | Insert | Delete | Space |
|----------------|--------|--------|--------|--------|-------|
| Array | O(1) | O(n) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(n) | O(1) | O(1)* | O(n) |
| Stack | O(n) | O(n) | O(1) | O(1) | O(n) |
| Queue | O(n) | O(n) | O(1) | O(1) | O(n) |
| Hash Map | O(1)† | O(1)† | O(1)† | O(1)† | O(n) |
| Binary Search Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Heap | O(1) top | O(n) | O(log n) | O(log n) | O(n) |
| Trie | O(L) | O(L) | O(L) | O(L) | O(N×A) |

> *O(1) with pointer to node. †Average case.

### Sorting Algorithms

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | ❌ |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | ✅ |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | ❌ |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | ❌ |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(k) | ✅ |
| Radix Sort | O(dn) | O(dn) | O(dn) | O(n) | ✅ |

---

## 🎯 Interview Patterns Cheat Sheet

### Array Patterns
```
Sliding Window    → max/min subarray, longest substring
Two Pointer       → sorted pair sum, rain water, remove duplicates
Prefix Sum        → range queries, subarray sum = k
Monotonic Stack   → next greater element, histogram area
Binary Search     → sorted/rotated arrays, search in matrix
```

### Linked List Tricks
```
Dummy node        → cleaner head insert/delete
Slow + Fast ptr   → middle node, cycle detection (Floyd's)
Reverse in-place  → prev, curr, next pattern
Two-pass          → n-th from end
```

### Tree Patterns
```
DFS (recursion)   → height, diameter, path sum, LCA
BFS (queue)       → level-order, zigzag, right-view
Post-order        → bottom-up: balance check, LCA
Inorder BST       → yields sorted sequence
```

### Graph Patterns
```
BFS               → shortest path (unweighted)
DFS               → connected components, cycle detection, topo sort
Dijkstra          → shortest path (non-negative weights)
Bellman-Ford      → shortest path (negative weights, detect neg cycles)
Union-Find        → Kruskal MST, number of islands
```

### DP Patterns
```
Memoization (top-down)  → add cache to recursive solution
Tabulation (bottom-up)  → build table iteratively
State definition         → dp[i] = "answer for first i elements"
Transition               → dp[i] = f(dp[i-1], dp[i-2], ...)
```

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork** the repository
2. **Create a branch**: `git checkout -b feature/add-topic-name`
3. **Add your code** following the existing style:
   - Header comment block with description and compile instructions
   - Inline comments explaining every non-trivial line
   - Complexity analysis (Time + Space)
   - Edge case handling
4. **Submit a Pull Request** with a clear description

### Code Style Guide
- C++: `snake_case` for variables/functions, `PascalCase` for classes
- Java: `camelCase` for variables/methods, `PascalCase` for classes
- Every file must compile without warnings with `-Wall`

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## ⭐ Star This Repo

If this helped you prepare for interviews or learn programming, please consider giving it a ⭐ — it helps others find this resource!

[![GitHub stars](https://img.shields.io/github/stars/848deepak/Complete-programming-roadmap?style=for-the-badge&logo=github)](https://github.com/848deepak/Complete-programming-roadmap/stargazers)

---

<div align="center">

**Made with ❤️ for learners everywhere**

*Complete Programming Roadmap — C++ & Java — From Basics to Advanced DSA*

</div>
