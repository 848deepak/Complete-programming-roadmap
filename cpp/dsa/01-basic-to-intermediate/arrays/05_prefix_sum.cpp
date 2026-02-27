// ============================================================
// DSA | C++ → Arrays: Prefix Sum
// ============================================================
// DESCRIPTION:
//   Prefix sum (cumulative sum) array allows O(1) range sum queries
//   after O(n) preprocessing. A fundamental building block for many
//   problems involving range aggregations.
//
// CONCEPT:
//   prefix[0] = 0
//   prefix[i] = prefix[i-1] + arr[i-1]   (1-indexed prefix)
//   Sum(L, R) = prefix[R+1] - prefix[L]  (0-indexed arr)
//
// COMPILE & RUN:
//   g++ -std=c++17 05_prefix_sum.cpp -o out && ./out
//
// SAMPLE INPUT:  arr = {3, 1, 4, 1, 5, 9, 2, 6}
// SAMPLE OUTPUT:
//   Prefix sum array: [0, 3, 4, 8, 9, 14, 23, 25, 31]
//   Sum(2, 5) = 19
//   Max subarray sum (length k=3) = 16
//
// COMPLEXITY:
//   Build prefix: O(n) time, O(n) space
//   Each query:   O(1) time after preprocessing
// ============================================================

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/**
 * Builds a prefix sum array from the input array.
 * prefix[i] = sum of arr[0..i-1]  (prefix[0] = 0 for easy range calc)
 *
 * @param arr   Input array
 * @param n     Size of input array
 * @return      Prefix sum vector of size n+1
 *
 * Time: O(n)  |  Space: O(n)
 */
vector<int> buildPrefix(const int arr[], int n) {
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];   // each prefix[i+1] extends prefix[i]
    }
    return prefix;
}

/**
 * Returns the sum of arr[L..R] (both inclusive, 0-indexed).
 * Uses the identity: sum(L, R) = prefix[R+1] - prefix[L]
 *
 * Time: O(1) per query  |  Edge case: L > R returns 0
 */
int rangeSum(const vector<int>& prefix, int L, int R) {
    if (L > R) return 0;   // edge case: invalid range
    return prefix[R + 1] - prefix[L];
}

/**
 * Finds the maximum sum of any contiguous subarray of exactly length k.
 * Uses prefix sum to compute each window in O(1) instead of O(k).
 *
 * Time: O(n)  |  Space: O(n) for prefix array
 * Edge case: returns INT_MIN if k > n
 */
int maxSumSubarrayK(const int arr[], int n, int k) {
    if (k > n) return INT_MIN;   // edge case: window larger than array

    vector<int> prefix = buildPrefix(arr, n);
    int maxSum = INT_MIN;

    // For each window [i, i+k-1], its sum = prefix[i+k] - prefix[i]
    for (int i = 0; i + k <= n; i++) {
        int windowSum = prefix[i + k] - prefix[i];
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}

/**
 * Finds the number of subarrays with sum exactly equal to target.
 * Technique: for each index r, count how many prefix[l] == prefix[r] - target.
 *
 * Time: O(n)  |  Space: O(n) for hashmap
 */
int subarraysWithSum(const int arr[], int n, int target) {
    unordered_map<int, int> freq;   // maps prefix sum → how many times seen
    freq[0] = 1;                    // empty prefix (sum = 0) occurs once
    int prefixSum = 0, count = 0;

    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];

        // If (prefixSum - target) was seen before, those subarrays sum to target
        int needed = prefixSum - target;
        if (freq.count(needed)) count += freq[needed];

        freq[prefixSum]++;
    }
    return count;
}

#include <unordered_map>

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    // ----------------------------------------------------------------
    // Demo 1: Build and display prefix sum array
    // ----------------------------------------------------------------
    cout << "=== PREFIX SUM ARRAY ===" << endl;
    cout << "Input: [ ";
    for (int i = 0; i < n; i++) cout << arr[i] << (i < n-1 ? ", " : "");
    cout << " ]\n";

    vector<int> prefix = buildPrefix(arr, n);
    cout << "Prefix: [ ";
    for (int x : prefix) cout << x << " ";
    cout << "]\n";

    // ----------------------------------------------------------------
    // Demo 2: Range queries in O(1)
    // ----------------------------------------------------------------
    cout << "\n=== RANGE SUM QUERIES (O(1) each) ===" << endl;
    cout << "Sum(0, 2) = " << rangeSum(prefix, 0, 2) << "\n";   // 3+1+4 = 8
    cout << "Sum(2, 5) = " << rangeSum(prefix, 2, 5) << "\n";   // 4+1+5+9 = 19
    cout << "Sum(0, 7) = " << rangeSum(prefix, 0, 7) << "\n";   // entire array = 31
    cout << "Sum(5, 5) = " << rangeSum(prefix, 5, 5) << "\n";   // single element = 9
    cout << "Sum(4, 1) = " << rangeSum(prefix, 4, 1) << "\n";   // invalid → 0 (edge case)

    // ----------------------------------------------------------------
    // Demo 3: Max sum subarray of fixed length k
    // ----------------------------------------------------------------
    cout << "\n=== MAX SUM SUBARRAY OF LENGTH k=3 ===" << endl;
    cout << "Max sum (k=3) = " << maxSumSubarrayK(arr, n, 3) << "\n";  // 9+2+6=17? Let's check
    // Windows: [3,1,4]=8, [1,4,1]=6, [4,1,5]=10, [1,5,9]=15, [5,9,2]=16, [9,2,6]=17
    cout << "Max sum (k=5) = " << maxSumSubarrayK(arr, n, 5) << "\n";

    // ----------------------------------------------------------------
    // Demo 4: Count subarrays with target sum
    // ----------------------------------------------------------------
    cout << "\n=== COUNT SUBARRAYS WITH SUM = target ===" << endl;
    int arr2[] = {1, 1, 1, 1};
    int target = 2;
    cout << "arr={1,1,1,1}, target=2: " << subarraysWithSum(arr2, 4, target) << "\n"; // 3

    int arr3[] = {1, 2, 3, -1, 1, 4};
    cout << "arr={1,2,3,-1,1,4}, target=5: " << subarraysWithSum(arr3, 6, 5) << "\n"; // 3

    return 0;
}
