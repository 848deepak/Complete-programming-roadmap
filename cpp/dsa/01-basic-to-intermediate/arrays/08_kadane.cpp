// ============================================================
// DSA | C++ → Arrays: Kadane's Algorithm
// ============================================================
// DESCRIPTION:
//   Kadane's algorithm finds the contiguous subarray with the
//   maximum sum in linear time O(n). It is a classic example
//   of dynamic programming used on arrays.
//
// PROBLEM: Maximum Subarray (LeetCode #53)
//   Given an integer array nums, find the subarray with the
//   largest sum, and return its sum.
//
// COMPILE & RUN:
//   g++ -std=c++17 08_kadane.cpp -o out && ./out
//
// SAMPLE INPUT:  arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
// SAMPLE OUTPUT: Max subarray sum = 6 (subarray [4,-1,2,1])
//
// COMPLEXITY:
//   Time:  O(n) — single pass through array
//   Space: O(1) — only constant variables
// ============================================================

#include <iostream>
#include <vector>
#include <climits>    // INT_MIN
#include <string>
using namespace std;

// ============================================================
// SECTION 1: BASIC KADANE'S ALGORITHM
// ============================================================
// Key insight:
//   At each position i, we have two choices:
//   1. Extend the current subarray : currentSum + arr[i]
//   2. Start fresh at this element : arr[i]
//
//   We pick whichever is larger.
//   We track the global max as we go.
//
//   currentSum = max(arr[i], currentSum + arr[i])
//   maxSum     = max(maxSum, currentSum)
// ------------------------------------------------------------ 

/**
 * Returns the maximum subarray sum.
 * Handles all-negative arrays correctly (returns the max single element).
 *
 * @param arr  Input array (may contain negative numbers)
 * @return     Maximum subarray sum
 *
 * Time: O(n)  |  Space: O(1)
 * Edge: single-element array → returns that element
 * Edge: all negative → returns the least-negative element
 */
int kadaneMaxSum(const vector<int>& arr) {
    if (arr.empty()) return 0;

    int maxSum     = arr[0];   // initialize with first element (handles all-negative case)
    int currentSum = arr[0];

    for (int i = 1; i < (int)arr.size(); i++) {
        // Choice: extend previous subarray or start new one here
        currentSum = max(arr[i], currentSum + arr[i]);

        // Update global max
        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}

// ============================================================
// SECTION 2: KADANE'S WITH SUBARRAY INDICES
// ============================================================
// Same algorithm but also tracks where the best subarray starts and ends.
//
// Strategy:
//   - When we start fresh (arr[i] > currentSum + arr[i]), reset tempStart = i
//   - When we update the global max, update start = tempStart, end = i
// ------------------------------------------------------------ 

struct SubarrayResult {
    int sum;    // maximum subarray sum
    int start;  // start index (inclusive)
    int end;    // end index (inclusive)
};

/**
 * Returns the maximum subarray sum AND the subarray indices.
 *
 * Time: O(n)  |  Space: O(1)
 */
SubarrayResult kadaneWithIndices(const vector<int>& arr) {
    int maxSum     = arr[0];
    int currentSum = arr[0];
    int start = 0, end = 0;
    int tempStart = 0;          // candidate start of new subarray

    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] > currentSum + arr[i]) {
            // Starting fresh is better → update temporary start
            currentSum = arr[i];
            tempStart  = i;
        } else {
            // Extending is better
            currentSum += arr[i];
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            start  = tempStart;
            end    = i;
        }
    }

    return {maxSum, start, end};
}

// ============================================================
// SECTION 3: MAXIMUM CIRCULAR SUBARRAY SUM
// ============================================================
// A circular array allows the subarray to wrap around.
// 
// Two cases:
//   Case 1: The max subarray is entirely within arr (normal Kadane)
//   Case 2: The max subarray wraps around
//           = totalSum - minSubarraySum (using Kadane for min)
//
// Answer = max(case1, case2)
//
// Edge: if all elements are negative, case2 = 0 (empty wrap),
//       but we must return the max negative (case1 handles this).
//
// Time: O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

int kadaneCircular(const vector<int>& arr) {
    int n = (int)arr.size();
    if (n == 1) return arr[0];

    // Case 1: normal max subarray (no wrap)
    int maxNormal = kadaneMaxSum(arr);

    // Case 2: wrap-around max = totalSum - minSubarray
    int totalSum   = 0;
    int minCurrent = arr[0];
    int minSum     = arr[0];

    for (int i = 0; i < n; i++) {
        totalSum  += arr[i];
        if (i > 0) {
            minCurrent = min(arr[i], minCurrent + arr[i]);
            minSum     = min(minSum, minCurrent);
        }
    }

    int maxCircular = totalSum - minSum;

    // Edge: all negative → maxCircular = 0 (empty array), return normal max
    if (maxNormal < 0) return maxNormal;

    return max(maxNormal, maxCircular);
}

// ============================================================
// SECTION 4: MAXIMUM PRODUCT SUBARRAY
// ============================================================
// Like Kadane but for product. We track both max and min because
// multiplying two negatives gives a positive.
//
// Time: O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

int maxProductSubarray(const vector<int>& arr) {
    int maxProd  = arr[0];
    int minProd  = arr[0];
    int result   = arr[0];

    for (int i = 1; i < (int)arr.size(); i++) {
        // When multiplied by a negative, max becomes min and vice versa
        if (arr[i] < 0) swap(maxProd, minProd);

        maxProd = max(arr[i], maxProd * arr[i]);
        minProd = min(arr[i], minProd * arr[i]);

        result = max(result, maxProd);
    }

    return result;
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Basic Kadane ---
    cout << "=== KADANE'S ALGORITHM ===" << "\n";

    vector<vector<int>> testCases = {
        {-2,  1, -3,  4, -1,  2,  1, -5,  4},   // classic: answer 6
        { 1,  2,  3,  4,  5},                    // all positive: entire array
        {-5, -3, -1, -2, -4},                    // all negative: -1
        { 0,  0,  0},                            // all zeros: 0
        { 3, -2,  5, -1}                         // mixed: 6
    };

    for (auto& arr : testCases) {
        cout << "Input: [";
        for (int i = 0; i < (int)arr.size(); i++)
            cout << arr[i] << (i+1<(int)arr.size()?",":"");
        cout << "]\n";
        cout << "  Max sum: " << kadaneMaxSum(arr) << "\n";
    }

    // --- With Indices ---
    cout << "\n=== KADANE'S WITH SUBARRAY INDICES ===" << "\n";
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    auto res = kadaneWithIndices(arr);
    cout << "Array: [-2,1,-3,4,-1,2,1,-5,4]\n";
    cout << "Max sum = " << res.sum << "\n";
    cout << "Subarray [" << res.start << ".." << res.end << "]: [";
    for (int i = res.start; i <= res.end; i++)
        cout << arr[i] << (i<res.end?",":"");
    cout << "]\n";

    // --- Circular Kadane ---
    cout << "\n=== MAXIMUM CIRCULAR SUBARRAY SUM ===" << "\n";
    vector<int> circ1 = {1, -2, 3, -2};
    vector<int> circ2 = {5, -3, 5};
    vector<int> circ3 = {-3, -2, -3};   // all negative edge case

    cout << "[1,-2,3,-2] circular max: " << kadaneCircular(circ1) << "\n";  // 3
    cout << "[5,-3,5]    circular max: " << kadaneCircular(circ2) << "\n";  // 10 (wrap)
    cout << "[-3,-2,-3]  circular max: " << kadaneCircular(circ3) << "\n";  // -2

    // --- Max Product Subarray ---
    cout << "\n=== MAXIMUM PRODUCT SUBARRAY ===" << "\n";
    vector<int> p1 = {2, 3, -2, 4};
    vector<int> p2 = {-2, 0, -1};
    vector<int> p3 = {-2, 3, -4};
    cout << "[2,3,-2,4]  max product: " << maxProductSubarray(p1) << "\n";  // 6
    cout << "[-2,0,-1]   max product: " << maxProductSubarray(p2) << "\n";  // 0
    cout << "[-2,3,-4]   max product: " << maxProductSubarray(p3) << "\n";  // 24

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   kadaneMaxSum       : O(n) time, O(1) space
//   kadaneWithIndices  : O(n) time, O(1) space
//   kadaneCircular     : O(n) time, O(1) space
//   maxProductSubarray : O(n) time, O(1) space
//
// COMMON INTERVIEW QUESTIONS:
//   1. Maximum subarray (classic Kadane)
//   2. Maximum product subarray
//   3. Maximum circular subarray
//   4. Minimum subarray sum (use -arr, then Kadane)
// ============================================================
