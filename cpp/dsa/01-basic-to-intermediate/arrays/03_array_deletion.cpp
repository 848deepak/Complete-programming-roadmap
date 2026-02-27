// ============================================================
// DSA | C++ → Arrays: Deletion
// ============================================================
// DESCRIPTION:
//   Demonstrates removing elements from a static array at:
//   - A given index (shift left)
//   - By value (search then shift)
//   - Duplicate removal
//
// COMPILE & RUN:
//   g++ -std=c++17 03_array_deletion.cpp -o out && ./out
//
// SAMPLE INPUT:  arr = {10, 20, 30, 40, 50}
// SAMPLE OUTPUT:
//   After deleting index 2: [10, 20, 40, 50]
//   After deleting value 40: [10, 20, 50]
//
// COMPLEXITY:
//   deleteAt(i)    : O(n) — must shift elements
//   deleteValue(v) : O(n) — search + shift
//   removeDups     : O(n²) naive | O(n) with hash set
// ============================================================

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/**
 * Prints the array in bracket notation.
 * Time: O(n)
 */
void printArr(const string& label, const vector<int>& arr) {
    cout << label << ": [";
    for (int i = 0; i < (int)arr.size(); i++)
        cout << arr[i] << (i + 1 < (int)arr.size() ? ", " : "");
    cout << "]\n";
}

/**
 * Deletes the element at position `index` from arr.
 * Shifts all subsequent elements one position to the left.
 *
 * @param arr    The array (passed by reference, modified in-place)
 * @param index  0-based index to delete
 *
 * Time:  O(n) — worst case shifts all elements (index = 0)
 * Space: O(1) — no extra allocation
 * Edge:  index < 0 or >= arr.size() → prints error, no change
 */
void deleteAt(vector<int>& arr, int index) {
    int n = (int)arr.size();

    if (index < 0 || index >= n) {          // edge case: invalid index
        cout << "Error: index " << index << " out of range [0, " << n - 1 << "]\n";
        return;
    }

    // Shift elements left to fill the gap
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];               // arr[i] ← arr[i+1]
    }

    arr.pop_back();                         // shrink size by 1
}

/**
 * Deletes the FIRST occurrence of `value` from arr.
 * Returns true if found and deleted, false otherwise.
 *
 * Time:  O(n) — linear scan to find value, then shift
 * Space: O(1)
 * Edge:  value not found → returns false, arr unchanged
 */
bool deleteByValue(vector<int>& arr, int value) {
    int n = (int)arr.size();

    // Step 1: find the value
    int foundIdx = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            foundIdx = i;
            break;                          // only delete first occurrence
        }
    }

    if (foundIdx == -1) {                   // edge case: value not in array
        cout << "Value " << value << " not found in array.\n";
        return false;
    }

    // Step 2: shift elements left
    for (int i = foundIdx; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr.pop_back();
    return true;
}

/**
 * Deletes ALL occurrences of `value` from arr.
 *
 * Time:  O(n) — single pass with write pointer
 * Space: O(1)
 *
 * Technique: Two-pointer (keep a writeIdx, only copy non-matching elements)
 */
int deleteAllOccurrences(vector<int>& arr, int value) {
    int writeIdx = 0;                       // where to write the next kept element
    int deleted  = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] != value) {
            arr[writeIdx++] = arr[i];       // keep this element
        } else {
            deleted++;
        }
    }

    arr.resize(writeIdx);                   // truncate to new size
    return deleted;
}

/**
 * Removes duplicate values, keeping only the first occurrence.
 * Uses an unordered_set to track seen values.
 *
 * Time:  O(n) average
 * Space: O(n) — for the seen set
 */
void removeDuplicates(vector<int>& arr) {
    unordered_set<int> seen;
    int writeIdx = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        if (!seen.count(arr[i])) {          // first time seeing this value
            seen.insert(arr[i]);
            arr[writeIdx++] = arr[i];
        }
        // else: skip duplicate
    }

    arr.resize(writeIdx);
}

// ============================================================
// MAIN
// ============================================================
int main() {
    // --- deleteAt ---
    cout << "=== DELETE BY INDEX ===" << "\n";
    vector<int> arr1 = {10, 20, 30, 40, 50};
    printArr("Original", arr1);

    deleteAt(arr1, 2);                      // delete index 2 (value 30)
    printArr("After deleteAt(2)", arr1);

    deleteAt(arr1, 0);                      // delete first element
    printArr("After deleteAt(0)", arr1);

    deleteAt(arr1, 99);                     // edge: out of range

    // --- deleteByValue (first occurrence) ---
    cout << "\n=== DELETE BY VALUE (first occurrence) ===" << "\n";
    vector<int> arr2 = {10, 20, 30, 40, 30, 50};
    printArr("Original", arr2);

    deleteByValue(arr2, 30);                // removes first 30
    printArr("After deleteByValue(30)", arr2);

    deleteByValue(arr2, 99);                // edge: not found

    // --- deleteAllOccurrences ---
    cout << "\n=== DELETE ALL OCCURRENCES ===" << "\n";
    vector<int> arr3 = {1, 2, 3, 2, 4, 2, 5};
    printArr("Original", arr3);

    int cnt = deleteAllOccurrences(arr3, 2);
    printArr("After deleteAll(2)", arr3);
    cout << "Deleted " << cnt << " occurrence(s) of 2\n";

    // --- removeDuplicates ---
    cout << "\n=== REMOVE DUPLICATES ===" << "\n";
    vector<int> arr4 = {4, 1, 2, 1, 3, 4, 2, 5, 4};
    printArr("Original", arr4);

    removeDuplicates(arr4);
    printArr("After removeDuplicates", arr4);

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   deleteAt(i)           : O(n) time, O(1) space
//   deleteByValue(v)      : O(n) time, O(1) space
//   deleteAllOccurrences  : O(n) time, O(1) space
//   removeDuplicates      : O(n) time, O(n) space
// ============================================================
