// ============================================================
// DSA | Java → Arrays: All Key Techniques
// ============================================================
// DESCRIPTION:
//   Covers all essential array operations and techniques:
//   - Traversal, insertion, deletion
//   - Linear and binary search
//   - Two pointer technique
//   - Prefix sum queries
//   - Kadane's Algorithm (max subarray)
//   - Sliding window
//
// COMPILE & RUN:
//   javac Arrays.java && java Arrays
//
// SAMPLE OUTPUT:
//   Max subarray sum (Kadane): 6
//   Two sum indices: [0, 1]
// ============================================================

import java.util.*;

public class Arrays {

    // ============================================================
    // 1. BASIC OPERATIONS: INSERT & DELETE
    // ============================================================

    /**
     * Inserts val at position idx in arr (shifted right, last element lost).
     * Time: O(n)  |  Space: O(1)
     */
    static void insertAt(int[] arr, int val, int idx, int size) {
        for (int i = size - 1; i > idx; i--)
            arr[i] = arr[i - 1];   // shift right
        arr[idx] = val;
    }

    /**
     * Deletes element at idx; returns new logical size.
     * Time: O(n)
     */
    static int deleteAt(int[] arr, int idx, int size) {
        for (int i = idx; i < size - 1; i++)
            arr[i] = arr[i + 1];   // shift left
        return size - 1;
    }

    // ============================================================
    // 2. BINARY SEARCH (requires sorted array)
    // ============================================================

    /**
     * Iterative binary search.
     * Time: O(log n)  |  Space: O(1)
     * @return index of target, or -1 if not found
     */
    static int binarySearch(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if      (arr[mid] == target) return mid;
            else if (arr[mid]  < target) low = mid + 1;
            else                         high = mid - 1;
        }
        return -1;
    }

    /**
     * First occurrence in sorted array with duplicates.
     * Time: O(log n)
     */
    static int firstOccurrence(int[] arr, int target) {
        int low = 0, high = arr.length - 1, result = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == target) { result = mid; high = mid - 1; }
            else if (arr[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return result;
    }

    // ============================================================
    // 3. PREFIX SUM — O(1) range queries after O(n) preprocessing
    // ============================================================

    static int[] buildPrefixSum(int[] arr) {
        int n = arr.length;
        int[] prefix = new int[n + 1];  // prefix[0] = 0 (empty prefix)
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + arr[i];
        return prefix;
    }

    /** Returns sum of arr[l..r] inclusive. O(1) */
    static int rangeSum(int[] prefix, int l, int r) {
        return prefix[r + 1] - prefix[l];
    }

    /** Count subarrays with sum == k using prefix sum + HashMap */
    static int subarraySumK(int[] arr, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        freq.put(0, 1);
        int sum = 0, count = 0;
        for (int x : arr) {
            sum += x;
            count += freq.getOrDefault(sum - k, 0);
            freq.merge(sum, 1, Integer::sum);
        }
        return count;
    }

    // ============================================================
    // 4. TWO POINTER TECHNIQUE
    // ============================================================

    /** Find pair with given sum in SORTED array. O(n) */
    static int[] twoSum(int[] arr, int target) {
        int left = 0, right = arr.length - 1;
        while (left < right) {
            int sum = arr[left] + arr[right];
            if      (sum == target) return new int[]{left, right};
            else if (sum  < target) left++;
            else                    right--;
        }
        return new int[]{-1, -1};
    }

    /** Remove duplicates from sorted array in-place. O(n) */
    static int removeDuplicates(int[] arr) {
        if (arr.length == 0) return 0;
        int slow = 0;
        for (int fast = 1; fast < arr.length; fast++) {
            if (arr[fast] != arr[slow])
                arr[++slow] = arr[fast];
        }
        return slow + 1;
    }

    /** Trap rain water. O(n) time O(1) space */
    static int trapRainWater(int[] h) {
        int left = 0, right = h.length - 1;
        int maxLeft = 0, maxRight = 0, water = 0;
        while (left <= right) {
            if (h[left] <= h[right]) {
                if (h[left] >= maxLeft) maxLeft = h[left];
                else water += maxLeft - h[left];
                left++;
            } else {
                if (h[right] >= maxRight) maxRight = h[right];
                else water += maxRight - h[right];
                right--;
            }
        }
        return water;
    }

    // ============================================================
    // 5. KADANE'S ALGORITHM — Maximum Subarray Sum
    // ============================================================

    /**
     * Returns maximum subarray sum (handles all negatives).
     * Time: O(n)  |  Space: O(1)
     */
    static int kadane(int[] arr) {
        int maxSum = arr[0], current = arr[0];
        for (int i = 1; i < arr.length; i++) {
            current = Math.max(arr[i], current + arr[i]);
            maxSum  = Math.max(maxSum, current);
        }
        return maxSum;
    }

    /** Kadane with start/end indices */
    static int[] kadaneWithIndices(int[] arr) {
        int maxSum = arr[0], current = arr[0];
        int start = 0, end = 0, tempStart = 0;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > current + arr[i]) {
                current = arr[i];
                tempStart = i;
            } else {
                current += arr[i];
            }
            if (current > maxSum) {
                maxSum = current;
                start = tempStart;
                end = i;
            }
        }
        return new int[]{maxSum, start, end};
    }

    // ============================================================
    // 6. SLIDING WINDOW — Maximum sum of subarray of size k
    // ============================================================

    /** Max sum of contiguous subarray of size k. O(n) */
    static int maxSumWindow(int[] arr, int k) {
        int windowSum = 0;
        for (int i = 0; i < k; i++) windowSum += arr[i];
        int maxSum = windowSum;
        for (int i = k; i < arr.length; i++) {
            windowSum += arr[i] - arr[i - k];    // slide: add new, remove old
            maxSum = Math.max(maxSum, windowSum);
        }
        return maxSum;
    }

    /** Length of longest subarray with sum ≤ k (two pointer). O(n) */
    static int longestSubarraySumLE(int[] arr, int k) {
        int left = 0, sum = 0, maxLen = 0;
        for (int right = 0; right < arr.length; right++) {
            sum += arr[right];
            while (sum > k) sum -= arr[left++];
            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    // ============================================================
    // 7. MATRIX OPERATIONS
    // ============================================================

    /** Transpose n×n matrix in-place */
    static void transpose(int[][] m) {
        int n = m.length;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int tmp = m[i][j]; m[i][j] = m[j][i]; m[j][i] = tmp;
            }
    }

    /** Rotate n×n matrix 90° clockwise in-place */
    static void rotate90CW(int[][] m) {
        transpose(m);
        for (int[] row : m) {
            int left = 0, right = row.length - 1;
            while (left < right) { int tmp = row[left]; row[left++] = row[right]; row[right--] = tmp; }
        }
    }

    /** Spiral order traversal */
    static List<Integer> spiral(int[][] m) {
        List<Integer> res = new ArrayList<>();
        int top = 0, bottom = m.length - 1, left = 0, right = m[0].length - 1;
        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; j++) res.add(m[top][j]); top++;
            for (int i = top; i <= bottom; i++) res.add(m[i][right]); right--;
            if (top <= bottom) { for (int j = right; j >= left; j--) res.add(m[bottom][j]); bottom--; }
            if (left <= right) { for (int i = bottom; i >= top; i--) res.add(m[i][left]); left++; }
        }
        return res;
    }

    // ============================================================
    // HELPER: print array
    // ============================================================
    static void print(String label, int[] arr, int len) {
        System.out.print("  " + label + ": [");
        for (int i = 0; i < len; i++)
            System.out.print(arr[i] + (i + 1 < len ? "," : ""));
        System.out.println("]");
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {

        // --- Insert / Delete ---
        System.out.println("=== INSERT & DELETE ===");
        int[] arr = {10, 20, 40, 50, 0};   // last slot empty
        int size = 4;
        insertAt(arr, 30, 2, size); size++;
        print("After insert(30, idx=2)", arr, size);
        size = deleteAt(arr, 1, size);
        print("After delete(idx=1)", arr, size);

        // --- Binary Search ---
        System.out.println("\n=== BINARY SEARCH ===");
        int[] sorted = {1, 3, 5, 7, 9, 11};
        System.out.println("  binarySearch(7): idx " + binarySearch(sorted, 7));
        System.out.println("  binarySearch(6): " + binarySearch(sorted, 6));
        int[] dup = {1,2,2,2,3,4};
        System.out.println("  firstOccurrence(2) in [1,2,2,2,3,4]: idx " + firstOccurrence(dup, 2));

        // --- Prefix Sum ---
        System.out.println("\n=== PREFIX SUM ===");
        int[] nums = {1, 2, 3, 4, 5};
        int[] prefix = buildPrefixSum(nums);
        System.out.println("  Sum [1..3]: " + rangeSum(prefix, 1, 3));   // 2+3+4=9
        System.out.println("  Subarrays summing to 2 in [1,1,1]: " + subarraySumK(new int[]{1,1,1}, 2));

        // --- Two Pointer ---
        System.out.println("\n=== TWO POINTER ===");
        int[] sortedArr = {1, 2, 3, 4, 6, 8};
        int[] pair = twoSum(sortedArr, 10);
        System.out.println("  twoSum([1..8], 10): [" + pair[0] + "," + pair[1] + "]");
        System.out.println("  trapRainWater([0,1,0,2,1,0,1,3,2,1,2,1]): "
            + trapRainWater(new int[]{0,1,0,2,1,0,1,3,2,1,2,1}));

        // --- Kadane ---
        System.out.println("\n=== KADANE'S ALGORITHM ===");
        int[] a1 = {-2,1,-3,4,-1,2,1,-5,4};
        System.out.println("  Max subarray sum: " + kadane(a1));   // 6
        int[] info = kadaneWithIndices(a1);
        System.out.println("  Subarray [" + info[1] + ".." + info[2] + "] sum=" + info[0]);

        // --- Sliding Window ---
        System.out.println("\n=== SLIDING WINDOW ===");
        int[] sw = {2,3,1,4,2,5};
        System.out.println("  maxSumWindow(k=3): " + maxSumWindow(sw, 3));   // 11
        System.out.println("  longestSubarraySum ≤ 7: " + longestSubarraySumLE(sw, 7));

        // --- Matrix ---
        System.out.println("\n=== MATRIX OPERATIONS ===");
        int[][] mat = {{1,2,3},{4,5,6},{7,8,9}};
        rotate90CW(mat);
        System.out.print("  Rotated 90° CW:\n");
        for (int[] row : mat) {
            System.out.print("    ");
            for (int v : row) System.out.printf("%3d", v);
            System.out.println();
        }
        System.out.println("  Spiral of 3x4 matrix: "
            + spiral(new int[][]{{1,2,3,4},{5,6,7,8},{9,10,11,12}}));
    }
}
