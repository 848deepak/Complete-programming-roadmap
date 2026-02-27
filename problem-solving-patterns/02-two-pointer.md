# 👆👆 Two Pointer Technique

## When to Use
- **Sorted array** problems: find pair with target sum, remove duplicates, merge
- **Partitioning**: separate elements meeting a condition
- **String palindrome** checks

## How to Recognize
Keywords: *pair*, *sorted*, *two ends*, *partition*, *in-place*, *palindrome*.

## Common Mistakes
1. **Using on unsorted data** — two pointer for pair-sum only works on sorted arrays
2. **Wrong movement direction** — always reason about which pointer to move and why
3. **Skipping duplicates incorrectly** — off-by-one when deduplicating

---

## Template — Opposite Direction (Two Ends)

```cpp
// C++ — Pair with target sum in sorted array
pair<int,int> twoSumSorted(vector<int>& arr, int target) {
    int left = 0, right = (int)arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target)      return {left, right};
        else if (sum < target)  left++;     // Need larger sum
        else                    right--;    // Need smaller sum
    }
    return {-1, -1};
}
```

```java
public static int[] twoSumSorted(int[] arr, int target) {
    int left = 0, right = arr.length - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return new int[]{left, right};
        else if (sum < target) left++;
        else right--;
    }
    return new int[]{-1, -1};
}
```

## Template — Same Direction (Slow-Fast)

```cpp
// C++ — Remove duplicates in-place from sorted array
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 0;  // Points to last unique element
    
    for (int fast = 1; fast < (int)nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            nums[++slow] = nums[fast];
        }
    }
    return slow + 1;
}
```

```java
public static int removeDuplicates(int[] nums) {
    if (nums.length == 0) return 0;
    int slow = 0;
    for (int fast = 1; fast < nums.length; fast++) {
        if (nums[fast] != nums[slow]) nums[++slow] = nums[fast];
    }
    return slow + 1;
}
```

---

## Example Problems

### 1. Container With Most Water
**Problem:** Given heights, find two lines that form container with most water.
**Apply:** Opposite-direction two pointer. Move the shorter line inward.

### 2. 3Sum (Triplets with Zero Sum)
**Problem:** Find all unique triplets summing to 0.
**Apply:** Fix one element, then two-pointer on remainder. Skip duplicates.

### 3. Trapping Rain Water
**Problem:** Compute trapped water in elevation map.
**Apply:** Two pointers from both ends. Track leftMax and rightMax.

---

## Decision Flowchart

```
Is the data sorted (or should it be)?
├── YES → Looking for pair/triplet?
│   ├── YES → Opposite-direction Two Pointer
│   └── NO  → Same-direction (slow-fast) for partitioning
└── NO  → Sort first if O(n log n) is acceptable, else use Hash Map
```
