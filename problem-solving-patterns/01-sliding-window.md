# 🪟 Sliding Window Pattern

## When to Use
- Finding **subarray/substring** that satisfies a condition (max/min length, sum, distinct count)
- The data is **contiguous** (not subsequence)
- Problem involves **optimization over contiguous elements**

## How to Recognize
Look for keywords: *subarray*, *substring*, *contiguous*, *window of size k*, *maximum/minimum sum*, *at most k distinct*.

## Two Variants

### Fixed Size Window
```
Window size is given (k). Slide one element at a time.
```

### Variable Size Window
```
Window grows/shrinks based on a condition. Find max/min window size.
```

## Common Mistakes
1. **Off-by-one on window boundaries** — window starts processing results at `i >= k-1` for fixed, not `i >= k`
2. **Not shrinking properly** — forgetting to update state when left pointer moves
3. **Using this for non-contiguous** — subsequence problems need DP, not sliding window

---

## Template — Fixed Size Window

```cpp
// C++ — Fixed window of size k
int fixedWindow(vector<int>& nums, int k) {
    int windowSum = 0, result = INT_MIN;
    
    for (int i = 0; i < (int)nums.size(); i++) {
        windowSum += nums[i];           // Expand: add right element
        
        if (i >= k) {
            windowSum -= nums[i - k];   // Shrink: remove leftmost
        }
        
        if (i >= k - 1) {
            result = max(result, windowSum);  // Window is full, record answer
        }
    }
    return result;
}
```

```java
// Java — Fixed window of size k
public static int fixedWindow(int[] nums, int k) {
    int windowSum = 0, result = Integer.MIN_VALUE;
    for (int i = 0; i < nums.length; i++) {
        windowSum += nums[i];
        if (i >= k) windowSum -= nums[i - k];
        if (i >= k - 1) result = Math.max(result, windowSum);
    }
    return result;
}
```

## Template — Variable Size Window

```cpp
// C++ — Find smallest window with sum >= target
int variableWindow(vector<int>& nums, int target) {
    int left = 0, windowSum = 0, minLen = INT_MAX;
    
    for (int right = 0; right < (int)nums.size(); right++) {
        windowSum += nums[right];       // Expand
        
        while (windowSum >= target) {   // Shrink while condition holds
            minLen = min(minLen, right - left + 1);
            windowSum -= nums[left++];
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}
```

```java
// Java — Variable window
public static int variableWindow(int[] nums, int target) {
    int left = 0, windowSum = 0, minLen = Integer.MAX_VALUE;
    for (int right = 0; right < nums.length; right++) {
        windowSum += nums[right];
        while (windowSum >= target) {
            minLen = Math.min(minLen, right - left + 1);
            windowSum -= nums[left++];
        }
    }
    return minLen == Integer.MAX_VALUE ? 0 : minLen;
}
```

---

## Example Problems

### 1. Maximum Sum Subarray of Size K (Fixed)
**Problem:** Find maximum sum of any contiguous subarray of size k.
**Apply template:** Fixed window, track `max(result, windowSum)`.

### 2. Minimum Window Substring (Variable)
**Problem:** Find smallest substring of `s` containing all characters of `t`.
**Key twist:** Use a frequency map for the condition check. Expand right to "satisfy", shrink left to "minimize".

### 3. Longest Substring Without Repeating Characters (Variable)
**Problem:** Longest substring with all unique characters.
**Key twist:** Use a hash set. Shrink left when duplicate is found.

---

## Decision Flowchart

```
Is the problem about CONTIGUOUS subarray/substring?
├── YES → Is window size fixed?
│   ├── YES → Fixed Sliding Window
│   └── NO  → Variable Sliding Window (expand right, shrink left)
└── NO  → Try Two Pointer, DP, or other pattern
```
