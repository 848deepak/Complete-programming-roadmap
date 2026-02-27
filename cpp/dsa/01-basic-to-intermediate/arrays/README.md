# C++ Data Structures & Algorithms: Arrays

> **Folder:** `cpp/dsa/01-basic-to-intermediate/arrays/` | **Level:** Basic to Intermediate  
> **Files:** `01_array_traversal.cpp` · `02_array_insert.cpp` · `03_array_deletion.cpp` · `04_linear_binary_search.cpp` · `05_prefix_sum.cpp` · `06_sliding_window.cpp` · `07_two_pointer.cpp` · `08_kadane.cpp` · `09_matrix_operations.cpp`

---

## 1. Introduction

Arrays are the most fundamental data structure. This module covers everything from basic array operations (insertion, deletion, traversal) to essential algorithmic techniques used in coding interviews: Binary Search, Prefix Sums, Sliding Window, Two Pointers, and Kadane's Algorithm.

> **Compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Core Concepts

### 2.1 Basic Operations (`01` to `03`)
- **Traversal:** Visiting every element in the array (O(n)).
- **Insertion:** Adding an element at a specific index. Requires shifting subsequent elements to the right (O(n)).
- **Deletion:** Removing an element at a specific index. Requires shifting subsequent elements to the left (O(n)).

### 2.2 Searching (`04_linear_binary_search.cpp`)
- **Linear Search:** Checks each element one by one. Works on unsorted arrays. (O(n) time).
- **Binary Search:** Radically faster, but **requires the array to be sorted**. Repeatedly divides the search interval in half. (O(log n) time).

### 2.3 Prefix Sum (`05_prefix_sum.cpp`)
A technique to quickly find the sum of elements in a given range `[L, R]`.
- **Precompute:** Create an array `P` where `P[i]` is the sum of all elements up to index `i`. (O(n) time).
- **Query:** The sum of range `[L, R]` is simply `P[R] - P[L-1]` (or `P[R+1] - P[L]` depending on indexing). This takes **O(1)** time.

### 2.4 Sliding Window (`06_sliding_window.cpp`)
Used for problems involving contiguous subarrays (e.g., "maximum sum subarray of size K").
- Instead of recalculating the sum of each window from scratch (O(n * K)), we maintain a running sum.
- We "slide" the window by adding the new element entering the window and subtracting the element leaving it. (O(n) time).

### 2.5 Two Pointers (`07_two_pointer.cpp`)
Uses two indices (pointers) moving through the data structure to solve problems in O(n) instead of O(n²).
- **Classic use cases:** Finding a pair with a target sum in a sorted array (pointers at start and end, move inwards), removing duplicates, palindromes, trapping rain water.

### 2.6 Kadane's Algorithm (`08_kadane.cpp`)
An elegant Dynamic Programming algorithm for finding the contiguous subarray with the largest sum.
- **Concept:** At each step, decide whether to add the current element to the existing subarray sum, or start a new subarray beginning at the current element.
- `currentSum = max(arr[i], currentSum + arr[i])`
- `globalMax = max(globalMax, currentSum)`
- **Time Complexity:** O(n).

### 2.7 Matrix Operations (`09_matrix_operations.cpp`)
Covers 2D array manipulations.
- Matrix addition, multiplication, transposition, and spiral traversal.

---

## 3. Techniques & Patterns

### When to use which pattern?

| Problem Type | Pattern to Try |
|--------------|----------------|
| Search in sorted array | **Binary Search** |
| Subarrays of fixed size K | **Fixed Sliding Window** |
| Subarrays matching a condition (e.g., sum > target) | **Variable Sliding Window** |
| Finding pairs/triplets with a target sum | **Two Pointers** (sort first if needed) |
| Multiple queries for range sums | **Prefix Sum** |
| Maximum contiguous subarray sum | **Kadane's Algorithm** |

---

## 4. Time & Space Complexity Table

| Algorithm / Operation | Time (Worst Case) | Space (Extra) |
|-----------------------|-------------------|---------------|
| Traversal | O(n) | O(1) |
| Insertion (at index) | O(n) | O(1) |
| Deletion (at index) | O(n) | O(1) |
| Linear Search | O(n) | O(1) |
| Binary Search | O(log n) | O(1) |
| Prefix Sum (Build) | O(n) | O(n) |
| Prefix Sum (Query) | O(1) | O(1) |
| Sliding Window | O(n) | O(1) |
| Two Pointers | O(n) | O(1) |
| Kadane's Algorithm | O(n) | O(1) |
| Matrix Multiplication | O(n³) | O(n²) |

---

## 5. Common Mistakes

- **Binary Search:**
  - Forgetting the condition is `left <= right` (not just `<`).
  - Calculating `mid` as `(left + right) / 2` which can cause integer overflow. Use `left + (right - left) / 2`.
  - Not ensuring the array is sorted before using Binary Search.
- **Sliding Window:**
  - Off-by-one errors when checking window size (e.g., `i - j + 1 == k`).
- **Two Pointers:**
  - Forgetting to sort the array first if the problem requires finding pairs by value (like Two Sum).
- **Prefix Sum:**
  - Not handling the `L = 0` edgecase correctly. (Using an array of size `n+1` makes this much cleaner).

---

## 6. Interview Relevance

Arrays are the most frequently tested topic in coding interviews. Mastering the patterns in this folder is critical.

| Pattern | Classic Interview Questions |
|---------|-----------------------------|
| **Two Pointers** | Two Sum II, 3Sum, Container With Most Water, Trapping Rain Water, Remove Duplicates |
| **Sliding Window** | Maximum Average Subarray I, Longest Substring Without Repeating Characters, Minimum Window Substring |
| **Prefix Sum** | Subarray Sum Equals K, Range Sum Query, Product of Array Except Self |
| **Kadane's** | Maximum Subarray (LeetCode 53), Maximum Circular Subarray Sum |
| **Binary Search** | Search in Rotated Sorted Array, Find First and Last Position, Koko Eating Bananas |

---

> **Next Steps:** Head to `linked-list/` to learn about dynamic, non-contiguous data structures.
