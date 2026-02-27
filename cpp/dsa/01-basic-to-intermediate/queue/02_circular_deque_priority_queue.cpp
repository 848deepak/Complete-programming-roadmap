// ============================================================
// DSA | C++ → Queue: Circular Queue & Deque & Priority Queue
// ============================================================
// DESCRIPTION:
//   Covers all queue variants:
//   1. Circular Queue (fixed-size array, O(1) enqueue/dequeue)
//   2. Deque (Double-ended Queue)
//   3. Priority Queue from scratch (min/max heap)
//
// COMPILE & RUN:
//   g++ -std=c++17 02_circular_deque_priority_queue.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

// ============================================================
// SECTION 1: CIRCULAR QUEUE (Fixed-size Array)
// ============================================================
// Solves the "false full" problem of regular linear queue.
// Uses modular arithmetic to wrap front/rear pointers.
//
//   [rear writes] →  [data] [data] ... [data]  → [front reads]
//                         (circular wrap with %)
//
// Time: enqueue O(1), dequeue O(1)
// Space: O(capacity)
// ------------------------------------------------------------ 

class CircularQueue {
    vector<int> data_;
    int front_, rear_, size_, capacity_;

public:
    explicit CircularQueue(int cap)
        : data_(cap), front_(0), rear_(0), size_(0), capacity_(cap) {}

    bool empty()    const { return size_ == 0; }
    bool full()     const { return size_ == capacity_; }
    int  size()     const { return size_; }
    int  capacity() const { return capacity_; }

    /** Peek front element without removing. */
    int front() const {
        if (empty()) throw underflow_error("Queue is empty");
        return data_[front_];
    }

    /** Peek rear element without removing. */
    int back() const {
        if (empty()) throw underflow_error("Queue is empty");
        return data_[(rear_ - 1 + capacity_) % capacity_];
    }

    /**
     * Enqueue: add element to rear.
     * Time: O(1)
     */
    void enqueue(int val) {
        if (full()) throw overflow_error("CircularQueue: overflow");
        data_[rear_] = val;
        rear_        = (rear_ + 1) % capacity_;  // wrap around
        size_++;
    }

    /**
     * Dequeue: remove element from front.
     * Time: O(1)
     */
    int dequeue() {
        if (empty()) throw underflow_error("CircularQueue: underflow");
        int val = data_[front_];
        front_  = (front_ + 1) % capacity_;     // wrap around
        size_--;
        return val;
    }

    void print(const string& label = "") const {
        if (!label.empty()) cout << label << "\n";
        cout << "  [front → rear] ";
        int idx = front_;
        for (int i = 0; i < size_; i++) {
            cout << data_[idx];
            if (i < size_ - 1) cout << ", ";
            idx = (idx + 1) % capacity_;
        }
        cout << "  (size=" << size_ << "/" << capacity_ << ")\n";
    }
};

// ============================================================
// SECTION 2: DEQUE (Double-Ended Queue)
// ============================================================
// Supports insertion and deletion at BOTH front and rear in O(1).
// Implemented using a doubly linked list internally.
// Used in: sliding window maximum, palindrome checking.
// ------------------------------------------------------------ 

class Deque {
    struct Node {
        int   data;
        Node* prev;
        Node* next;
        explicit Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    int   size_;

public:
    Deque() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~Deque() {
        while (head_) {
            Node* tmp = head_;
            head_     = head_->next;
            delete tmp;
        }
    }

    bool empty() const { return size_ == 0; }
    int  size()  const { return size_; }

    int front() const {
        if (empty()) throw underflow_error("Deque empty");
        return head_->data;
    }

    int back() const {
        if (empty()) throw underflow_error("Deque empty");
        return tail_->data;
    }

    /** Add to front. O(1) */
    void pushFront(int val) {
        Node* node = new Node(val);
        if (empty()) {
            head_ = tail_ = node;
        } else {
            node->next  = head_;
            head_->prev = node;
            head_       = node;
        }
        size_++;
    }

    /** Add to back. O(1) */
    void pushBack(int val) {
        Node* node = new Node(val);
        if (empty()) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev  = tail_;
            tail_       = node;
        }
        size_++;
    }

    /** Remove from front. O(1) */
    int popFront() {
        if (empty()) throw underflow_error("Deque empty");
        Node* tmp = head_;
        int   val = head_->data;
        head_     = head_->next;
        if (head_) head_->prev = nullptr;
        else       tail_ = nullptr;
        delete tmp;
        size_--;
        return val;
    }

    /** Remove from back. O(1) */
    int popBack() {
        if (empty()) throw underflow_error("Deque empty");
        Node* tmp = tail_;
        int   val = tail_->data;
        tail_     = tail_->prev;
        if (tail_) tail_->next = nullptr;
        else       head_ = nullptr;
        delete tmp;
        size_--;
        return val;
    }

    void print(const string& label = "") const {
        if (!label.empty()) cout << label << "\n";
        cout << "  FRONT ↔ ";
        Node* curr = head_;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " ↔ ";
            curr = curr->next;
        }
        cout << " ↔ BACK  (size=" << size_ << ")\n";
    }
};

// ============================================================
// APPLICATION: SLIDING WINDOW MAXIMUM using Deque
// ============================================================
// For each window of size k, find the maximum.
// Maintain deque of indices in decreasing order of element value.
// Uses STL deque which supports O(1) front/back push/pop.
//
// Time: O(n)  |  Space: O(k)
// ------------------------------------------------------------ 

#include <deque>

vector<int> slidingWindowMaxSTL(const vector<int>& arr, int k) {
    deque<int>  dq;       // stores indices; front = max index
    vector<int> result;
    int n = (int)arr.size();

    for (int i = 0; i < n; i++) {
        // Remove indices outside current window
        while (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();

        // Remove indices of elements smaller than arr[i] from back
        while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();

        dq.push_back(i);

        if (i >= k - 1)   // window is full
            result.push_back(arr[dq.front()]);   // front = max
    }

    return result;
}

// ============================================================
// SECTION 3: PRIORITY QUEUE (Min-Heap from scratch)
// ============================================================
// Binary Min-Heap stored in array. Parent at index i has children at 2i+1, 2i+2.
//
// heapifyUp   : used after insert (bubble up)
// heapifyDown : used after extract (bubble down)
//
// Time: insert O(log n), extractMin O(log n), peek O(1)
// Space: O(n)
// ------------------------------------------------------------ 

class MinPriorityQueue {
    vector<int> heap_;   // 0-indexed binary heap

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap_[parent(i)] > heap_[i]) {
            swap(heap_[parent(i)], heap_[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int n        = (int)heap_.size();

        if (left(i)  < n && heap_[left(i)]  < heap_[smallest]) smallest = left(i);
        if (right(i) < n && heap_[right(i)] < heap_[smallest]) smallest = right(i);

        if (smallest != i) {
            swap(heap_[i], heap_[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    bool empty() const { return heap_.empty(); }
    int  size()  const { return (int)heap_.size(); }
    int  peek()  const {
        if (empty()) throw underflow_error("PQ empty");
        return heap_[0];   // root = minimum
    }

    /**
     * Insert element. Adds to end then bubbles up.
     * Time: O(log n)
     */
    void insert(int val) {
        heap_.push_back(val);
        heapifyUp((int)heap_.size() - 1);
    }

    /**
     * Extract minimum element (root).
     * Swap root with last, pop last, then heapify down.
     * Time: O(log n)
     */
    int extractMin() {
        if (empty()) throw underflow_error("PQ empty");
        int minVal    = heap_[0];
        heap_[0]      = heap_.back();
        heap_.pop_back();
        if (!empty()) heapifyDown(0);
        return minVal;
    }

    void print(const string& label = "") const {
        if (!label.empty()) cout << label << "\n";
        cout << "  Heap: [";
        for (int i = 0; i < (int)heap_.size(); i++)
            cout << heap_[i] << (i+1<(int)heap_.size()?",":"");
        cout << "]  min=" << (empty() ? -1 : heap_[0]) << "\n";
    }
};

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Circular Queue ---
    cout << "=== CIRCULAR QUEUE (capacity=5) ===" << "\n";
    CircularQueue cq(5);
    cq.enqueue(10); cq.enqueue(20); cq.enqueue(30); cq.enqueue(40); cq.enqueue(50);
    cq.print("After 5 enqueues:");
    cout << "  front=" << cq.front() << "  back=" << cq.back() << "\n";
    cq.dequeue(); cq.dequeue();
    cq.print("After 2 dequeues:");
    cq.enqueue(60); cq.enqueue(70);   // wraps around!
    cq.print("After 2 more enqueues (wraparound):");
    try { cq.enqueue(80); } catch (const exception& e) { cout << "  Overflow: " << e.what() << "\n"; }

    // --- Deque ---
    cout << "\n=== DEQUE (double-ended queue) ===" << "\n";
    Deque dq;
    dq.pushBack(10);
    dq.pushBack(20);
    dq.pushFront(5);
    dq.pushFront(1);
    dq.print("After pushBack(10,20) + pushFront(5,1):");
    cout << "  popFront() → " << dq.popFront() << "\n";
    cout << "  popBack()  → " << dq.popBack()  << "\n";
    dq.print("After pops:");

    // --- Sliding Window Maximum ---
    cout << "\n=== SLIDING WINDOW MAXIMUM (k=3) ===" << "\n";
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    auto maxArr = slidingWindowMaxSTL(arr, 3);
    cout << "  Input: [1,3,-1,-3,5,3,6,7]\n";
    cout << "  Max of each window k=3: [";
    for (int i = 0; i < (int)maxArr.size(); i++)
        cout << maxArr[i] << (i+1<(int)maxArr.size()?",":"");
    cout << "]\n";   // [3,3,5,5,6,7]

    // --- Min Priority Queue ---
    cout << "\n=== MIN PRIORITY QUEUE (from scratch) ===" << "\n";
    MinPriorityQueue pq;
    for (int v : {5, 3, 8, 1, 9, 2, 7}) pq.insert(v);
    pq.print("After inserting {5,3,8,1,9,2,7}:");
    cout << "  Extracting in order: ";
    while (!pq.empty()) cout << pq.extractMin() << " ";
    cout << "\n";   // 1 2 3 5 7 8 9

    // --- Edge cases ---
    cout << "\n=== EDGE CASES ===" << "\n";
    CircularQueue empty(3);
    try { empty.dequeue(); } catch (const underflow_error& e) { cout << "  " << e.what() << "\n"; }
    MinPriorityQueue emptyPQ;
    try { emptyPQ.extractMin(); } catch (const underflow_error& e) { cout << "  " << e.what() << "\n"; }

    return 0;
}
