// ============================================================
// DSA | C++ → Sorting Algorithms — Complete Reference
// ============================================================
// DESCRIPTION:
//   All major sorting algorithms implemented from scratch
//   with complexity analysis, stable/unstable notes.
//
// ALGORITHMS:
//   1. Bubble Sort      — O(n²) stable
//   2. Selection Sort   — O(n²) unstable
//   3. Insertion Sort   — O(n²) stable (best O(n))
//   4. Merge Sort       — O(n log n) stable
//   5. Quick Sort       — O(n log n) avg, unstable
//   6. Heap Sort        — O(n log n) unstable
//   7. Counting Sort    — O(n+k) stable (non-comparison)
//   8. Radix Sort       — O(d*(n+k)) stable
//
// COMPILE & RUN:
//   g++ -std=c++17 02_all_sorting_algorithms.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>    // max_element
#include <string>
using namespace std;

void print(const string& label, const vector<int>& arr) {
    cout << "  " << label << ": [";
    for (int i = 0; i < (int)arr.size(); i++)
        cout << arr[i] << (i+1<(int)arr.size()?",":"");
    cout << "]\n";
}

// ============================================================
// 1. BUBBLE SORT — O(n²) stable
// ============================================================
// Compare adjacent pairs; swap if out of order.
// Largest element "bubbles" to end each pass.
// Optimised: stop early if no swaps in a pass (already sorted).
// ------------------------------------------------------------ 

/**
 * Time: O(n²) worst/avg, O(n) best (already sorted)
 * Space: O(1)  |  Stable: YES
 */
void bubbleSort(vector<int>& arr) {
    int n = (int)arr.size();
    for (int pass = 0; pass < n - 1; pass++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - pass; j++) {   // last `pass` elements are sorted
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // early exit: no swaps = already sorted
    }
}

// ============================================================
// 2. SELECTION SORT — O(n²) unstable
// ============================================================
// Find the minimum in the unsorted portion; swap it to position i.
// ------------------------------------------------------------ 

/**
 * Time: O(n²) all cases  |  Space: O(1)  |  Stable: NO
 */
void selectionSort(vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(arr[i], arr[minIdx]);   // place minimum at position i
    }
}

// ============================================================
// 3. INSERTION SORT — O(n²) stable, O(n) best
// ============================================================
// Pick next element; shift larger sorted elements right, then insert.
// Excellent for nearly-sorted data and small arrays.
// ------------------------------------------------------------ 

/**
 * Time: O(n²) worst, O(n) best  |  Space: O(1)  |  Stable: YES
 */
void insertionSort(vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];   // element to insert into sorted portion
        int j   = i - 1;

        // Shift elements greater than key to one position right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;  // place key in its correct sorted position
    }
}

// ============================================================
// 4. MERGE SORT — O(n log n) stable
// ============================================================
// Divide: split array into two halves.
// Conquer: recursively sort each half.
// Combine: merge two sorted halves into one sorted array.
// ------------------------------------------------------------ 

/**
 * Merges arr[left..mid] and arr[mid+1..right] into sorted order.
 * Time: O(n)  |  Space: O(n) temporary
 */
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];   // <= preserves stable order
        else                  temp[k++] = arr[j++];
    }
    while (i <= mid)   temp[k++] = arr[i++];  // remaining left
    while (j <= right) temp[k++] = arr[j++];  // remaining right

    for (int x = 0; x < k; x++) arr[left + x] = temp[x];  // copy back
}

/**
 * Time: O(n log n) all cases  |  Space: O(n)  |  Stable: YES
 */
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;   // base: 0 or 1 element

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);      // sort left half
    mergeSort(arr, mid + 1, right); // sort right half
    merge(arr, left, mid, right);   // merge the sorted halves
}

// ============================================================
// 5. QUICK SORT — O(n log n) average, O(n²) worst
// ============================================================
// Choose pivot; partition elements smaller to left, larger to right.
// Recursively sort the two partitions.
// Pivot choice matters: random pivot avoids O(n²) worst case.
// ------------------------------------------------------------ 

/**
 * Lomuto partition: pivot = arr[right].
 * Returns final position of pivot.
 */
int partition(vector<int>& arr, int low, int high) {
    int pivot    = arr[high];  // pivot is last element
    int storeIdx = low;        // index where next smaller element goes

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[storeIdx], arr[j]);
            storeIdx++;
        }
    }
    swap(arr[storeIdx], arr[high]);   // place pivot in correct position
    return storeIdx;
}

/**
 * Time: O(n log n) avg, O(n²) worst  |  Space: O(log n) stack  |  Stable: NO
 */
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // pivot index after partitioning
        quickSort(arr, low, pi - 1);         // sort left of pivot
        quickSort(arr, pi + 1, high);        // sort right of pivot
    }
}

// ============================================================
// 6. HEAP SORT — O(n log n) in-place, unstable
// ============================================================
// Build a max-heap from the array.
// Repeatedly extract the max (swap root with last), heapify.
// ------------------------------------------------------------ 

/**
 * Maintains max-heap property for subtree rooted at i.
 * n = heap size, i = root of subtree.
 */
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;               // assume root is largest
    int left    = 2 * i + 1;      // left child index
    int right   = 2 * i + 2;      // right child index

    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);   // fix the affected subtree
    }
}

/**
 * Time: O(n log n) all cases  |  Space: O(1)  |  Stable: NO
 */
void heapSort(vector<int>& arr) {
    int n = (int)arr.size();

    // Step 1: Build max-heap (bottom-up, start from last non-leaf)
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    // Step 2: Extract max one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);       // move current max to end
        heapify(arr, i, 0);         // restore max-heap for remaining i elements
    }
}

// ============================================================
// 7. COUNTING SORT — O(n + k), k = range of values
// ============================================================
// Not a comparison sort! Counts occurrences and computes positions.
// Only works for non-negative integers.
// ------------------------------------------------------------ 

/**
 * Time: O(n + k)  |  Space: O(k)  |  Stable: YES
 * @param arr  Input array
 * @param k    Maximum value (inclusive) in arr
 */
void countingSort(vector<int>& arr, int k) {
    if (arr.empty()) return;

    vector<int> count(k + 1, 0);

    // Count occurrences
    for (int x : arr) count[x]++;

    // Prefix sum → gives starting index for each value
    for (int i = 1; i <= k; i++) count[i] += count[i - 1];

    // Build output array (traverse input right-to-left for stability)
    vector<int> output(arr.size());
    for (int i = (int)arr.size() - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    arr = output;
}

// ============================================================
// 8. RADIX SORT — O(d * (n + k))
// ============================================================
// Sort by each digit position from least significant to most.
// Uses counting sort as a stable subroutine for each digit.
// ------------------------------------------------------------ 

void countingSortByDigit(vector<int>& arr, int exp) {
    int n = (int)arr.size();
    vector<int> output(n), count(10, 0);

    // Count occurrences of each digit (0–9) at position exp
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;

    // Prefix sum
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    // Build output (right-to-left for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }

    arr = output;
}

/**
 * Time: O(d * (n + 10)) = O(d * n)  |  Space: O(n)  |  Stable: YES
 * d = number of digits in maximum element
 */
void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());

    // Sort for each digit position (1s, 10s, 100s, ...)
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortByDigit(arr, exp);
}

// ============================================================
// MAIN: Run and compare all sorting algorithms
// ============================================================
int main() {
    vector<int> original = {64, 34, 25, 12, 22, 11, 90, 5, 47, 31};

    cout << "=== SORTING ALGORITHMS COMPARISON ===" << "\n";
    print("Original", original);

    auto test = [&](const string& name, auto sortFn) {
        vector<int> arr = original;
        sortFn(arr);
        print(name, arr);
    };

    test("Bubble Sort   ", [](vector<int>& a){ bubbleSort(a); });
    test("Selection Sort", [](vector<int>& a){ selectionSort(a); });
    test("Insertion Sort", [](vector<int>& a){ insertionSort(a); });
    test("Merge Sort    ", [](vector<int>& a){ mergeSort(a, 0, (int)a.size()-1); });
    test("Quick Sort    ", [](vector<int>& a){ quickSort(a, 0, (int)a.size()-1); });
    test("Heap Sort     ", [](vector<int>& a){ heapSort(a); });
    test("Counting Sort ", [](vector<int>& a){ countingSort(a, *max_element(a.begin(),a.end())); });
    test("Radix Sort    ", [](vector<int>& a){ radixSort(a); });

    // --- Edge cases ---
    cout << "\n=== EDGE CASES ===" << "\n";
    vector<int> empty = {};
    vector<int> single = {42};
    vector<int> sorted = {1,2,3,4,5};
    vector<int> reverse_ = {5,4,3,2,1};
    vector<int> dupes = {3,1,4,1,5,9,2,6,5,3};

    for (auto arr : {empty, single, sorted, reverse_, dupes}) {
        bubbleSort(arr);
        print("bubble sorted", arr);
    }

    return 0;
}

// ============================================================
// COMPARISON TABLE
//   Algorithm    | Best    | Avg     | Worst   | Space   | Stable
//   Bubble       | O(n)    | O(n²)   | O(n²)   | O(1)    | Yes
//   Selection    | O(n²)   | O(n²)   | O(n²)   | O(1)    | No
//   Insertion    | O(n)    | O(n²)   | O(n²)   | O(1)    | Yes
//   Merge        | O(nlogn)| O(nlogn)| O(nlogn)| O(n)    | Yes
//   Quick        | O(nlogn)| O(nlogn)| O(n²)   | O(logn) | No
//   Heap         | O(nlogn)| O(nlogn)| O(nlogn)| O(1)    | No
//   Counting     | O(n+k)  | O(n+k)  | O(n+k)  | O(k)    | Yes
//   Radix        | O(dn)   | O(dn)   | O(dn)   | O(n)    | Yes
//
// CHOOSE BASED ON:
//   Small array / nearly sorted → Insertion Sort
//   General purpose            → QuickSort (practical) / MergeSort (guaranteed)
//   Need stability             → Merge Sort
//   Integer range known        → Counting Sort / Radix Sort
//   Memory is priority         → Heap Sort
// ============================================================
