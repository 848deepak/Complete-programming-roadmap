# 🎯 Edge Case Based Questions

> The difference between "works" and "production-ready." These are the edge cases that break naive solutions.

---

## 1. Integer Overflow

### The Trap
```cpp
int a = INT_MAX;    // 2,147,483,647
int b = a + 1;      // ❌ OVERFLOW → -2,147,483,648 (undefined in C++)

// Midpoint calculation
int mid = (lo + hi) / 2;  // ❌ Can overflow if lo+hi > INT_MAX

// ✅ Safe version
int mid = lo + (hi - lo) / 2;
```

### Java Difference
```java
int a = Integer.MAX_VALUE + 1;  // Wraps to Integer.MIN_VALUE (defined behavior in Java)
// But still gives WRONG ANSWERS
```

### 📌 Interview Tip
> Always use `lo + (hi - lo) / 2` for midpoint. Mention this proactively — interviewers love candidates who think about overflow.

---

## 2. Empty Input

| Data Structure | Empty Case | Check |
|---------------|-----------|-------|
| Array | `[]` | `arr.empty()` or `arr.length == 0` |
| String | `""` | `s.empty()` or `s.length() == 0` |
| Linked List | `null` head | `head == null` |
| Tree | `null` root | `root == null` |
| Graph | 0 nodes | `n == 0` |

### ⚠️ Trap
> Accessing `arr[0]` on an empty array = crash. Always check size first.

---

## 3. Single Element

```cpp
// Reverse array with 1 element → no-op (but code shouldn't crash)
// Find min & max of 1 element → both are that element
// Binary search with 1 element → check if it matches target
// Linked list with 1 node → head == tail, next == null
```

### 📌 Interview Tip
> Test your solution mentally with: **empty input, single element, two elements**. These three catch 90% of edge case bugs.

---

## 4. Negative Numbers

```cpp
// Modulo with negatives (C++ behavior):
-7 % 3  // = -1 in C++ (not +2!)

// ✅ Safe modulo:
int safeMod(int a, int m) { return ((a % m) + m) % m; }

// Binary search on answer — is lo always 0?
// Not for problems with negative values!
```

### Java Difference
```java
-7 % 3  // = -1 in Java too
Math.floorMod(-7, 3)  // = 2 ✅ (Java 8+)
```

---

## 5. Duplicate Elements

```cpp
// Binary search — finding FIRST occurrence vs ANY occurrence
// If duplicates exist, standard BS may return any of them
// Need lower_bound / upper_bound variants

// Two Sum — can same element be used twice?
// [3, 3], target=6 → depends on problem constraints!

// Sorting — stable vs unstable sort matters when duplicates have meaning
```

---

## 6. Very Large Input (10⁵ - 10⁹)

| Input Size | Max Acceptable Complexity |
|-----------|--------------------------|
| n ≤ 10 | O(n!) — brute force OK |
| n ≤ 20 | O(2ⁿ) — backtracking |
| n ≤ 500 | O(n³) |
| n ≤ 5000 | O(n²) |
| n ≤ 10⁶ | O(n log n) |
| n ≤ 10⁸ | O(n) |
| n > 10⁸ | O(log n) or O(1) |

### 📌 Interview Tip
> When you see `n ≤ 10⁵`, immediately rule out O(n²). When you see `n ≤ 10⁹`, you need O(log n) — almost certainly binary search.

---

## 7. Boundary Values

```cpp
// Array rotation: k == 0 → no change. k == n → no change. k > n → use k % n

// Array is already sorted → algorithms expecting unsorted may behave differently
// Array is reverse sorted → worst case for some sorting algorithms

// Graph: disconnected graph → BFS from one node won't visit all
// Tree: skewed tree (like a linked list) → O(n) height, not O(log n)
```

---

## 8. Floating Point Precision

```cpp
// ❌ Never compare floats with ==
double a = 0.1 + 0.2;
if (a == 0.3)  // FALSE! a ≈ 0.30000000000000004

// ✅ Use epsilon comparison
if (abs(a - 0.3) < 1e-9)  // TRUE
```

---

## Edge Case Checklist (Use Before Submitting)

- [ ] Empty input handled?
- [ ] Single element handled?
- [ ] All same elements?
- [ ] Negative numbers?
- [ ] Integer overflow possible?
- [ ] Very large input → correct complexity?
- [ ] Already sorted / reverse sorted?
- [ ] Duplicate elements?
- [ ] Floating point precision?
