// ============================================================
// DSA | C++ → Stack: Next Greater Element
// ============================================================
// DESCRIPTION:
//   For each element in an array, find the next element to
//   its RIGHT that is GREATER than it.
//   Solved in O(n) using a monotonic stack.
//
// VARIANTS COVERED:
//   1. Next Greater Element         → right, for array
//   2. Previous Greater Element     → left
//   3. Next Smaller Element         → right
//   4. Next Greater in Circular     → circular array wrap-around
//   5. Stock Span Problem           → classic NGE application
//   6. Largest Rectangle in Histogram
//
// COMPILE & RUN:
//   g++ -std=c++17 04_next_greater_element.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void printPairs(const string& label, const vector<int>& arr, const vector<int>& result) {
    cout << label << "\n";
    cout << "  Input : [";
    for (int i = 0; i < (int)arr.size(); i++)
        cout << arr[i] << (i+1<(int)arr.size()?",":"");
    cout << "]\n";
    cout << "  Output: [";
    for (int i = 0; i < (int)result.size(); i++)
        cout << result[i] << (i+1<(int)result.size()?",":"");
    cout << "]\n";
}

// ============================================================
// SECTION 1: NEXT GREATER ELEMENT (→ right)
// ============================================================
// Monotonic Decreasing Stack approach:
//   Process array left to right.
//   Maintain a stack of indices of elements not yet answered.
//   When arr[i] > arr[stack.top()], arr[i] is the NGE for stack.top().
//
// Time: O(n) — each element pushed and popped at most once
// Space: O(n)
// ------------------------------------------------------------ 

/**
 * For each element, returns the next greater element to its right.
 * If no greater element exists, returns -1.
 */
vector<int> nextGreaterRight(const vector<int>& arr) {
    int n = (int)arr.size();
    vector<int> result(n, -1);   // default: -1 (no greater element)
    stack<int>  stk;             // stores INDICES of elements awaiting their NGE

    for (int i = 0; i < n; i++) {
        // Current element arr[i] might be the NGE for pending elements
        while (!stk.empty() && arr[i] > arr[stk.top()]) {
            result[stk.top()] = arr[i];   // arr[i] is the NGE for arr[stk.top()]
            stk.pop();
        }
        stk.push(i);    // this element has no NGE yet — add to pending
    }
    // All remaining elements in stack have no NGE → result[stk.top()] = -1 (already set)

    return result;
}

// ============================================================
// SECTION 2: PREVIOUS GREATER ELEMENT (← left)
// ============================================================
// Process right to left (or use the same left-to-right with
// a stack that answers queries for the current element).
//
// Time: O(n)  |  Space: O(n)
// ------------------------------------------------------------ 

/**
 * For each element, returns the previous greater element to its left.
 * If no greater element exists, returns -1.
 */
vector<int> prevGreaterLeft(const vector<int>& arr) {
    int n = (int)arr.size();
    vector<int> result(n, -1);
    stack<int>  stk;   // stores VALUES (not indices) here

    for (int i = 0; i < n; i++) {
        // Pop elements that are <= arr[i] (they cannot be PGE for arr[i])
        while (!stk.empty() && stk.top() <= arr[i]) stk.pop();

        result[i] = stk.empty() ? -1 : stk.top();   // nearest greater to left
        stk.push(arr[i]);
    }

    return result;
}

// ============================================================
// SECTION 3: NEXT SMALLER ELEMENT (→ right)
// ============================================================
// Same pattern but we pop when current < stack.top().
// ------------------------------------------------------------ 

/**
 * For each element, returns the next smaller element to its right.
 */
vector<int> nextSmallerRight(const vector<int>& arr) {
    int n = (int)arr.size();
    vector<int> result(n, -1);
    stack<int>  stk;

    for (int i = 0; i < n; i++) {
        while (!stk.empty() && arr[i] < arr[stk.top()]) {
            result[stk.top()] = arr[i];
            stk.pop();
        }
        stk.push(i);
    }

    return result;
}

// ============================================================
// SECTION 4: NEXT GREATER IN CIRCULAR ARRAY
// ============================================================
// The array wraps around. We process the array TWICE (0..2n-1)
// using index % n to simulate circular traversal.
//
// Time: O(n)  |  Space: O(n)
// ------------------------------------------------------------ 

/**
 * For a circular array, returns the next greater element for each position.
 */
vector<int> nextGreaterCircular(const vector<int>& arr) {
    int n = (int)arr.size();
    vector<int> result(n, -1);
    stack<int>  stk;

    // Process 2n elements to simulate circular traversal
    for (int i = 2 * n - 1; i >= 0; i--) {
        // Pop elements that are <= current
        while (!stk.empty() && stk.top() <= arr[i % n]) stk.pop();

        if (i < n)
            result[i] = stk.empty() ? -1 : stk.top();  // only record for first pass

        stk.push(arr[i % n]);
    }

    return result;
}

// ============================================================
// SECTION 5: STOCK SPAN PROBLEM
// ============================================================
// Given stock prices for each day, find the span for each day.
// Span[i] = consecutive days before day i where price <= price[i].
//
// When the price today is higher than previous days, those days
// are "spanned". Use a monotonic stack storing day indices.
//
// Time: O(n)  |  Space: O(n)
// ------------------------------------------------------------ 

/**
 * Returns the span for each day's stock price.
 * Span[i] = how many consecutive days (including today) price was <= price[i]
 */
vector<int> stockSpan(const vector<int>& prices) {
    int n = (int)prices.size();
    vector<int> span(n);
    stack<int>  stk;   // stores indices; elements maintain decreasing price order

    for (int i = 0; i < n; i++) {
        // Pop days with lower or equal prices (they are spanned by today)
        while (!stk.empty() && prices[stk.top()] <= prices[i]) stk.pop();

        // If stack empty → all previous days are spanned (span = i+1)
        span[i] = stk.empty() ? i + 1 : i - stk.top();

        stk.push(i);
    }

    return span;
}

// ============================================================
// SECTION 6: LARGEST RECTANGLE IN HISTOGRAM
// ============================================================
// Given bar heights, find the area of the largest rectangle.
//
// For each bar, the max width extends left and right until a shorter bar.
// Use NGE (next smaller) and PGE (prev smaller) to find boundaries.
//
// Time: O(n)  |  Space: O(n)
// ------------------------------------------------------------ 

/**
 * Returns the area of the largest rectangle in histogram.
 */
int largestRectangle(const vector<int>& heights) {
    int n = (int)heights.size();
    stack<int> stk;
    int maxArea = 0;

    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];   // sentinel 0 at end

        while (!stk.empty() && h < heights[stk.top()]) {
            int height = heights[stk.top()];
            stk.pop();
            int width  = stk.empty() ? i : i - stk.top() - 1;
            maxArea    = max(maxArea, height * width);
        }
        stk.push(i);
    }

    return maxArea;
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Next Greater Right ---
    cout << "=== NEXT GREATER ELEMENT (right) ===" << "\n";
    vector<int> arr1 = {4, 5, 2, 10, 8};
    printPairs("NGE right:", arr1, nextGreaterRight(arr1));

    vector<int> arr2 = {1, 3, 2, 4};
    printPairs("NGE right:", arr2, nextGreaterRight(arr2));

    // --- Previous Greater Left ---
    cout << "\n=== PREVIOUS GREATER ELEMENT (left) ===" << "\n";
    printPairs("PGE left:", arr1, prevGreaterLeft(arr1));

    // --- Next Smaller Right ---
    cout << "\n=== NEXT SMALLER ELEMENT (right) ===" << "\n";
    vector<int> arr3 = {4, 2, 7, 3, 1};
    printPairs("NSE right:", arr3, nextSmallerRight(arr3));

    // --- Next Greater Circular ---
    cout << "\n=== NEXT GREATER CIRCULAR ===" << "\n";
    vector<int> circ = {1, 2, 1};
    printPairs("NGE circular:", circ, nextGreaterCircular(circ));

    vector<int> circ2 = {5, 4, 3, 2, 1};
    printPairs("NGE circular:", circ2, nextGreaterCircular(circ2));

    // --- Stock Span ---
    cout << "\n=== STOCK SPAN PROBLEM ===" << "\n";
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    cout << "  Prices: [100,80,60,70,60,75,85]\n";
    auto spans = stockSpan(prices);
    cout << "  Spans : [";
    for (int i = 0; i < (int)spans.size(); i++)
        cout << spans[i] << (i+1<(int)spans.size()?",":"");
    cout << "]\n";
    // Expected: [1,1,1,2,1,4,6]

    // --- Largest Rectangle in Histogram ---
    cout << "\n=== LARGEST RECTANGLE IN HISTOGRAM ===" << "\n";
    vector<int> h1 = {2, 1, 5, 6, 2, 3};
    vector<int> h2 = {6, 2, 5, 4, 5, 1, 6};
    vector<int> h3 = {2, 4};
    cout << "  Heights [2,1,5,6,2,3]   → max rect: " << largestRectangle(h1) << "\n";  // 10
    cout << "  Heights [6,2,5,4,5,1,6] → max rect: " << largestRectangle(h2) << "\n";  // 12
    cout << "  Heights [2,4]           → max rect: " << largestRectangle(h3) << "\n";  // 4

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   nextGreaterRight   : O(n) time, O(n) space
//   prevGreaterLeft    : O(n) time, O(n) space
//   nextSmallerRight   : O(n) time, O(n) space
//   nextGreaterCircular: O(n) time, O(n) space
//   stockSpan          : O(n) time, O(n) space
//   largestRectangle   : O(n) time, O(n) space
//
// KEY INSIGHT: Monotonic Stack
//   Maintain stack in monotonically decreasing (or increasing) order.
//   Pop elements that violate the order — those are "answered" by
//   the current element.
//   Each element is pushed and popped at most once → O(n) total.
// ============================================================
