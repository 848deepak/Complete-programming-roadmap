// ============================================================
// MODULE 04 | C++ BASICS → Arrays & Strings
// ============================================================
// DESCRIPTION:
//   Covers 1D and 2D array operations (sort, reverse, rotate,
//   sliding window, prefix sum, missing number), and string
//   operations (palindrome, anagram, longest unique substring).
//
// COMPILE & RUN:
//   g++ -std=c++17 04_arrays_strings.cpp -o out && ./out
//
// COMPLEXITY OVERVIEW:
//   Array sort        : O(n log n)
//   Reverse (2-ptr)   : O(n)
//   Rotate (3-reverse): O(n)
//   Sliding window    : O(n)
//   Missing number    : O(n)
//   Matrix transpose  : O(n²)
//   Palindrome check  : O(n)
//   Anagram check     : O(n log n)
//   Longest unique    : O(n) with sliding window
// ============================================================

#include <iostream>
#include <string>
#include <algorithm>      // sort, reverse, swap
#include <unordered_map>  // for sliding window on strings
using namespace std;

// ============================================================
// HELPER: Print 1D Array
// ============================================================
/**
 * Prints a labeled 1D integer array in [ a, b, c ] format.
 * @param a      Pointer to the array
 * @param n      Number of elements
 * @param label  Optional label to print before the array
 */
void printArr(int* a, int n, const char* label = "") {
    if (label[0]) cout << label << ": ";
    cout << "[ ";
    for (int i = 0; i < n; i++) cout << a[i] << (i < n - 1 ? ", " : "");
    cout << " ]\n";
}

int main() {

    // ================================================================
    // SECTION 1: ONE-DIMENSIONAL ARRAYS
    // ================================================================
    cout << "=== 1D ARRAYS ===" << endl;

    int arr[] = {64, 23, 87, 12, 45};
    int n = 5;
    printArr(arr, n, "Original");

    // Sort ascending  — std::sort uses introsort: O(n log n)
    sort(arr, arr + n);
    printArr(arr, n, "Sorted Asc");

    // Sort descending — pass a custom comparator
    sort(arr, arr + n, greater<int>());
    printArr(arr, n, "Sorted Desc");

    // ----------------------------------------------------------------
    // Reverse using two-pointer technique
    // Left pointer moves right, right pointer moves left, swap.
    // Time: O(n)  |  Space: O(1)
    // ----------------------------------------------------------------
    int rev[] = {1, 2, 3, 4, 5};
    for (int l = 0, r = 4; l < r; l++, r--) swap(rev[l], rev[r]);
    printArr(rev, 5, "Reversed");

    // ----------------------------------------------------------------
    // Rotate right by k — three-reversal trick
    // After rotation of {1,2,3,4,5,6,7} by k=3: {5,6,7,1,2,3,4}
    // Step 1: reverse entire array
    // Step 2: reverse first k elements
    // Step 3: reverse remaining n-k elements
    // Time: O(n)  |  Space: O(1)
    // ----------------------------------------------------------------
    int rot[] = {1, 2, 3, 4, 5, 6, 7};
    int sz = 7, k = 3;
    k %= sz;                                // handle k > sz
    reverse(rot, rot + sz);                 // reverse all
    reverse(rot, rot + k);                  // reverse first k
    reverse(rot + k, rot + sz);             // reverse rest
    printArr(rot, sz, "Rotated+3");

    // ================================================================
    // SECTION 2: SLIDING WINDOW — MAX SUM OF K CONSECUTIVE ELEMENTS
    // ================================================================
    // Maintain a window of size k; slide it by adding the new element
    // and removing the outgoing element. Avoids recomputing the sum.
    // Time: O(n)  |  Space: O(1)
    // ----------------------------------------------------------------
    cout << "\n=== SLIDING WINDOW (max sum k=3) ===" << endl;

    int win[]  = {2, 1, 5, 1, 3, 2};
    int wSz    = 3;
    int winSum = 0, maxSum = 0;

    // Compute sum of the first window
    for (int i = 0; i < wSz; i++) winSum += win[i];
    maxSum = winSum;

    // Slide the window: add new element, remove outgoing element
    for (int i = wSz; i < 6; i++) {
        winSum += win[i] - win[i - wSz];    // slide right by one
        maxSum = max(maxSum, winSum);
    }
    cout << "Max sum of 3 consecutive = " << maxSum << endl;  // 9 (5+1+3)

    // ================================================================
    // SECTION 3: MISSING NUMBER (using sum formula)
    // ================================================================
    // Expected sum for 1..N = N*(N+1)/2
    // Missing number = expected sum - actual sum
    // Time: O(n)  |  Space: O(1)
    // ----------------------------------------------------------------
    cout << "\n=== MISSING NUMBER ===" << endl;

    int miss[] = {1, 2, 4, 5, 6};    // 3 is missing from 1..6
    int N = 6;
    int expected = N * (N + 1) / 2;   // 21
    int actual   = 0;
    for (int x : miss) actual += x;   // 18
    cout << "Missing number = " << expected - actual << endl;  // 3

    // ================================================================
    // SECTION 4: 2D ARRAYS — MATRIX TRANSPOSE
    // ================================================================
    // Transpose swaps mat[i][j] with mat[j][i] for i < j.
    // This is done in-place by iterating the upper triangle.
    // Time: O(n²)  |  Space: O(1)
    // ----------------------------------------------------------------
    cout << "\n=== 2D ARRAY — MATRIX TRANSPOSE ===" << endl;

    int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    cout << "Original matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) printf("%4d", mat[i][j]);
        cout << "\n";
    }

    // Swap elements across the main diagonal
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 3; j++)
            swap(mat[i][j], mat[j][i]);

    cout << "Transposed matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) printf("%4d", mat[i][j]);
        cout << "\n";
    }

    // ================================================================
    // SECTION 5: STRINGS
    // ================================================================
    cout << "\n=== STRINGS ===" << endl;

    string s = "Hello, World!";
    cout << "string      = \"" << s << "\"\n";
    cout << "length      = " << s.length() << "\n";
    cout << "charAt[0]   = " << s[0] << "\n";
    cout << "substr(7,5) = " << s.substr(7, 5) << "\n";   // "World"
    cout << "find(',')   = " << s.find(',') << "\n";       // index 5

    // Reverse a string copy
    string rev2 = s;
    reverse(rev2.begin(), rev2.end());
    cout << "reversed    = " << rev2 << "\n";

    // ----------------------------------------------------------------
    // Palindrome Check
    // A palindrome reads the same forwards and backwards.
    // Two-pointer approach: compare from both ends.
    // Time: O(n)  |  Space: O(1) with two-pointer (O(n) if we create a copy)
    // ----------------------------------------------------------------
    auto isPalindrome = [](const string& str) -> bool {
        int l = 0, r = (int)str.size() - 1;
        while (l < r) {
            if (str[l] != str[r]) return false;
            l++; r--;
        }
        return true;
    };
    cout << "\nboolalpha mode enabled:\n";
    cout << boolalpha;
    cout << "\"racecar\" palindrome: " << isPalindrome("racecar") << "\n";  // true
    cout << "\"hello\"   palindrome: " << isPalindrome("hello")   << "\n";  // false

    // ----------------------------------------------------------------
    // Anagram Check
    // Two strings are anagrams if they contain the same characters.
    // Sort both and compare — Time: O(n log n)
    // ----------------------------------------------------------------
    auto isAnagram = [](string a, string b) -> bool {
        if (a.size() != b.size()) return false;   // edge case: different lengths
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a == b;
    };
    cout << "\"listen\"/\"silent\" anagram: " << isAnagram("listen", "silent") << "\n"; // true
    cout << "\"hello\"/\"world\"   anagram: " << isAnagram("hello", "world")   << "\n"; // false

    // ----------------------------------------------------------------
    // Longest Substring Without Repeating Characters (Sliding Window)
    // Use a hashmap to track the last seen position of each character.
    // Shrink the left boundary when a duplicate is found.
    // Time: O(n)  |  Space: O(min(n, charset)) — at most 128 for ASCII
    // ----------------------------------------------------------------
    auto longestUnique = [](const string& str) -> int {
        if (str.empty()) return 0;                    // edge case: empty string
        unordered_map<char, int> lastSeen;            // char → last index seen
        int left = 0, maxLen = 0;

        for (int right = 0; right < (int)str.size(); right++) {
            char c = str[right];
            // If c was seen inside the current window, shrink from left
            if (lastSeen.count(c) && lastSeen[c] >= left)
                left = lastSeen[c] + 1;

            lastSeen[c] = right;                      // update last position
            maxLen = max(maxLen, right - left + 1);   // update max window size
        }
        return maxLen;
    };

    cout << "\n\"abcabcbb\" longest unique = " << longestUnique("abcabcbb") << "\n"; // 3 (abc)
    cout << "\"bbbbb\"    longest unique = " << longestUnique("bbbbb")    << "\n"; // 1 (b)
    cout << "\"\"         longest unique = " << longestUnique("")         << "\n"; // 0 (edge case)

    // ----------------------------------------------------------------
    // String ↔ Number Conversion
    // ----------------------------------------------------------------
    cout << "\n=== STRING ↔ NUMBER ===" << endl;
    cout << "to_string(42)  = \"" << to_string(42)  << "\"\n";
    cout << "stoi(\"99\")     = "  << stoi("99")    << "\n";
    cout << "stod(\"3.14\")   = "  << stod("3.14")  << "\n";

    return 0;
}
