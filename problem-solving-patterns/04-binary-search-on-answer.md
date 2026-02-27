# 🎯 Binary Search on Answer

## When to Use
- You need to **optimize** a value (minimize maximum / maximize minimum)
- The answer has a **monotonic feasibility** property: if X works, then X+1 also works (or vice versa)
- Direct computation is hard, but **checking if an answer is feasible** is easy

## How to Recognize
Keywords: *minimize the maximum*, *maximize the minimum*, *smallest/largest value such that*, *allocate/distribute optimally*.

## Common Mistakes
1. **Wrong search space** — lo and hi must bound ALL possible answers
2. **Wrong feasibility check** — the check function must be O(n) or better
3. **Off-by-one in lo/hi** — use `lo <= hi` pattern and track `ans` separately

---

## Template

```cpp
// C++ — Binary Search on Answer
bool isFeasible(vector<int>& data, int candidate) {
    // Return true if 'candidate' is a valid answer
    // This is the problem-specific greedy check
    return true; // placeholder
}

int binarySearchOnAnswer(vector<int>& data) {
    int lo = MIN_POSSIBLE_ANSWER;
    int hi = MAX_POSSIBLE_ANSWER;
    int ans = lo;  // or hi, depending on min/max
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        if (isFeasible(data, mid)) {
            ans = mid;       // mid works, try for better
            lo = mid + 1;    // For MAXIMIZING — search higher
            // hi = mid - 1; // For MINIMIZING — search lower
        } else {
            hi = mid - 1;    // For MAXIMIZING — mid too high
            // lo = mid + 1; // For MINIMIZING — mid too low
        }
    }
    return ans;
}
```

```java
public static int binarySearchOnAnswer(int[] data) {
    int lo = MIN_POSSIBLE, hi = MAX_POSSIBLE, ans = lo;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isFeasible(data, mid)) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    return ans;
}
```

---

## Example Problems

### 1. Aggressive Cows (Maximize Minimum Distance)
**Problem:** Place k cows in n stalls. Maximize the minimum distance between any two cows.
**Search space:** lo=1, hi=max_position-min_position. **Check:** Greedily place cows with gap ≥ mid.

### 2. Allocate Minimum Pages (Minimize Maximum)
**Problem:** Divide n books among k students. Minimize the maximum pages any student reads.
**Search space:** lo=max(pages), hi=sum(pages). **Check:** Greedily assign books, count students needed.

### 3. Koko Eating Bananas
**Problem:** Koko eats bananas at speed k. Find minimum k to finish all piles in h hours.
**Search space:** lo=1, hi=max(pile). **Check:** Sum of ceil(pile/mid) ≤ h.

---

## Key Insight

> The power of this pattern is **converting an optimization problem into a decision problem.**
> Instead of "what is the best answer?", you ask "is X a valid answer?" and binary search on X.
