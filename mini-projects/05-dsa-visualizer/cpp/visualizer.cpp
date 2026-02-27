/*
 * DSA Visualizer — C++ Console Implementation
 * Visually demonstrates sorting, searching, and data structure operations
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;

// ===================== Utility =====================

void printArray(const vector<int>& arr, int highlight1 = -1, int highlight2 = -1) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (i == highlight1 || i == highlight2)
            cout << "[" << setw(3) << arr[i] << "]";
        else
            cout << " " << setw(3) << arr[i] << " ";
    }
    cout << "\n";
}

void printBar(const vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int h = maxVal; h >= 1; h--) {
        for (int i = 0; i < (int)arr.size(); i++)
            cout << (arr[i] >= h ? " █ " : "   ");
        cout << "\n";
    }
    for (int i = 0; i < (int)arr.size(); i++)
        cout << setw(3) << arr[i];
    cout << "\n";
}

void wait() {
    cout << "  Press Enter to continue...";
    cin.get();
}

// ===================== Sorting Visualizer =====================

void bubbleSortVisual(vector<int> arr) {
    cout << "\n🫧 Bubble Sort Visualization\n";
    cout << "Initial: "; printArray(arr);
    int n = arr.size(), swaps = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            cout << "Compare: "; printArray(arr, j, j+1);
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swaps++;
                cout << "Swapped: "; printArray(arr, j, j+1);
            }
        }
        cout << "--- Pass " << i+1 << " complete ---\n";
    }
    cout << "✅ Sorted: "; printArray(arr);
    cout << "Total swaps: " << swaps << "\n";
}

void selectionSortVisual(vector<int> arr) {
    cout << "\n🎯 Selection Sort Visualization\n";
    cout << "Initial: "; printArray(arr);
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        cout << "Min at index " << minIdx << " (value " << arr[minIdx] << "), swap with index " << i << "\n";
        swap(arr[i], arr[minIdx]);
        cout << "After:   "; printArray(arr, i, -1);
    }
    cout << "✅ Sorted: "; printArray(arr);
}

// ===================== Binary Search Visualizer =====================

void binarySearchVisual(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    cout << "\n🔍 Binary Search for " << target << "\n";
    cout << "Array: "; printArray(arr);
    
    int lo = 0, hi = arr.size()-1, step = 1;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        cout << "\nStep " << step++ << ": lo=" << lo << " hi=" << hi << " mid=" << mid 
             << " arr[mid]=" << arr[mid] << "\n";
        
        // Visual: show search space
        cout << "       ";
        for (int i = 0; i < (int)arr.size(); i++) {
            if (i == mid) cout << "[" << setw(3) << arr[i] << "]";
            else if (i >= lo && i <= hi) cout << " " << setw(3) << arr[i] << " ";
            else cout << "  .  ";
        }
        cout << "\n";
        
        if (arr[mid] == target) {
            cout << "✅ Found " << target << " at index " << mid << "!\n";
            return;
        } else if (arr[mid] < target) {
            cout << "   " << arr[mid] << " < " << target << " → search RIGHT half\n";
            lo = mid+1;
        } else {
            cout << "   " << arr[mid] << " > " << target << " → search LEFT half\n";
            hi = mid-1;
        }
    }
    cout << "❌ " << target << " not found.\n";
}

// ===================== Stack Visualizer =====================

void stackVisual() {
    cout << "\n📚 Stack Visualizer (LIFO)\n";
    stack<int> st;
    vector<pair<string, int>> ops = {
        {"push", 10}, {"push", 20}, {"push", 30}, {"pop", 0}, {"push", 40}, {"pop", 0}, {"pop", 0}
    };
    
    for (auto& [op, val] : ops) {
        if (op == "push") {
            st.push(val);
            cout << "PUSH " << val << "  →  Stack (top→bottom): ";
        } else {
            cout << "POP  " << st.top() << "  →  Stack (top→bottom): ";
            st.pop();
        }
        // Display stack state
        stack<int> temp = st;
        vector<int> items;
        while (!temp.empty()) { items.push_back(temp.top()); temp.pop(); }
        cout << "[ ";
        for (int x : items) cout << x << " ";
        cout << "]  (size=" << st.size() << ")\n";
    }
}

// ===================== Queue Visualizer =====================

void queueVisual() {
    cout << "\n🚶 Queue Visualizer (FIFO)\n";
    queue<int> q;
    vector<pair<string, int>> ops = {
        {"enqueue", 10}, {"enqueue", 20}, {"enqueue", 30}, {"dequeue", 0}, {"enqueue", 40}, {"dequeue", 0}
    };
    
    for (auto& [op, val] : ops) {
        if (op == "enqueue") {
            q.push(val);
            cout << "ENQUEUE " << val << "  →  Queue (front→back): ";
        } else {
            cout << "DEQUEUE " << q.front() << "  →  Queue (front→back): ";
            q.pop();
        }
        queue<int> temp = q;
        cout << "[ ";
        while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); }
        cout << "]  (size=" << q.size() << ")\n";
    }
}

// ===================== BST Visualizer =====================

struct BSTNode {
    int val;
    BSTNode *left, *right;
    BSTNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

BSTNode* bstInsert(BSTNode* root, int val) {
    if (!root) return new BSTNode(val);
    if (val < root->val) root->left = bstInsert(root->left, val);
    else root->right = bstInsert(root->right, val);
    return root;
}

void printBST(BSTNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    cout << prefix << (isLeft ? "├── " : "└── ") << root->val << "\n";
    printBST(root->left,  prefix + (isLeft ? "│   " : "    "), true);
    printBST(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

void bstVisual() {
    cout << "\n🌳 BST Visualizer\n";
    BSTNode* root = nullptr;
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int v : values) {
        root = bstInsert(root, v);
        cout << "\nInserted " << v << ":\n";
        printBST(root, "", false);
    }
}

// ===================== Main Menu =====================

int main() {
    int choice;
    do {
        cout << "\n===== DSA Visualizer =====\n"
             << "1. Bubble Sort\n"
             << "2. Selection Sort\n"
             << "3. Binary Search\n"
             << "4. Stack Operations\n"
             << "5. Queue Operations\n"
             << "6. BST Operations\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice; cin.ignore();
        
        vector<int> sample = {64, 34, 25, 12, 22, 11, 90};
        switch (choice) {
            case 1: bubbleSortVisual(sample); break;
            case 2: selectionSortVisual(sample); break;
            case 3: binarySearchVisual(sample, 25); break;
            case 4: stackVisual(); break;
            case 5: queueVisual(); break;
            case 6: bstVisual(); break;
        }
    } while (choice != 0);
    return 0;
}
