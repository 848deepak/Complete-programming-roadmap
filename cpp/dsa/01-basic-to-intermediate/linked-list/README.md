# C++ Data Structures & Algorithms: Linked List

> **Folder:** `cpp/dsa/01-basic-to-intermediate/linked-list/` | **Level:** Basic to Intermediate  
> **Files:** `01` through `14` cover creation, insertion/deletion (start, end, and position), searching, reversing, doubly/circular variants, cycle detection, and merging.

---

## 1. Introduction

A Linked List is a linear data structure where elements (nodes) are not stored in contiguous memory locations. Instead, each node contains **data** and a **pointer** (link) to the next node in the sequence. This dynamic memory allocation allows for efficient insertions and deletions without the need to shift elements like in arrays.

> **Compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Core Concepts

### File Index (`01` to `14`)

| File | Focus |
|------|-------|
| `01_create_print_linkedlist.cpp` | Create and print singly linked list |
| `01_linked_list.cpp` | Combined basics: insert/delete (start, end, position), search, reverse |
| `02_insert_at_start.cpp` | Insert node at beginning |
| `03_insert_at_end.cpp` | Insert node at end |
| `04_delete_from_start.cpp` | Delete node from beginning |
| `05_delete_from_end.cpp` | Delete node from end |
| `06_search_element.cpp` | Search element in list |
| `07_find_middle.cpp` | Find middle element (slow/fast pointers) |
| `08_reverse_linkedlist.cpp` | Reverse singly linked list |
| `09_doubly_linked_list.cpp` | Doubly linked list operations |
| `10_circular_linked_list.cpp` | Circular linked list operations |
| `11_detect_cycle.cpp` | Detect/find/remove cycle |
| `12_merge_two_lists.cpp` | Merge two/K sorted lists, merge sort |
| `13_insert_at_position.cpp` | Insert at any valid position |
| `14_delete_from_position.cpp` | Delete from any valid position |

### 2.1 The Node Structure
In C++, a node is typically defined using a `struct` or `class`:
```cpp
struct Node {
    int data;
    Node* next;
    
    // Constructor
    Node(int val) : data(val), next(nullptr) {}
};
```

### 2.2 Singly Linked List (`01` to `08`)
Each node only has a pointer to the **next** node.
- **Insertion/Deletion at Start:** Easy, O(1). Just rewire the `head` pointer.
- **Insertion/Deletion at End/Middle:** Requires traversing from the `head` to the desired node (O(n)), then rewiring.
- **Searching:** Linear search from `head` (O(n)). Random access (`arr[i]`) is not possible.
- **Reversing (`08_reverse_linkedlist.cpp`):** A classic interview problem. Requires three pointers: `prev`, `curr`, and `next` to iteratively reverse the links in O(n) time and O(1) space.

### 2.3 Doubly Linked List (`09_doubly_linked_list.cpp`)
Each node has pointers to both the **next** and **previous** nodes.
- **Advantage:** Allows traversal in both directions. Deletion of a given node is O(1) if you already have a pointer to it (no need to traverse from head to find the predecessor).
- **Disadvantage:** Takes up more memory (extra pointer per node) and requires more careful pointer management during operations.

### 2.4 Circular Linked List (`10_circular_linked_list.cpp`)
The `next` pointer of the last node points back to the `head` node, forming a circle. Can be singly or doubly linked.
- Useful for applications needing repeated cycling through a list (e.g., round-robin scheduling).

### 2.5 Advanced Patterns (`11` and `12`)
- **Cycle Detection (Floyd's Tortoise and Hare):** Uses two pointers, a `slow` pointer (moves 1 step) and a `fast` pointer (moves 2 steps). If there is a cycle, they are guaranteed to meet. (O(n) time, O(1) space).
- **Merge Two Sorted Lists:** A recursive or iterative approach to combine two pre-sorted linked lists into a single sorted list by constantly comparing the heads of the two lists.

### 2.6 Position-Based Operations (`13` and `14`)
- **Insert at Position (`13_insert_at_position.cpp`):** Insert a new node at a given 0-based index by traversing to the previous node and reconnecting links safely.
- **Delete from Position (`14_delete_from_position.cpp`):** Remove the node at a given 0-based index with proper handling for head deletion and out-of-range positions.

---

## 3. Time & Space Complexity

| Operation | Array (For Comparison) | Singly Linked List | Doubly Linked List |
|-----------|------------------------|--------------------|--------------------|
| Access (`[i]`) | **O(1)** | O(n) | O(n) |
| Insert at Start | O(n) (shifting) | **O(1)** | **O(1)** |
| Insert at End | O(1) (if space capacity) | O(n) (or O(1) if `tail` tracked) | O(1) (if `tail` tracked) |
| Delete at Start | O(n) (shifting) | **O(1)** | **O(1)** |
| Delete given node | O(n) (search + shift) | O(n) (need to find predecessor) | **O(1)** |
| Search value | O(n) | O(n) | O(n) |
| Memory overhead | Low (just data) | Medium (1 pointer per node) | High (2 pointers per node)|

---

## 4. Common Mistakes & Edge Cases

When working with Linked Lists, always consider these edge cases:
1. **Empty list:** The `head` is `nullptr`.
2. **Single node list:** Operations might need to update both `head` and/or `tail` (if tracked).
3. **Operating on the first node:** Deleting or inserting at the head requires explicitly updating the `head` pointer.
4. **Operating on the last node:** The `next` pointer of the new tail must be reliably set to `nullptr`.

**Common Errors:**
- **Dereferencing `nullptr`:** Always check `if (curr == nullptr)` before doing `curr->data` or `curr->next`. This is the #1 cause of SegFaults.
- **Losing the rest of the list:** When inserting a node `N` between `A` and `B`, you must do `N->next = A->next` *before* doing `A->next = N`. If you reverse the order, you lose the pointer to `B` forever.
- **Memory Leaks:** Always remember to `delete` nodes that you remove from the list.

---

## 5. Interview Relevance

Linked Lists are a staple in technical interviews because they test your ability to manage references (pointers) carefully without making memory errors.

| Problem Type | Classic Interview Questions |
|--------------|-----------------------------|
| **Traversal & Reversal** | Reverse a Linked List (Iterative & Recursive), Reverse in K-Groups, Palindrome Linked List |
| **Two Pointers (Slow/Fast)** | Find Middle Node, Detect Cycle (Linked List Cycle I/II), Find Kth Node from End |
| **Merging & Intersections** | Merge Two Sorted Lists, Merge k Sorted Lists, Intersection of Two Linked Lists |
| **Advanced Manipulation** | Copy List with Random Pointer, Flatten a Multilevel Doubly Linked List, LRU Cache (uses Doubly Linked List) |

---

> **Next Steps:** Head to `stack/` and `queue/` to see how restricted-access data structures are built (often using Linked Lists under the hood).
