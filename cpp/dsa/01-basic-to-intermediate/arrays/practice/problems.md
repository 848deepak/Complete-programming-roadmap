# 📦 Arrays — Practice Problems

> **Topic:** Arrays | **Level:** Easy → Hard | **Focus:** Interview-Ready Patterns
>
> Solutions are provided in **C++ and Java**. Each problem includes real-world relevance, a clear approach, edge cases, and complexity analysis.

---

## Table of Contents

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Two Sum](#1-two-sum) | 🟢 Easy | Hash Map |
| 2 | [Find Maximum & Minimum](#2-find-maximum--minimum) | 🟢 Easy | Linear Scan |
| 3 | [Reverse an Array](#3-reverse-an-array) | 🟢 Easy | Two Pointer |
| 4 | [Check Array is Sorted](#4-check-array-is-sorted) | 🟢 Easy | Linear Scan |
| 5 | [Remove Duplicates from Sorted Array](#5-remove-duplicates-from-sorted-array) | 🟢 Easy | Two Pointer |
| 6 | [Best Time to Buy and Sell Stock](#6-best-time-to-buy-and-sell-stock) | 🟡 Medium | Greedy / Sliding Window |
| 7 | [Subarray with Given Sum (Positive Numbers)](#7-subarray-with-given-sum-positive-numbers) | 🟡 Medium | Sliding Window |
| 8 | [Maximum Product Subarray](#8-maximum-product-subarray) | 🟡 Medium | Dynamic Programming |
| 9 | [3Sum — Find All Triplets with Zero Sum](#9-3sum--find-all-triplets-with-zero-sum) | 🟡 Medium | Sorting + Two Pointer |
| 10 | [Rotate Array by K Steps](#10-rotate-array-by-k-steps) | 🟡 Medium | Reversal Algorithm |
| 11 | [Trapping Rain Water](#11-trapping-rain-water) | 🔴 Hard | Two Pointer / Stack |
| 12 | [Merge k Sorted Arrays](#12-merge-k-sorted-arrays) | 🔴 Hard | Min Heap |
| 13 | [Longest Subarray with Equal 0s and 1s](#13-longest-subarray-with-equal-0s-and-1s) | 🔴 Hard | Prefix Sum + Hash Map |

---

## 🟢 EASY PROBLEMS

---

### 1. Two Sum

#### Problem Statement
Given an array of integers `nums` and a target integer `target`, return the **indices** of the two numbers that add up to the target. You may assume exactly one solution exists, and the same element cannot be used twice.

**Example:**
```
Input:  nums = [2, 7, 11, 15], target = 9
Output: [0, 1]   // nums[0] + nums[1] = 2 + 7 = 9
```

#### 🌍 Real-World Relevance
Used in financial systems to find two transactions whose sum matches a required amount. Fundamental hash map pattern — appears in almost every coding interview.

#### 💡 Approach
- **Brute Force (O(n²)):** Check every pair — too slow.
- **Optimized (O(n)):** Use a hash map. For each number, check if `target - num` already exists in the map.

#### ⚠️ Edge Cases
- Negative numbers in the array
- Target is 0 (e.g., `[-3, 3]` → valid)
- Very large array (10⁵ elements) — forces O(n) solution

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // value → index

    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];

        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};  // guaranteed to have a solution
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    auto res = twoSum(nums, target);
    cout << "[" << res[0] << ", " << res[1] << "]\n";  // [0, 1]
    return 0;
}
```

#### ✅ Java Solution
```java
import java.util.HashMap;
import java.util.Map;

public class TwoSum {
    public static int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> seen = new HashMap<>();  // value → index

        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];

            if (seen.containsKey(complement)) {
                return new int[]{seen.get(complement), i};
            }
            seen.put(nums[i], i);
        }
        return new int[]{};  // guaranteed to have a solution
    }

    public static void main(String[] args) {
        int[] nums = {2, 7, 11, 15};
        int[] result = twoSum(nums, 9);
        System.out.println("[" + result[0] + ", " + result[1] + "]");  // [0, 1]
    }
}
```

#### 📊 Complexity
| | Time | Space |
|--|------|-------|
| Brute Force | O(n²) | O(1) |
| **Optimized** | **O(n)** | **O(n)** |

---

### 2. Find Maximum & Minimum

#### Problem Statement
Given an unsorted array, find the **maximum** and **minimum** element using the **minimum number of comparisons**.

**Example:**
```
Input:  [3, 5, 1, 8, 2]
Output: max = 8, min = 1
```

#### 🌍 Real-World Relevance
Finding extremes in sensor readings, stock prices, or game scores. The "tournament method" teaches the principle of minimizing comparisons — critical for hardware-constrained systems.

#### 💡 Approach
- **Naive:** Two separate passes — 2(n-1) comparisons.
- **Optimized (Pair Comparison):** Compare elements in pairs, then compare each pair's larger to current max and smaller to current min. Total: **~1.5n** comparisons.

#### ⚠️ Edge Cases
- Array with a single element → max = min = that element
- All elements equal
- Negative numbers

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

pair<int, int> findMinMax(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {INT_MAX, INT_MIN};
    if (n == 1) return {nums[0], nums[0]};

    int minVal, maxVal;
    int start;

    // Initialize from first pair
    if (nums[0] < nums[1]) {
        minVal = nums[0];
        maxVal = nums[1];
    } else {
        minVal = nums[1];
        maxVal = nums[0];
    }
    start = 2;

    // Process remaining pairs
    for (int i = start; i + 1 < n; i += 2) {
        if (nums[i] < nums[i + 1]) {
            minVal = min(minVal, nums[i]);
            maxVal = max(maxVal, nums[i + 1]);
        } else {
            minVal = min(minVal, nums[i + 1]);
            maxVal = max(maxVal, nums[i]);
        }
    }

    // If odd number of elements, handle the last one
    if (n % 2 != 0) {
        minVal = min(minVal, nums[n - 1]);
        maxVal = max(maxVal, nums[n - 1]);
    }

    return {minVal, maxVal};
}

int main() {
    vector<int> nums = {3, 5, 1, 8, 2};
    auto [mn, mx] = findMinMax(nums);
    cout << "Min: " << mn << ", Max: " << mx << "\n";  // Min: 1, Max: 8
    return 0;
}
```

#### ✅ Java Solution
```java
public class MinMax {
    static int[] findMinMax(int[] nums) {
        int n = nums.length;
        if (n == 0) return new int[]{Integer.MAX_VALUE, Integer.MIN_VALUE};
        if (n == 1) return new int[]{nums[0], nums[0]};

        int minVal, maxVal;
        if (nums[0] < nums[1]) { minVal = nums[0]; maxVal = nums[1]; }
        else                   { minVal = nums[1]; maxVal = nums[0]; }

        for (int i = 2; i + 1 < n; i += 2) {
            if (nums[i] < nums[i + 1]) {
                minVal = Math.min(minVal, nums[i]);
                maxVal = Math.max(maxVal, nums[i + 1]);
            } else {
                minVal = Math.min(minVal, nums[i + 1]);
                maxVal = Math.max(maxVal, nums[i]);
            }
        }
        if (n % 2 != 0) {
            minVal = Math.min(minVal, nums[n - 1]);
            maxVal = Math.max(maxVal, nums[n - 1]);
        }
        return new int[]{minVal, maxVal};
    }

    public static void main(String[] args) {
        int[] result = findMinMax(new int[]{3, 5, 1, 8, 2});
        System.out.println("Min: " + result[0] + ", Max: " + result[1]);
    }
}
```

#### 📊 Complexity
| | Time | Space | Comparisons |
|--|------|-------|-------------|
| **Optimized** | **O(n)** | **O(1)** | **~1.5n** |

---

### 3. Reverse an Array

#### Problem Statement
Reverse an array **in-place** without using extra memory.

**Example:**
```
Input:  [1, 2, 3, 4, 5]
Output: [5, 4, 3, 2, 1]
```

#### 🌍 Real-World Relevance
String reversal (palindrome checks), undoing operation history (editor undo stacks), reversing command queues. The classic in-place two-pointer pattern appears in dozens of harder problems.

#### 💡 Approach
Use two pointers — `left` starting at 0, `right` at n-1. Swap and move inward until they meet.

#### ⚠️ Edge Cases
- Empty array
- Single element (no-op)
- Already reversed array

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
using namespace std;

void reverseArray(vector<int>& arr) {
    int left = 0, right = (int)arr.size() - 1;
    while (left < right) {
        swap(arr[left++], arr[right--]);
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    reverseArray(arr);
    for (int x : arr) cout << x << " ";  // 5 4 3 2 1
    return 0;
}
```

#### ✅ Java Solution
```java
public class ReverseArray {
    static void reverseArray(int[] arr) {
        int left = 0, right = arr.length - 1;
        while (left < right) {
            int temp = arr[left];
            arr[left++] = arr[right];
            arr[right--] = temp;
        }
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5};
        reverseArray(arr);
        for (int x : arr) System.out.print(x + " ");  // 5 4 3 2 1
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) — in-place |

---

### 4. Check Array is Sorted

#### Problem Statement
Return `true` if the array is sorted in **non-decreasing** order, `false` otherwise.

**Example:**
```
Input:  [1, 2, 2, 4, 5]  → true
Input:  [1, 3, 2, 4]     → false
```

#### 🌍 Real-World Relevance
Pre-validation step before binary search. Ensures data integrity in pipelines. Often used as a sub-problem inside more complex algorithms.

#### 💡 Approach
Single pass: compare each adjacent pair. Return `false` immediately on finding arr[i] > arr[i+1].

#### ⚠️ Edge Cases
- Empty array → `true` (vacuously sorted)
- Single element → `true`
- Array with duplicates → still sorted if non-decreasing

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
using namespace std;

bool isSorted(vector<int>& arr) {
    for (int i = 0; i + 1 < (int)arr.size(); i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

int main() {
    vector<int> a = {1, 2, 2, 4, 5};
    vector<int> b = {1, 3, 2, 4};
    cout << isSorted(a) << "\n";  // 1 (true)
    cout << isSorted(b) << "\n";  // 0 (false)
    return 0;
}
```

#### ✅ Java Solution
```java
public class CheckSorted {
    static boolean isSorted(int[] arr) {
        for (int i = 0; i + 1 < arr.length; i++) {
            if (arr[i] > arr[i + 1]) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        System.out.println(isSorted(new int[]{1, 2, 2, 4, 5}));  // true
        System.out.println(isSorted(new int[]{1, 3, 2, 4}));     // false
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 5. Remove Duplicates from Sorted Array

#### Problem Statement
Given a **sorted** array, remove duplicates **in-place** and return the new length. Elements beyond the new length don't matter.

**Example:**
```
Input:  [1, 1, 2, 3, 3, 4]
Output: length = 4, array = [1, 2, 3, 4, ...]
```

#### 🌍 Real-World Relevance
Database deduplication, log processing, removing duplicate entries from sorted result sets. Classic in-place two-pointer application.

#### 💡 Approach
Use a **slow pointer** `k` that tracks the position for the next unique element. A **fast pointer** `i` scans the array. When `nums[i] != nums[k-1]`, place `nums[i]` at `nums[k]` and increment `k`.

#### ⚠️ Edge Cases
- Empty array → return 0
- All elements same → return 1
- All elements unique → return n (no change)

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int k = 1;  // position for next unique element
    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] != nums[k - 1]) {
            nums[k++] = nums[i];
        }
    }
    return k;
}

int main() {
    vector<int> nums = {1, 1, 2, 3, 3, 4};
    int newLen = removeDuplicates(nums);
    cout << "New length: " << newLen << "\n";  // 4
    for (int i = 0; i < newLen; i++) cout << nums[i] << " ";  // 1 2 3 4
    return 0;
}
```

#### ✅ Java Solution
```java
public class RemoveDuplicates {
    static int removeDuplicates(int[] nums) {
        if (nums.length == 0) return 0;

        int k = 1;
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] != nums[k - 1]) {
                nums[k++] = nums[i];
            }
        }
        return k;
    }

    public static void main(String[] args) {
        int[] nums = {1, 1, 2, 3, 3, 4};
        int newLen = removeDuplicates(nums);
        System.out.println("New length: " + newLen);  // 4
        for (int i = 0; i < newLen; i++) System.out.print(nums[i] + " ");
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) — in-place |

---

## 🟡 MEDIUM PROBLEMS

---

### 6. Best Time to Buy and Sell Stock

#### Problem Statement
Given an array `prices` where `prices[i]` is the price of a stock on day `i`, find the **maximum profit** you can achieve by buying on one day and selling on a later day. Return 0 if no profit is possible.

**Example:**
```
Input:  [7, 1, 5, 3, 6, 4]
Output: 5   // Buy at 1, sell at 6
```

#### 🌍 Real-World Relevance
Core algorithmic concept behind trading systems. Also models any "buy low, sell later" optimization (equipment, commodities). Pattern: tracking a historical minimum while computing current gain.

#### 💡 Approach
Track `minPrice` seen so far. For each day, compute `profit = price - minPrice`. Update `maxProfit` if this is better. Update `minPrice` if current price is lower.

#### ⚠️ Edge Cases
- Prices strictly decreasing → return 0
- Only 1 price → return 0
- All prices equal → return 0

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;

    for (int price : prices) {
        if (price < minPrice) {
            minPrice = price;           // Found cheaper buying point
        } else {
            maxProfit = max(maxProfit, price - minPrice);  // Check profit
        }
    }
    return maxProfit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << maxProfit(prices) << "\n";  // 5
    return 0;
}
```

#### ✅ Java Solution
```java
public class BestTimeToBuyStock {
    public static int maxProfit(int[] prices) {
        int minPrice = Integer.MAX_VALUE;
        int maxProfit = 0;

        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;
            } else {
                maxProfit = Math.max(maxProfit, price - minPrice);
            }
        }
        return maxProfit;
    }

    public static void main(String[] args) {
        System.out.println(maxProfit(new int[]{7, 1, 5, 3, 6, 4}));  // 5
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 7. Subarray with Given Sum (Positive Numbers)

#### Problem Statement
Given an array of **positive integers** and a target sum, find a **contiguous subarray** that adds up to the target. Return the start and end indices (1-indexed). Return `-1` if none found.

**Example:**
```
Input:  arr = [1, 4, 20, 3, 10, 5], target = 33
Output: [3, 5]   // arr[2]+arr[3]+arr[4] = 20+3+10 = 33 (1-indexed: 3 to 5)
```

#### 🌍 Real-World Relevance
Network packet inspection (finding a burst of data matching a size), financial ledger analysis, log time-window queries. Classic sliding window pattern.

#### 💡 Approach
**Sliding Window:** Maintain a window `[left, right]`. Expand right to add elements. If sum exceeds target, shrink from left. Since all elements are positive, the window sum is monotonically related to window size.

#### ⚠️ Edge Cases
- No valid subarray → return `{-1, -1}`
- Single element equals target
- All elements larger than target → return `{-1, -1}`
- Target = 0 (not meaningful for positive arrays)

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
using namespace std;

pair<int,int> subarrayWithSum(vector<int>& arr, int target) {
    int left = 0, currSum = 0;

    for (int right = 0; right < (int)arr.size(); right++) {
        currSum += arr[right];

        // Shrink window from left while sum exceeds target
        while (currSum > target && left < right) {
            currSum -= arr[left++];
        }

        if (currSum == target) {
            return {left + 1, right + 1};  // 1-indexed
        }
    }
    return {-1, -1};
}

int main() {
    vector<int> arr = {1, 4, 20, 3, 10, 5};
    auto [s, e] = subarrayWithSum(arr, 33);
    if (s != -1) cout << "Found at [" << s << ", " << e << "]\n";  // [3, 5]
    else cout << "Not found\n";
    return 0;
}
```

#### ✅ Java Solution
```java
public class SubarrayWithSum {
    static int[] subarrayWithSum(int[] arr, int target) {
        int left = 0, currSum = 0;

        for (int right = 0; right < arr.length; right++) {
            currSum += arr[right];

            while (currSum > target && left < right) {
                currSum -= arr[left++];
            }

            if (currSum == target) {
                return new int[]{left + 1, right + 1};  // 1-indexed
            }
        }
        return new int[]{-1, -1};
    }

    public static void main(String[] args) {
        int[] result = subarrayWithSum(new int[]{1, 4, 20, 3, 10, 5}, 33);
        if (result[0] != -1)
            System.out.println("Found at [" + result[0] + ", " + result[1] + "]");
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

> **Note:** Each element is added/removed from the window at most once.

---

### 8. Maximum Product Subarray

#### Problem Statement
Find the contiguous subarray that has the **largest product** and return that product.

**Example:**
```
Input:  [2, 3, -2, 4]
Output: 6    // [2, 3]
Input:  [-2, 0, -1]
Output: 0
```

#### 🌍 Real-World Relevance
Signal processing (finding peak signal amplification sequences), physics simulations. Key DP insight: tracking both max AND min because multiplying two negatives gives a positive.

#### 💡 Approach
Track both `maxProd` and `minProd` at each index (because a large negative × another negative = large positive). At each step:
- `newMax = max(nums[i], maxProd * nums[i], minProd * nums[i])`
- `newMin = min(nums[i], maxProd * nums[i], minProd * nums[i])`

#### ⚠️ Edge Cases
- Array contains zeros → resets the product
- All negative numbers (even count → positive product)
- Single element

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxProduct(vector<int>& nums) {
    int maxProd = nums[0], minProd = nums[0], result = nums[0];

    for (int i = 1; i < (int)nums.size(); i++) {
        // When multiplying by negative, max and min swap
        if (nums[i] < 0) swap(maxProd, minProd);

        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);
        result  = max(result, maxProd);
    }
    return result;
}

int main() {
    vector<int> nums = {2, 3, -2, 4};
    cout << maxProduct(nums) << "\n";  // 6

    vector<int> nums2 = {-2, 0, -1};
    cout << maxProduct(nums2) << "\n";  // 0
    return 0;
}
```

#### ✅ Java Solution
```java
public class MaxProductSubarray {
    public static int maxProduct(int[] nums) {
        int maxProd = nums[0], minProd = nums[0], result = nums[0];

        for (int i = 1; i < nums.length; i++) {
            if (nums[i] < 0) {
                int temp = maxProd;
                maxProd = minProd;
                minProd = temp;
            }
            maxProd = Math.max(nums[i], maxProd * nums[i]);
            minProd = Math.min(nums[i], minProd * nums[i]);
            result  = Math.max(result, maxProd);
        }
        return result;
    }

    public static void main(String[] args) {
        System.out.println(maxProduct(new int[]{2, 3, -2, 4}));   // 6
        System.out.println(maxProduct(new int[]{-2, 0, -1}));     // 0
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 9. 3Sum — Find All Triplets with Zero Sum

#### Problem Statement
Given an array, find **all unique triplets** `[a, b, c]` such that `a + b + c = 0`. The solution set must not contain duplicate triplets.

**Example:**
```
Input:  [-1, 0, 1, 2, -1, -4]
Output: [[-1, -1, 2], [-1, 0, 1]]
```

#### 🌍 Real-World Relevance
Collision detection in physics engines, finding balanced partitions in distributed systems. Extends the Two Sum pattern to three elements — a must-know interview problem.

#### 💡 Approach
1. Sort the array.
2. Fix one element `nums[i]`, then use Two Pointer on `nums[i+1..n-1]` to find pairs summing to `-nums[i]`.
3. Skip duplicates carefully.

#### ⚠️ Edge Cases
- Array shorter than 3 → return empty
- All zeros `[0,0,0]` → one valid triplet `[0,0,0]`
- Large arrays with many duplicates → must skip correctly

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 0; i < n - 2; i++) {
        // Skip duplicate values for the fixed element
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        // Optimization: if smallest three are positive, stop
        if (nums[i] > 0) break;

        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                // Skip duplicates for left and right
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto res = threeSum(nums);
    for (auto& t : res)
        cout << "[" << t[0] << ", " << t[1] << ", " << t[2] << "]\n";
    return 0;
}
```

#### ✅ Java Solution
```java
import java.util.*;

public class ThreeSum {
    public static List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(nums);
        int n = nums.length;

        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            if (nums[i] > 0) break;

            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }

    public static void main(String[] args) {
        int[] nums = {-1, 0, 1, 2, -1, -4};
        System.out.println(threeSum(nums));  // [[-1,-1,2],[-1,0,1]]
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n²) | O(1) extra (output excluded) |

---

### 10. Rotate Array by K Steps

#### Problem Statement
Rotate array `nums` to the **right** by `k` steps **in-place**.

**Example:**
```
Input:  nums = [1, 2, 3, 4, 5, 6, 7], k = 3
Output: [5, 6, 7, 1, 2, 3, 4]
```

#### 🌍 Real-World Relevance
Circular buffer management in OS kernels and embedded systems. Ring queues in networking. Understanding the reversal trick is a key interview differentiator.

#### 💡 Approach — Reversal Algorithm (O(1) space)
1. Handle `k = k % n`.
2. Reverse the entire array.
3. Reverse the first `k` elements.
4. Reverse the remaining `n-k` elements.

#### ⚠️ Edge Cases
- `k = 0` or `k = n` → no effective change
- `k > n` → use `k % n`
- Single element array

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    if (k == 0) return;

    reverse(nums.begin(), nums.end());           // Step 1: reverse all
    reverse(nums.begin(), nums.begin() + k);     // Step 2: reverse first k
    reverse(nums.begin() + k, nums.end());       // Step 3: reverse rest
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    rotate(nums, 3);
    for (int x : nums) cout << x << " ";  // 5 6 7 1 2 3 4
    return 0;
}
```

#### ✅ Java Solution
```java
public class RotateArray {
    static void reverse(int[] nums, int left, int right) {
        while (left < right) {
            int temp = nums[left];
            nums[left++] = nums[right];
            nums[right--] = temp;
        }
    }

    public static void rotate(int[] nums, int k) {
        int n = nums.length;
        k %= n;
        if (k == 0) return;

        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3, 4, 5, 6, 7};
        rotate(nums, 3);
        for (int x : nums) System.out.print(x + " ");  // 5 6 7 1 2 3 4
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) — in-place |

---

## 🔴 HARD PROBLEMS

---

### 11. Trapping Rain Water

#### Problem Statement
Given an elevation map represented by array `height`, compute how much water can be trapped after rain.

**Example:**
```
Input:  [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
Output: 6
```

#### 🌍 Real-World Relevance
Civil engineering simulations, terrain analysis in GIS systems, game world flood simulation. One of the most famous array problems — tests ability to think in complementary directions simultaneously.

#### 💡 Approaches

| Approach | Time | Space |
|---------|------|-------|
| Precompute left/right max arrays | O(n) | O(n) |
| **Two Pointer (optimal)** | **O(n)** | **O(1)** |

**Two Pointer Logic:**
- Maintain `left`, `right` pointers, `leftMax`, `rightMax`.
- If `height[left] < height[right]`: water at left = `leftMax - height[left]`. Move left.
- Else: water at right = `rightMax - height[right]`. Move right.

#### ⚠️ Edge Cases
- Empty or single element → 0
- Array with no "valleys" (monotonically increasing or decreasing) → 0
- Large flat plateaus

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
using namespace std;

int trap(vector<int>& height) {
    int left = 0, right = (int)height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];       // Update wall
            } else {
                water += leftMax - height[left];  // Trapped water
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    return water;
}

int main() {
    vector<int> h = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(h) << "\n";  // 6
    return 0;
}
```

#### ✅ Java Solution
```java
public class TrappingRainWater {
    public static int trap(int[] height) {
        int left = 0, right = height.length - 1;
        int leftMax = 0, rightMax = 0, water = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) leftMax = height[left];
                else water += leftMax - height[left];
                left++;
            } else {
                if (height[right] >= rightMax) rightMax = height[right];
                else water += rightMax - height[right];
                right--;
            }
        }
        return water;
    }

    public static void main(String[] args) {
        System.out.println(trap(new int[]{0,1,0,2,1,0,1,3,2,1,2,1}));  // 6
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 12. Merge k Sorted Arrays

#### Problem Statement
Given `k` sorted arrays, merge them into a single sorted array efficiently.

**Example:**
```
Input:  [[1, 4, 7], [2, 5, 8], [3, 6, 9]]
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9]
```

#### 🌍 Real-World Relevance
Database merge joins (merging results from distributed shards), external sorting of large files that don't fit in memory, merging sorted logs from multiple servers. The min-heap approach is used in real production merge operations.

#### 💡 Approach — Min Heap
Push the first element of each array into a min heap. Repeatedly extract the minimum, add to result, and push the next element from the same array.

#### ⚠️ Edge Cases
- Empty arrays in input
- k = 1 → return original
- Arrays of very different lengths
- Duplicate values across arrays

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> mergeKSorted(vector<vector<int>>& arrays) {
    // Min-heap: {value, arrayIndex, elementIndex}
    using T = tuple<int, int, int>;
    priority_queue<T, vector<T>, greater<T>> minHeap;

    // Push first element from each array
    for (int i = 0; i < (int)arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        auto [val, arrIdx, elemIdx] = minHeap.top();
        minHeap.pop();
        result.push_back(val);

        // Push next element from the same array
        if (elemIdx + 1 < (int)arrays[arrIdx].size()) {
            minHeap.push({arrays[arrIdx][elemIdx + 1], arrIdx, elemIdx + 1});
        }
    }
    return result;
}

int main() {
    vector<vector<int>> arrays = {{1,4,7},{2,5,8},{3,6,9}};
    auto res = mergeKSorted(arrays);
    for (int x : res) cout << x << " ";  // 1 2 3 4 5 6 7 8 9
    return 0;
}
```

#### ✅ Java Solution
```java
import java.util.*;

public class MergeKSortedArrays {
    public static int[] mergeKSorted(int[][] arrays) {
        // PriorityQueue: {value, arrayIndex, elementIndex}
        PriorityQueue<int[]> minHeap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        int totalSize = 0;

        for (int i = 0; i < arrays.length; i++) {
            if (arrays[i].length > 0) {
                minHeap.offer(new int[]{arrays[i][0], i, 0});
                totalSize += arrays[i].length;
            }
        }

        int[] result = new int[totalSize];
        int idx = 0;

        while (!minHeap.isEmpty()) {
            int[] top = minHeap.poll();
            result[idx++] = top[0];
            int arrIdx = top[1], elemIdx = top[2];

            if (elemIdx + 1 < arrays[arrIdx].length) {
                minHeap.offer(new int[]{arrays[arrIdx][elemIdx + 1], arrIdx, elemIdx + 1});
            }
        }
        return result;
    }

    public static void main(String[] args) {
        int[][] arrays = {{1,4,7},{2,5,8},{3,6,9}};
        System.out.println(Arrays.toString(mergeKSorted(arrays)));
    }
}
```

#### 📊 Complexity
Let N = total elements, k = number of arrays.

| Time | Space |
|------|-------|
| O(N log k) | O(k) for heap + O(N) output |

---

### 13. Longest Subarray with Equal 0s and 1s

#### Problem Statement
Given a binary array (only `0s` and `1s`), find the length of the **longest contiguous subarray** with equal numbers of 0s and 1s.

**Example:**
```
Input:  [0, 1, 0, 1, 1, 0, 0]
Output: 6    // subarray [0,1,0,1,1,0] has 3 zeros and 3 ones
```

#### 🌍 Real-World Relevance
Balancing load in distributed systems (0 = server A, 1 = server B), analyzing equal-distribution windows in A/B testing data, packet-level analysis.

#### 💡 Approach — Prefix Sum + Hash Map
Replace 0s with -1. Now the problem becomes: **find the longest subarray with sum = 0**.
Use a prefix sum and store the **first occurrence** of each prefix sum. If the same prefix sum appears again at index `i`, the subarray between those indices sums to 0.

#### ⚠️ Edge Cases
- All 0s or all 1s → return 0
- Empty array → return 0
- Alternating `[0,1,0,1]` → full array is valid

#### ✅ C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int longestSubarrayEqualZeroOne(vector<int>& nums) {
    // Replace 0 with -1 to use prefix sum trick
    unordered_map<int, int> firstOccurrence;
    firstOccurrence[0] = -1;  // prefix sum of 0 before any element

    int prefixSum = 0, maxLen = 0;

    for (int i = 0; i < (int)nums.size(); i++) {
        prefixSum += (nums[i] == 0) ? -1 : 1;

        if (firstOccurrence.count(prefixSum)) {
            // Subarray from firstOccurrence[prefixSum]+1 to i has sum = 0
            maxLen = max(maxLen, i - firstOccurrence[prefixSum]);
        } else {
            firstOccurrence[prefixSum] = i;  // Store first occurrence only
        }
    }
    return maxLen;
}

int main() {
    vector<int> nums = {0, 1, 0, 1, 1, 0, 0};
    cout << longestSubarrayEqualZeroOne(nums) << "\n";  // 6
    return 0;
}
```

#### ✅ Java Solution
```java
import java.util.HashMap;
import java.util.Map;

public class LongestSubarrayEqualZeroOne {
    public static int longestSubarray(int[] nums) {
        Map<Integer, Integer> firstOccurrence = new HashMap<>();
        firstOccurrence.put(0, -1);

        int prefixSum = 0, maxLen = 0;

        for (int i = 0; i < nums.length; i++) {
            prefixSum += (nums[i] == 0) ? -1 : 1;

            if (firstOccurrence.containsKey(prefixSum)) {
                maxLen = Math.max(maxLen, i - firstOccurrence.get(prefixSum));
            } else {
                firstOccurrence.put(prefixSum, i);
            }
        }
        return maxLen;
    }

    public static void main(String[] args) {
        System.out.println(longestSubarray(new int[]{0, 1, 0, 1, 1, 0, 0}));  // 6
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(n) for hash map |

---

## 🗺️ Pattern Summary for Arrays

| Pattern | Problems Using It |
|---------|------------------|
| Hash Map | Two Sum, Longest Subarray (0s & 1s) |
| Two Pointer | Reverse Array, Remove Duplicates, 3Sum, Rotate Array, Trapping Rain Water |
| Sliding Window | Subarray with Given Sum |
| Greedy | Best Time to Buy & Sell Stock |
| DP (tracking local state) | Maximum Product Subarray |
| Min Heap | Merge k Sorted Arrays |
| Prefix Sum | Longest Subarray (Equal 0s & 1s) |

---

*Next: [Linked List Practice](../../linked-list/practice/problems.md) →*
