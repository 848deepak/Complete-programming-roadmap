# ✂️ Divide & Conquer Framework

## When to Use
- Problem can be **split into independent subproblems** of the same type
- Subproblems can be **solved independently** and **merged** efficiently
- Classic examples: merge sort, quicksort, binary search, closest pair

## How to Recognize
Keywords: *split*, *merge*, *halve*, *sorted halves*, *count across partition*.

## Divide & Conquer vs Regular Recursion
- D&C splits into **multiple independent** subproblems (usually 2)
- Regular recursion may have **dependent** or **single** subproblem

## Common Mistakes
1. **Inefficient merge step** — the merge must be O(n) or better
2. **Not splitting evenly** — uneven splits degrade to O(n²)
3. **Base case too late** — stop at size 1 (or 0), not size 2

---

## Template

```cpp
// C++ — Divide & Conquer Template
ResultType divideAndConquer(vector<int>& data, int lo, int hi) {
    // Base case
    if (lo >= hi) return baseResult;
    
    // Divide
    int mid = lo + (hi - lo) / 2;
    
    // Conquer (solve subproblems independently)
    ResultType leftResult  = divideAndConquer(data, lo, mid);
    ResultType rightResult = divideAndConquer(data, mid + 1, hi);
    
    // Combine (merge results)
    return merge(leftResult, rightResult, data, lo, mid, hi);
}
```

```java
static ResultType divideAndConquer(int[] data, int lo, int hi) {
    if (lo >= hi) return baseResult;
    int mid = lo + (hi - lo) / 2;
    ResultType left  = divideAndConquer(data, lo, mid);
    ResultType right = divideAndConquer(data, mid + 1, hi);
    return merge(left, right, data, lo, mid, hi);
}
```

---

## Example Problems

### 1. Merge Sort
```cpp
void mergeSort(vector<int>& a, int lo, int hi) {
    if (lo >= hi) return;
    int mid = (lo+hi)/2;
    mergeSort(a, lo, mid);
    mergeSort(a, mid+1, hi);
    // Merge two sorted halves
    vector<int> tmp; int i=lo, j=mid+1;
    while (i<=mid && j<=hi) tmp.push_back(a[i]<=a[j] ? a[i++] : a[j++]);
    while (i<=mid) tmp.push_back(a[i++]);
    while (j<=hi)  tmp.push_back(a[j++]);
    for (int k=lo;k<=hi;k++) a[k]=tmp[k-lo];
}
```
**T(n) = 2T(n/2) + O(n) → O(n log n)**

### 2. Count Inversions (Modified Merge Sort)
**Problem:** Count pairs (i,j) where i < j but a[i] > a[j].
**Key:** During merge, when a[j] < a[i], all remaining left-half elements are inversions.

### 3. Maximum Subarray Sum (Kadane's D&C variant)
**Problem:** Find max subarray sum.
**Apply:** Max is in left half, right half, or **crossing the midpoint**. Crossing case: extend left from mid, extend right from mid+1.

---

## Master Theorem (Complexity Guide)

| Recurrence | Complexity | Example |
|-----------|-----------|---------|
| T(n) = 2T(n/2) + O(n) | O(n log n) | Merge Sort |
| T(n) = 2T(n/2) + O(1) | O(n) | Binary Tree Traversal |
| T(n) = T(n/2) + O(1) | O(log n) | Binary Search |
| T(n) = 2T(n/2) + O(n²) | O(n²) | Naive closest pair |
