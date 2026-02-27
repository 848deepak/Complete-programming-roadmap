// ============================================================
// DSA | C++ → Arrays: Sliding Window Technique
// ============================================================
// DESCRIPTION:
//   The sliding window pattern maintains a contiguous subarray
//   (window) and slides it across the input, updating results
//   incrementally rather than recalculating from scratch.
//
//   Two types:
//   1. Fixed-size window  — window size k is given
//   2. Variable-size window — window grows/shrinks based on condition
//
// COMPILE & RUN:
//   g++ -std=c++17 06_sliding_window.cpp -o out && ./out
//
// COMPLEXITY:
//   All problems below: O(n) time, O(1) or O(k) space
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

// ============================================================
// PROBLEM 1: Max Sum of Fixed-Size Window (k)
// ============================================================
/**
 * Returns the maximum sum of any subarray of exactly length k.
 *
 * Approach:
 *   Build sum of first window [0..k-1].
 *   Then slide: add arr[right], subtract arr[right-k].
 *
 * Time: O(n)  |  Space: O(1)
 * Edge case: return -1 if k > n or k <= 0.
 */
int maxWindowSum(const vector<int>& arr, int k) {
    int n = arr.size();
    if (k <= 0 || k > n) return -1;   // invalid window size

    // Compute sum of the first window
    int windowSum = 0;
    for (int i = 0; i < k; i++) windowSum += arr[i];
    int maxSum = windowSum;

    // Slide the window: O(n-k) more iterations
    for (int right = k; right < n; right++) {
        windowSum += arr[right] - arr[right - k];   // add new, remove old
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}

// ============================================================
// PROBLEM 2: Longest Substring Without Repeating Characters
// ============================================================
/**
 * Returns the length of the longest substring with all unique chars.
 *
 * Approach: Variable window. Maintain a freq map for characters in
 * the window. When a duplicate enters, shrink from the left.
 *
 * Time: O(n)  |  Space: O(min(n, 26)) for alphabet chars
 * Edge case: empty string → 0
 */
int longestUniqueSubstring(const string& s) {
    if (s.empty()) return 0;

    unordered_map<char, int> freq;   // char → count in current window
    int left = 0, maxLen = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        freq[s[right]]++;   // expand window by including s[right]

        // Shrink from left until no duplicates exist in window
        while (freq[s[right]] > 1) {
            freq[s[left]]--;
            if (freq[s[left]] == 0) freq.erase(s[left]);
            left++;
        }
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// ============================================================
// PROBLEM 3: Minimum Window Substring (contains all chars of t)
// ============================================================
/**
 * Returns the shortest substring of s that contains all chars of t.
 *
 * Approach: Two maps — 'need' tracks required counts, 'have' tracks
 * current window counts. Track when all 'need' chars are satisfied.
 *
 * Time: O(|s| + |t|)  |  Space: O(|t|)
 * Edge case: no valid window → return ""
 */
string minWindowSubstring(const string& s, const string& t) {
    if (t.empty() || s.size() < t.size()) return "";

    unordered_map<char, int> need;   // required character counts
    for (char c : t) need[c]++;

    unordered_map<char, int> have;   // counts in current window
    int formed  = 0;                 // how many chars satisfy requirement
    int required = (int)need.size(); // distinct chars needed
    int left = 0;
    int minLen = INT_MAX, minLeft = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        char c = s[right];
        have[c]++;

        // Check if this char now satisfies its requirement
        if (need.count(c) && have[c] == need[c]) formed++;

        // Try to shrink window from left while all requirements met
        while (formed == required) {
            int windowLen = right - left + 1;
            if (windowLen < minLen) {
                minLen  = windowLen;
                minLeft = left;
            }
            // Remove left character from window
            char lc = s[left];
            have[lc]--;
            if (need.count(lc) && have[lc] < need[lc]) formed--;
            left++;
        }
    }
    return (minLen == INT_MAX) ? "" : s.substr(minLeft, minLen);
}

// ============================================================
// PROBLEM 4: Count Subarrays with at Most k Distinct Integers
// ============================================================
/**
 * Returns number of subarrays with at most k distinct integers.
 * Helper for "exactly k distinct" problems.
 *
 * Time: O(n)  |  Space: O(k)
 */
int atMostKDistinct(const vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    int left = 0, count = 0;

    for (int right = 0; right < (int)arr.size(); right++) {
        freq[arr[right]]++;

        // Too many distinct — shrink window
        while ((int)freq.size() > k) {
            freq[arr[left]]--;
            if (freq[arr[left]] == 0) freq.erase(arr[left]);
            left++;
        }
        count += right - left + 1;   // all windows ending at right
    }
    return count;
}

/** Subarrays with EXACTLY k distinct = atMost(k) - atMost(k-1) */
int exactlyKDistinct(const vector<int>& arr, int k) {
    return atMostKDistinct(arr, k) - atMostKDistinct(arr, k - 1);
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // Problem 1: Fixed window max sum
    cout << "=== MAX SUM OF WINDOW SIZE k ===" << endl;
    vector<int> arr = {2, 1, 5, 1, 3, 2};
    cout << "arr = {2,1,5,1,3,2}, k=3\n";
    cout << "Max Window Sum = " << maxWindowSum(arr, 3) << "\n";  // 5+1+3=9

    vector<int> arr2 = {-1, -3, -2, -4, -5};
    cout << "arr = {-1,-3,-2,-4,-5}, k=2\n";
    cout << "Max Window Sum = " << maxWindowSum(arr2, 2) << "\n"; // -1+(-3)= -4? No: -1+-3=-4, or -2+-4=-6? -> -4

    // Problem 2: Longest unique substring
    cout << "\n=== LONGEST UNIQUE SUBSTRING ===" << endl;
    cout << "\"abcabcbb\" → " << longestUniqueSubstring("abcabcbb") << "\n"; // 3
    cout << "\"bbbbb\"    → " << longestUniqueSubstring("bbbbb")    << "\n"; // 1
    cout << "\"pwwkew\"   → " << longestUniqueSubstring("pwwkew")   << "\n"; // 3 (wke)
    cout << "\"\"         → " << longestUniqueSubstring("")         << "\n"; // 0 (edge)

    // Problem 3: Minimum window substring
    cout << "\n=== MINIMUM WINDOW SUBSTRING ===" << endl;
    cout << "s=\"ADOBECODEBANC\" t=\"ABC\" → \""
         << minWindowSubstring("ADOBECODEBANC", "ABC") << "\"\n"; // "BANC"
    cout << "s=\"a\" t=\"a\" → \""
         << minWindowSubstring("a", "a") << "\"\n";               // "a"
    cout << "s=\"a\" t=\"aa\" → \""
         << minWindowSubstring("a", "aa") << "\"\n";              // "" (edge)

    // Problem 4: Subarrays with exactly k distinct
    cout << "\n=== SUBARRAYS WITH EXACTLY k DISTINCT ===" << endl;
    vector<int> arr3 = {1, 2, 1, 2, 3};
    cout << "arr={1,2,1,2,3}, k=2: " << exactlyKDistinct(arr3, 2) << "\n";  // 7
    cout << "arr={1,2,1,2,3}, k=3: " << exactlyKDistinct(arr3, 3) << "\n";  // 3

    return 0;
}
