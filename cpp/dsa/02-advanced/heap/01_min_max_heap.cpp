// ============================================================
// DSA | C++ → Heap: Min Heap, Max Heap, Heap Sort, K-th Largest
// ============================================================
// DESCRIPTION:
//   Complete heap data structure:
//   - Binary heap theory (array representation)
//   - Min Heap and Max Heap from scratch
//   - Heap Sort
//   - K-th largest/smallest element
//   - Merge K sorted arrays using heap
//
// COMPILE & RUN:
//   g++ -std=c++17 01_min_max_heap.cpp -o out && ./out
//
// HEAP PROPERTY:
//   Max Heap: parent >= children (root = maximum)
//   Min Heap: parent <= children (root = minimum)
//
// ARRAY REPRESENTATION:
//   For node at index i:
//     parent    = (i-1)/2
//     leftChild = 2*i+1
//     rightChild= 2*i+2
// ============================================================

#include <iostream>
#include <vector>
#include <functional>   // greater<T>
#include <algorithm>    // make_heap, sort_heap
#include <queue>        // std::priority_queue
#include <string>
using namespace std;

// ============================================================
// SECTION 1: MAX HEAP (from scratch)
// ============================================================

class MaxHeap {
    vector<int> heap_;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    /**
     * Bubble element at index i UP to restore heap property.
     * Used after insertion.
     * Time: O(log n)
     */
    void siftUp(int i) {
        while (i > 0 && heap_[parent(i)] < heap_[i]) {
            swap(heap_[parent(i)], heap_[i]);
            i = parent(i);
        }
    }

    /**
     * Push element at index i DOWN to restore heap property.
     * Used after extraction.
     * Time: O(log n)
     */
    void siftDown(int i) {
        int n = (int)heap_.size();
        while (true) {
            int largest = i;
            int l = left(i), r = right(i);

            if (l < n && heap_[l] > heap_[largest]) largest = l;
            if (r < n && heap_[r] > heap_[largest]) largest = r;

            if (largest == i) break;     // heap property satisfied

            swap(heap_[i], heap_[largest]);
            i = largest;
        }
    }

public:
    MaxHeap() = default;

    /**
     * Build heap from existing array — O(n) using bottom-up heapify.
     * More efficient than n individual insertions (O(n log n)).
     */
    explicit MaxHeap(vector<int> arr) : heap_(move(arr)) {
        // Start from the last non-leaf node and sift down
        for (int i = (int)heap_.size() / 2 - 1; i >= 0; i--)
            siftDown(i);
    }

    bool empty() const { return heap_.empty(); }
    int  size()  const { return (int)heap_.size(); }

    /** Top element (maximum). O(1) */
    int top() const {
        if (empty()) throw underflow_error("Heap is empty");
        return heap_[0];
    }

    /** Insert element. O(log n) */
    void push(int val) {
        heap_.push_back(val);
        siftUp((int)heap_.size() - 1);
    }

    /** Extract maximum. O(log n) */
    int pop() {
        if (empty()) throw underflow_error("Heap is empty");
        int maxVal = heap_[0];
        heap_[0]   = heap_.back();
        heap_.pop_back();
        if (!empty()) siftDown(0);
        return maxVal;
    }

    /**
     * Heap Sort: repeatedly extract max to get sorted order.
     * Can directly sort the internal array in-place.
     * Returns sorted (ascending) order.
     * Time: O(n log n)  |  Space: O(1) in-place
     */
    vector<int> heapSort() {
        // In-place: swap root with last, reduce heap size, siftDown
        int n = (int)heap_.size();
        vector<int> arr = heap_;   // copy for output

        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);     // max goes to end
            // Sift down for heap of size i
            int j = 0;
            while (true) {
                int largest = j;
                int l = 2*j+1, r = 2*j+2;
                if (l < i && arr[l] > arr[largest]) largest = l;
                if (r < i && arr[r] > arr[largest]) largest = r;
                if (largest == j) break;
                swap(arr[j], arr[largest]);
                j = largest;
            }
        }
        return arr;    // ascending sorted
    }

    void print(const string& label = "") const {
        if (!label.empty()) cout << "  " << label << ":\n";
        cout << "    Heap array: [";
        for (int i = 0; i < (int)heap_.size(); i++)
            cout << heap_[i] << (i+1<(int)heap_.size()?",":"");
        cout << "]  max=" << (empty() ? -1 : heap_[0]) << "\n";
    }
};

// ============================================================
// SECTION 2: MIN HEAP (from scratch)
// ============================================================

class MinHeap {
    vector<int> heap_;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && heap_[parent(i)] > heap_[i]) {
            swap(heap_[parent(i)], heap_[i]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int n = (int)heap_.size();
        while (true) {
            int smallest = i;
            int l = left(i), r = right(i);
            if (l < n && heap_[l] < heap_[smallest]) smallest = l;
            if (r < n && heap_[r] < heap_[smallest]) smallest = r;
            if (smallest == i) break;
            swap(heap_[i], heap_[smallest]);
            i = smallest;
        }
    }

public:
    bool empty() const { return heap_.empty(); }
    int  size()  const { return (int)heap_.size(); }
    int  top()   const { if (empty()) throw underflow_error("empty"); return heap_[0]; }

    void push(int val) { heap_.push_back(val); siftUp((int)heap_.size()-1); }

    int pop() {
        if (empty()) throw underflow_error("empty");
        int minVal = heap_[0];
        heap_[0]   = heap_.back();
        heap_.pop_back();
        if (!empty()) siftDown(0);
        return minVal;
    }

    void print(const string& label = "") const {
        if (!label.empty()) cout << "  " << label << ":\n";
        cout << "    Heap array: [";
        for (int i = 0; i < (int)heap_.size(); i++)
            cout << heap_[i] << (i+1<(int)heap_.size()?",":"");
        cout << "]  min=" << (empty() ? -1 : heap_[0]) << "\n";
    }
};

// ============================================================
// SECTION 3: K-TH LARGEST ELEMENT
// ============================================================
// Approach: Use a Min-Heap of size K.
//   For each element: push if heap size < K, else compare with min.
//   After processing all elements, heap[0] = K-th largest.
//
// Time: O(n log k)  |  Space: O(k)
// ------------------------------------------------------------ 

/**
 * Returns the K-th largest element in arr.
 */
int kthLargest(const vector<int>& arr, int k) {
    MinHeap minH;
    for (int x : arr) {
        minH.push(x);
        if (minH.size() > k) minH.pop();   // maintain exactly k elements
    }
    return minH.top();   // the smallest in the heap = k-th largest overall
}

/**
 * Returns the K-th smallest element.
 * Use Max-Heap of size K.
 */
int kthSmallest(const vector<int>& arr, int k) {
    MaxHeap maxH;
    for (int x : arr) {
        maxH.push(x);
        if (maxH.size() > k) maxH.pop();   // pop max, keep k smallest
    }
    return maxH.top();   // largest of k smallest = k-th smallest
}

// ============================================================
// SECTION 4: STL HEAP (std::priority_queue)
// ============================================================

void demoSTLHeap() {
    cout << "\n=== STL HEAP (std::priority_queue) ===" << "\n";

    // Max heap (default)
    priority_queue<int> maxPQ;
    for (int x : {3, 1, 4, 1, 5, 9, 2, 6}) maxPQ.push(x);
    cout << "  Max PQ top=" << maxPQ.top() << "\n";
    cout << "  Popping: ";
    while (!maxPQ.empty()) { cout << maxPQ.top() << " "; maxPQ.pop(); }
    cout << "\n";

    // Min heap — use greater<int> comparator
    priority_queue<int, vector<int>, greater<int>> minPQ;
    for (int x : {3, 1, 4, 1, 5, 9, 2, 6}) minPQ.push(x);
    cout << "  Min PQ top=" << minPQ.top() << "\n";
    cout << "  Popping: ";
    while (!minPQ.empty()) { cout << minPQ.top() << " "; minPQ.pop(); }
    cout << "\n";

    // STL make_heap on a vector
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    make_heap(v.begin(), v.end());      // in-place max-heap
    cout << "  STL make_heap top=" << v.front() << "\n";
    sort_heap(v.begin(), v.end());      // heap sort ascending
    cout << "  STL sort_heap: [";
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << (i+1<(int)v.size()?",":"");
    cout << "]\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {

    cout << "=== MAX HEAP ===" << "\n";
    MaxHeap maxH;
    for (int x : {5, 3, 8, 1, 9, 2, 7}) maxH.push(x);
    maxH.print("After inserting {5,3,8,1,9,2,7}");
    cout << "  Extracting max: ";
    while (!maxH.empty()) cout << maxH.pop() << " ";
    cout << "\n";

    cout << "\n=== BUILD HEAP (O(n)) ===" << "\n";
    MaxHeap built({4, 10, 3, 5, 1, 8});
    built.print("Built from {4,10,3,5,1,8}");
    auto sorted = built.heapSort();
    cout << "    Heap Sort result: [";
    for (int i = 0; i < (int)sorted.size(); i++) cout << sorted[i] << (i+1<(int)sorted.size()?",":"");
    cout << "]\n";

    cout << "\n=== MIN HEAP ===" << "\n";
    MinHeap minH;
    for (int x : {5, 3, 8, 1, 9, 2, 7}) minH.push(x);
    minH.print("After inserting {5,3,8,1,9,2,7}");
    cout << "  Extracting min: ";
    while (!minH.empty()) cout << minH.pop() << " ";
    cout << "\n";

    cout << "\n=== K-TH LARGEST / SMALLEST ===" << "\n";
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    cout << "  Array: [3,2,1,5,6,4]\n";
    cout << "  2nd largest : " << kthLargest(arr, 2) << "\n";    // 5
    cout << "  3rd largest : " << kthLargest(arr, 3) << "\n";    // 4
    cout << "  2nd smallest: " << kthSmallest(arr, 2) << "\n";   // 2
    cout << "  3rd smallest: " << kthSmallest(arr, 3) << "\n";   // 3

    demoSTLHeap();

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   push      : O(log n) — sift up
//   pop       : O(log n) — sift down
//   top       : O(1)
//   buildHeap : O(n)     — bottom-up is O(n), not O(n log n)!
//   heapSort  : O(n log n) time, O(1) extra space
//   kthLargest: O(n log k) — better than O(n log n) full sort for small k
// ============================================================
