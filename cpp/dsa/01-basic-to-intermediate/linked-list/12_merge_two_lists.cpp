// ============================================================
// DSA | C++ → Linked Lists: Merge Two Sorted Lists
// ============================================================
// DESCRIPTION:
//   Merge two sorted singly linked lists into a single sorted list.
//   Also covers:
//   - Merge K sorted lists (using min-heap)
//   - Merge sort on a linked list
//
// COMPILE & RUN:
//   g++ -std=c++17 12_merge_two_lists.cpp -o out && ./out
//
// SAMPLE INPUT:  L1 = [1→3→5], L2 = [2→4→6]
// SAMPLE OUTPUT: Merged: [1→2→3→4→5→6]
//
// COMPLEXITY:
//   Merge two lists  : O(m+n) time, O(1) space
//   Merge K lists    : O(N log K) where N = total nodes
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================================
// NODE STRUCTURE
// ============================================================
struct Node {
    int   data;
    Node* next;
    explicit Node(int val) : data(val), next(nullptr) {}
};

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

/** Build a linked list from a vector. Returns head. */
Node* buildList(const vector<int>& vals) {
    if (vals.empty()) return nullptr;
    Node* head = new Node(vals[0]);
    Node* curr = head;
    for (int i = 1; i < (int)vals.size(); i++) {
        curr->next = new Node(vals[i]);
        curr       = curr->next;
    }
    return head;
}

/** Print a linked list. */
void printList(Node* head, const string& label = "") {
    if (!label.empty()) cout << "  " << label << ": ";
    else                 cout << "  ";
    while (head) {
        cout << head->data;
        if (head->next) cout << " → ";
        head = head->next;
    }
    cout << " → NULL\n";
}

/** Free all nodes of a list. */
void freeList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ============================================================
// SECTION 1: MERGE TWO SORTED LISTS — ITERATIVE
// ============================================================
// Use a dummy head node to simplify edge cases.
// Compare the two heads; attach the smaller one; advance it.
//
// Time: O(m + n)  |  Space: O(1) — no new nodes, re-links existing
// ------------------------------------------------------------ 

/**
 * Merges two sorted linked lists into one sorted list.
 * Modifies in-place (no new nodes allocated).
 *
 * @param l1  Head of first sorted list
 * @param l2  Head of second sorted list
 * @return    Head of the merged sorted list
 */
Node* mergeTwoSorted(Node* l1, Node* l2) {
    Node  dummy(0);          // sentinel head (avoids special-casing empty result)
    Node* tail = &dummy;     // tracks the end of the merged list

    while (l1 && l2) {
        if (l1->data <= l2->data) {
            tail->next = l1;    // attach smaller node
            l1         = l1->next;
        } else {
            tail->next = l2;
            l2         = l2->next;
        }
        tail = tail->next;      // advance merged tail
    }

    // Attach the remaining portion (at most one list has nodes left)
    tail->next = l1 ? l1 : l2;

    return dummy.next;          // real head (skip sentinel)
}

// ============================================================
// SECTION 2: MERGE TWO SORTED LISTS — RECURSIVE
// ============================================================
// Elegant recursive approach. Each call attaches one node.
//
// Time: O(m + n)  |  Space: O(m + n) — call stack depth
// ------------------------------------------------------------ 

/**
 * Recursive merge of two sorted lists.
 */
Node* mergeTwoSortedRecursive(Node* l1, Node* l2) {
    if (!l1) return l2;   // base: l1 exhausted
    if (!l2) return l1;   // base: l2 exhausted

    if (l1->data <= l2->data) {
        l1->next = mergeTwoSortedRecursive(l1->next, l2);  // l1 is smaller; recurse on l1->next
        return l1;
    } else {
        l2->next = mergeTwoSortedRecursive(l1, l2->next);  // l2 is smaller; recurse on l2->next
        return l2;
    }
}

// ============================================================
// SECTION 3: MERGE K SORTED LISTS (using min-heap)
// ============================================================
// Add the head of each list to a min-heap.
// Repeatedly extract the minimum node, append to result,
// and push its successor into the heap.
//
// Time: O(N log K) where N = total nodes, K = number of lists
// Space: O(K) — heap stores at most K elements at a time
// ------------------------------------------------------------ 

/**
 * Merges K sorted linked lists.
 *
 * @param lists  Vector of head pointers for each sorted list
 * @return       Head of merged sorted list
 */
Node* mergeKLists(vector<Node*>& lists) {
    // Min-heap: compare by node value
    auto cmp = [](Node* a, Node* b) { return a->data > b->data; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> minHeap(cmp);

    // Push the head of each non-empty list
    for (Node* head : lists) {
        if (head) minHeap.push(head);
    }

    Node  dummy(0);
    Node* tail = &dummy;

    while (!minHeap.empty()) {
        Node* smallest = minHeap.top();
        minHeap.pop();

        tail->next = smallest;          // attach smallest node
        tail       = tail->next;

        if (smallest->next)             // push successor into heap
            minHeap.push(smallest->next);
    }

    return dummy.next;
}

// ============================================================
// SECTION 4: MERGE SORT ON LINKED LIST
// ============================================================
// Split the list into halves (using slow/fast pointers),
// recursively sort each half, then merge.
//
// Time: O(n log n)  |  Space: O(log n) recursive stack
// ------------------------------------------------------------ 

/** Find the middle node (slow/fast pointer). */
Node* findMid(Node* head) {
    Node* slow = head;
    Node* fast = head->next;    // start fast one ahead so we get left half
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;   // slow is the last node of left half
}

/**
 * Merge sort on a linked list. Sorts in-place.
 *
 * @param head  Head of the list to sort
 * @return      New head after sorting
 */
Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;   // base: 0 or 1 node

    // Split
    Node* mid   = findMid(head);
    Node* right = mid->next;
    mid->next   = nullptr;                   // sever the two halves

    // Recurse
    Node* leftSorted  = mergeSort(head);
    Node* rightSorted = mergeSort(right);

    // Merge the two sorted halves
    return mergeTwoSorted(leftSorted, rightSorted);
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Merge two sorted lists (iterative) ---
    cout << "=== MERGE TWO SORTED LISTS (iterative) ===" << "\n";
    Node* l1 = buildList({1, 3, 5, 7, 9});
    Node* l2 = buildList({2, 4, 6, 8, 10});
    printList(l1, "L1");
    printList(l2, "L2");
    Node* merged = mergeTwoSorted(l1, l2);
    printList(merged, "Merged");

    // --- Merge two sorted lists (recursive) ---
    cout << "\n=== MERGE TWO SORTED LISTS (recursive) ===" << "\n";
    Node* l3 = buildList({1, 4, 7});
    Node* l4 = buildList({2, 3, 5, 8});
    printList(l3, "L3");
    printList(l4, "L4");
    Node* merged2 = mergeTwoSortedRecursive(l3, l4);
    printList(merged2, "Merged");

    // --- Merge one list with nullptr ---
    cout << "\n=== EDGE: MERGE WITH EMPTY LIST ===" << "\n";
    Node* l5 = buildList({5, 10, 15});
    Node* merged3 = mergeTwoSorted(l5, nullptr);
    printList(merged3, "Merged with NULL");
    Node* merged4 = mergeTwoSorted(nullptr, nullptr);
    cout << "  Merge NULL+NULL: " << (merged4 == nullptr ? "nullptr (correct)" : "error") << "\n";

    // --- Merge K sorted lists ---
    cout << "\n=== MERGE K SORTED LISTS ===" << "\n";
    vector<Node*> lists = {
        buildList({1, 4, 7}),
        buildList({2, 5, 8}),
        buildList({3, 6, 9}),
        buildList({0, 10})
    };
    for (int i = 0; i < (int)lists.size(); i++)
        printList(lists[i], "L" + to_string(i));
    Node* mergedK = mergeKLists(lists);
    printList(mergedK, "Merged K");

    // --- Merge Sort on linked list ---
    cout << "\n=== MERGE SORT ON LINKED LIST ===" << "\n";
    Node* unsorted = buildList({5, 1, 8, 3, 9, 2, 7, 4, 6});
    printList(unsorted, "Before sort");
    Node* sorted = mergeSort(unsorted);
    printList(sorted, "After mergeSort");

    // --- Single element merge sort ---
    cout << "\n=== EDGE: SINGLE ELEMENT MERGE SORT ===" << "\n";
    Node* single = new Node(42);
    Node* sortedSingle = mergeSort(single);
    printList(sortedSingle, "Single element sorted");

    // Free memory
    freeList(merged);
    freeList(merged2);
    freeList(merged3);
    freeList(mergedK);
    freeList(sorted);
    freeList(sortedSingle);

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   mergeTwoSorted          : O(m+n) time, O(1) space (iterative)
//   mergeTwoSortedRecursive : O(m+n) time, O(m+n) space (stack depth)
//   mergeKLists             : O(N log K) time, O(K) space (heap)
//   mergeSort (LL)          : O(n log n) time, O(log n) space (stack)
//
// COMPARISON TABLE:
//   Method        | Time      | Space     | Use When
//   Iterative     | O(m+n)    | O(1)      | Production code (safe)
//   Recursive     | O(m+n)    | O(m+n)    | Clean code, small lists
//   Merge Sort    | O(n logn) | O(log n)  | Sorting an entire LL
//   K list heap   | O(N logK) | O(K)      | Multiple sorted streams
// ============================================================
