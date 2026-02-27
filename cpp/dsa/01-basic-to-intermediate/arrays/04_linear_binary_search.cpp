// ============================================================
// DSA | C++ → Arrays: Linear Search & Binary Search
// ============================================================
// DESCRIPTION:
//   Implements and compares two fundamental searching algorithms:
//   - Linear Search : works on unsorted arrays    O(n)
//   - Binary Search : requires sorted arrays      O(log n)
//   Includes recursive and iterative binary search variants.
//
// COMPILE & RUN:
//   g++ -std=c++17 04_linear_binary_search.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   Linear search(7) in [1..9]: found at index 6
//   Binary search(7) in sorted: found at index 6
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>    // sort (used in examples)
using namespace std;

// ============================================================
// SECTION 1: LINEAR SEARCH
// ============================================================
// Scan every element from left to right.
// Does NOT require sorted input.
//
// Time:  O(n) worst/average, O(1) best (first element)
// Space: O(1)
// ------------------------------------------------------------ 

/**
 * Finds the FIRST occurrence of `target` in array.
 *
 * @param arr     The input array
 * @param target  Value to search for
 * @return        0-based index if found, -1 if not found
 */
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) return i;    // found — return index immediately
    }
    return -1;                             // not found
}

/**
 * Finds ALL indices where `target` appears.
 *
 * Time:  O(n) — must check every element
 * Space: O(k) — k = number of occurrences
 */
vector<int> linearSearchAll(const vector<int>& arr, int target) {
    vector<int> indices;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) indices.push_back(i);
    }
    return indices;
}

// ============================================================
// SECTION 2: BINARY SEARCH (Iterative)
// ============================================================
// REQUIREMENT: Array must be SORTED in ascending order.
//
// Strategy: Compare target with middle element.
//   - If target == mid  → found
//   - If target  < mid  → search LEFT half
//   - If target  > mid  → search RIGHT half
// Each step HALVES the search space → O(log n)
//
// Time:  O(log n)
// Space: O(1) — no recursion stack
// ------------------------------------------------------------ 

/**
 * Iterative binary search.
 *
 * @param arr     SORTED array
 * @param target  Value to find
 * @return        0-based index if found, -1 if not found
 */
int binarySearchIterative(const vector<int>& arr, int target) {
    int low  = 0;
    int high = (int)arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;  // AVOID overflow: don't use (low+high)/2

        if      (arr[mid] == target) return mid;   // exact match
        else if (arr[mid]  < target) low  = mid + 1; // target is in right half
        else                         high = mid - 1; // target is in left half
    }

    return -1;   // target not found
}

// ============================================================
// SECTION 3: BINARY SEARCH (Recursive)
// ============================================================
// Same logic but uses call stack instead of a loop.
//
// Time:  O(log n)
// Space: O(log n) — one stack frame per recursive call
// ------------------------------------------------------------ 

/**
 * Recursive binary search on arr[low..high].
 *
 * @param arr     SORTED array
 * @param low     Left boundary of current search window
 * @param high    Right boundary of current search window
 * @param target  Value to find
 * @return        0-based index if found, -1 otherwise
 */
int binarySearchRecursive(const vector<int>& arr, int low, int high, int target) {
    if (low > high) return -1;              // base case: empty window

    int mid = low + (high - low) / 2;

    if      (arr[mid] == target) return mid;
    else if (arr[mid]  < target) return binarySearchRecursive(arr, mid + 1, high, target);
    else                         return binarySearchRecursive(arr, low, mid - 1, target);
}

// ============================================================
// SECTION 4: FIRST & LAST OCCURRENCE (Modified Binary Search)
// ============================================================
// For arrays with duplicates, binary search can be adapted to find
// the FIRST or LAST position of the target.
// ------------------------------------------------------------ 

/**
 * Returns the INDEX of the first occurrence of `target`.
 * Returns -1 if not found.
 */
int firstOccurrence(const vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;         // record this position
            high = mid - 1;       // but keep searching LEFT for an earlier occurrence
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

/**
 * Returns the INDEX of the last occurrence of `target`.
 * Returns -1 if not found.
 */
int lastOccurrence(const vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;         // record this position
            low = mid + 1;        // keep searching RIGHT for a later occurrence
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// ============================================================
// SECTION 5: SEARCH IN ROTATED SORTED ARRAY
// ============================================================
// A sorted array rotated at some pivot (e.g., [4,5,6,1,2,3]).
// Modified binary search: determine which half is sorted, then decide.
//
// Time: O(log n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Binary search in a rotated sorted array (no duplicates).
 * Returns index of target, or -1.
 */
int searchRotated(const vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) return mid;

        // Left half [low..mid] is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] <= target && target < arr[mid])
                high = mid - 1;      // target in sorted left half
            else
                low = mid + 1;       // target in right half
        }
        // Right half [mid..high] is sorted
        else {
            if (arr[mid] < target && target <= arr[high])
                low = mid + 1;       // target in sorted right half
            else
                high = mid - 1;      // target in left half
        }
    }

    return -1;
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Linear Search ---
    cout << "=== LINEAR SEARCH ===" << "\n";
    vector<int> arr = {4, 7, 2, 9, 1, 5, 7, 3, 8};

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    int idx = linearSearch(arr, 7);
    cout << "linearSearch(7): " << (idx != -1 ? "index " + to_string(idx) : "not found") << "\n";

    auto allIdx = linearSearchAll(arr, 7);
    cout << "linearSearchAll(7): [";
    for (int i = 0; i < (int)allIdx.size(); i++)
        cout << allIdx[i] << (i+1<(int)allIdx.size()?",":"");
    cout << "]\n";

    cout << "linearSearch(99): not found? " << (linearSearch(arr, 99) == -1 ? "yes" : "no") << "\n";

    // --- Binary Search ---
    cout << "\n=== BINARY SEARCH ===" << "\n";
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "Sorted array: ";
    for (int x : sorted) cout << x << " ";
    cout << "\n";

    cout << "Iterative BS(7): index " << binarySearchIterative(sorted, 7)  << "\n";   // 6
    cout << "Recursive BS(7): index " << binarySearchRecursive(sorted, 0, 8, 7) << "\n";
    cout << "Iterative BS(1): index " << binarySearchIterative(sorted, 1)  << "\n";   // 0
    cout << "Iterative BS(10): " << binarySearchIterative(sorted, 10) << " (not found)\n";

    // --- First / Last Occurrence ---
    cout << "\n=== FIRST & LAST OCCURRENCE ===" << "\n";
    vector<int> dup = {1, 2, 2, 2, 3, 4, 4, 5};
    cout << "Array with duplicates: ";
    for (int x : dup) cout << x << " ";
    cout << "\n";
    cout << "First occurrence of 2: index " << firstOccurrence(dup, 2) << "\n";   // 1
    cout << "Last  occurrence of 2: index " << lastOccurrence(dup, 2)  << "\n";   // 3
    cout << "Occurrences of 4: ["  << firstOccurrence(dup,4) << ".." << lastOccurrence(dup,4) << "]\n";

    // --- Rotated Sorted Array ---
    cout << "\n=== ROTATED SORTED ARRAY SEARCH ===" << "\n";
    vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    cout << "Rotated array: ";
    for (int x : rotated) cout << x << " ";
    cout << "\n";
    cout << "searchRotated(0): index " << searchRotated(rotated, 0) << "\n";  // 4
    cout << "searchRotated(6): index " << searchRotated(rotated, 6) << "\n";  // 2
    cout << "searchRotated(3): " << searchRotated(rotated, 3) << " (not found)\n";

    return 0;
}

// ============================================================
// COMPARISON TABLE
//   Algorithm         | Time (best) | Time (worst) | Space | Requires sorted?
//   Linear Search     | O(1)        | O(n)         | O(1)  | No
//   Binary Iterative  | O(1)        | O(log n)     | O(1)  | Yes
//   Binary Recursive  | O(1)        | O(log n)     | O(log n) | Yes
//   Rotated BS        | O(1)        | O(log n)     | O(1)  | Yes (rotated)
// ============================================================
