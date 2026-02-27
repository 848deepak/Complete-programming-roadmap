# C++ Data Structures & Algorithms: Stack

> **Folder:** `cpp/dsa/01-basic-to-intermediate/stack/` | **Level:** Basic to Intermediate  
> **Files:** `01_stack_array.cpp` · `02_stack_linked_list.cpp` · `03_balanced_parentheses.cpp` · `04_next_greater_element.cpp`

---

## 1. Introduction

A Stack is a linear data structure that follows the **LIFO (Last In, First Out)** principle. Think of it like a stack of plates: the last plate you put on top is the first one you take off.

Stacks are fundamental for managing function calls (the call stack), evaluating expressions, backtracking algorithms (like DFS), and parsing syntax.

> **Compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Core Operations

Regardless of how it's implemented, a Stack must support these core operations efficiently (all O(1) time):

- `push(x)`: Add element `x` to the top of the stack.
- `pop()`: Remove the element from the top of the stack.
- `peek()` or `top()`: Look at the top element without removing it.
- `isEmpty()`: Check if the stack has no elements.
- `isFull()`: Check if the stack is full (only applicable for array-based fixed-size stacks).

---

## 3. Implementations

### 3.1 Stack using Array (`01_stack_array.cpp`)
- **How it works:** Uses a fixed-size `int arr[MAX]` and an integer `top` (initialized to -1) to track the highest filled index.
- **Push:** Increment `top`, then `arr[top] = x`.
- **Pop:** Decrement `top` (the old value remains in memory but is "overwritten" logically).
- **Pros:** simple, cache-friendly (contiguous memory).
- **Cons:** Fixed capacity. (Though a dynamic array like `std::vector` solves this constraint by resizing).

### 3.2 Stack using Linked List (`02_stack_linked_list.cpp`)
- **How it works:** maintains a pointers to a sequential node. The `head` of the Linked List acts as the `top` of the stack.
- **Push:** create node, set `node->next = head`, then `head = node` (insert at start).
- **Pop:** move `head = head->next` and `delete` the old head (delete from start).
- **Pros:** Dynamic sizing, no memory wasted on unused capacity.
- **Cons:** Extra memory overhead per element (pointer), less cache-friendly due to scattered heap allocations.

---

## 4. Algorithmic Applications

### 4.1 Balanced Parentheses (`03_balanced_parentheses.cpp`)
A classic stack problem evaluating if a string composed of brackets `()`, `{}`, `[]` is well-formed.
- **Algorithm:** Traverse the string. If it's an opening bracket, `push()` it. If it's a closing bracket, `pop()` the top and ensure it matches the closing bracket type. The string is balanced if the stack is completely `isEmpty()` at the very end.
- **Logic:** LIFO structure elegantly ensures that the most recently opened bracket is closed first.

### 4.2 Next Greater Element (`04_next_greater_element.cpp`)
Given an array, find the next nearest element to the right that is strictly greater than the current element.
- **Brute Force:** Nested loops, O(n²).
- **Optimal Stack Approach:** Use a "Monotonic Decreasing Stack". Iterate from Right-to-Left. Maintain a stack of elements seen so far. For the current element, `pop()` from the stack until the top element is strictly greater. The top element is the answer. Then `push()` current element.
- **Time Complexity:** O(n). Every element is pushed and popped at most once.

---

## 5. Time & Space Complexity

### Implementation Complexities
| Operation | Array Implementation | Linked List Implementation |
|-----------|-----------------------|-----------------------------|
| push() | **O(1)** (avg) | **O(1)** |
| pop() | **O(1)** | **O(1)** |
| peek() | **O(1)** | **O(1)** |
| Space | O(N capacity) | O(N elements * (data + ptr)) |

### Application Complexities
| Application | Time | Extra Space |
|-------------|------|-------------|
| Balanced Parentheses | O(N length) | O(N) (worst case all `(((`) |
| Next Greater Element | O(N array) | O(N) |

---

## 6. Interview Relevance

Stacks are frequently used as auxiliary data structures to optimize solutions to string parsing or array traversal problems to O(n).

| Problem Pattern | Classic Examples |
|-----------------|------------------|
| **String Parsing / Matching** | Balanced Parentheses, Evaluate Reverse Polish Notation, Basic Calculator, Decode String, Validate Stack Sequences |
| **Monotonic Stack (Crucial!)** | Next Greater Element (I & II), Daily Temperatures, Largest Rectangle in Histogram, Trapping Rain Water (Stack Approach), Online Stock Span |
| **Design** | Min Stack, Implement Queue using Stacks |

---

> **Next Steps:** Head over to the `queue/` folder to explore the FIFO counterpart to Stacks.
