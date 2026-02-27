# ⏱️ Time Complexity — Tricky Interview Questions

> Beyond O(n) and O(log n) — the subtle analysis questions interviewers use to test deep understanding.

---

## 1. Hidden Loops

### Question: What's the time complexity?
```cpp
for (int i = 1; i < n; i *= 2)   // O(log n)
    for (int j = 0; j < i; j++)  // runs 1+2+4+...+n times total
        // work
```

### ⚠️ Trap
> Students say O(n log n). **Correct answer: O(n)**.
> Sum: 1 + 2 + 4 + ... + n = 2n - 1 ≈ O(n). Geometric series, not n × log n.

---

## 2. String Concatenation

```java
// What's the complexity?
String s = "";
for (int i = 0; i < n; i++) {
    s += "a";  // Creates new string EACH TIME
}
```

### Answer: **O(n²)** not O(n)!
> Each `+=` copies the entire string. Copies: 1 + 2 + 3 + ... + n = O(n²).
> **Fix:** Use `StringBuilder` → O(n).

### 📌 Interview Tip
> In Java, `String` is immutable. Concatenation in a loop is **always** O(n²). Use `StringBuilder`.

---

## 3. Amortized Analysis

### Example: Dynamic Array (ArrayList) `.add()`

| Operation | Cost |
|-----------|------|
| Normal add | O(1) |
| Resize add (when full) | O(n) — copy all elements |
| **Amortized per add** | **O(1)** |

> If array doubles when full: n inserts trigger resizes at 1, 2, 4, 8, ..., n.
> Total copies: 1+2+4+...+n ≈ 2n. Average per operation = 2n/n = O(1).

### 📌 Interview Tip
> "Amortized" means average over a sequence of operations, NOT average case. It's a **guarantee**: even the worst case averages out.

---

## 4. Hash Map Operations

### Question: "Is HashMap O(1)?"

| | Average | Worst |
|--|---------|-------|
| `get`/`put` | O(1) | O(n)* |

> *Worst case is O(n) with all collisions in one bucket. But Java 8+ converts long chains to **balanced trees** → worst case O(log n).

### ⚠️ Trap
> Students say hashmap is always O(1). Interviewers will ask about collision handling and worst-case scenarios.

---

## 5. Recursion Complexity

### Fibonacci (Naive)
```cpp
int fib(int n) { return n<=1 ? n : fib(n-1)+fib(n-2); }
```
**Complexity: O(2ⁿ)** — exponential! Each call branches into two.

### Fibonacci (Memoized)
```cpp
int fib(int n, vector<int>& memo) {
    if (memo[n]!=-1) return memo[n];
    return memo[n] = fib(n-1,memo)+fib(n-2,memo);
}
```
**Complexity: O(n)** — each subproblem solved once.

### Master Theorem Quick Reference

| Recurrence | Complexity |
|-----------|-----------|
| T(n) = T(n/2) + O(1) | O(log n) |
| T(n) = T(n-1) + O(1) | O(n) |
| T(n) = 2T(n/2) + O(n) | O(n log n) |
| T(n) = 2T(n-1) + O(1) | O(2ⁿ) |
| T(n) = T(n-1) + O(n) | O(n²) |

---

## 6. Sorting Lower Bound

### Question: "Can you sort faster than O(n log n)?"

> **Comparison-based sorting:** O(n log n) is a proven lower bound (information-theoretic argument: n! permutations need log(n!) ≈ n log n comparisons).
>
> **Non-comparison sorting:** Counting sort, Radix sort = O(n + k) where k is the range. But only works for integers with bounded range.

---

## 7. Log Base Doesn't Matter

### Question: "Is O(log₂n) different from O(log₁₀n)?"

> **No.** log₂n = log₁₀n / log₁₀2 = constant × log₁₀n. Constants are dropped in Big-O.
>
> All logarithmic bases are equivalent in Big-O: O(log n) regardless of base.

---

## 8. Common Complexity Ranking

```
O(1) < O(log n) < O(√n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2ⁿ) < O(n!)
```

| Complexity | n=10⁶ operations |
|-----------|-----------------|
| O(n) | 10⁶ ✅ |
| O(n log n) | ~2×10⁷ ✅ |
| O(n²) | 10¹² ❌ (too slow) |
| O(2ⁿ) | heat death of universe |
