// ============================================================
// DSA | C++ → Linked Lists: Circular Linked List
// ============================================================
// DESCRIPTION:
//   A Circular Linked List (CLL) is a list where the last node's
//   next pointer points back to the first node, forming a circle.
//
// TYPES:
//   - Circular Singly LL : last.next = head
//   - Circular Doubly LL : last.next = head, head.prev = last
//
// USE CASES:
//   - Round-robin scheduling
//   - Circular buffers / ring buffers
//   - Multiplayer games (turns cycling through players)
//
// COMPILE & RUN:
//   g++ -std=c++17 10_circular_linked_list.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   CLL: [10] → [20] → [30] → [10] (circular)
// ============================================================

#include <iostream>
#include <vector>
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
// CIRCULAR SINGLY LINKED LIST
// ============================================================
// We maintain a `tail` pointer (instead of `head`) because:
//   - tail->next gives us head in O(1)
//   - insertAtEnd is O(1) without traversing to the end
// ------------------------------------------------------------ 

class CircularLinkedList {
private:
    Node* tail;   // last node; tail->next = head
    int   size_;

public:
    CircularLinkedList() : tail(nullptr), size_(0) {}

    ~CircularLinkedList() {
        if (!tail) return;                  // empty list
        Node* curr = tail->next;            // start from head
        Node* head = curr;
        do {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        } while (curr != head);
        tail = nullptr;
    }

    int  size()  const { return size_; }
    bool empty() const { return tail == nullptr; }

    // Access head (tail->next) in O(1)
    Node* head() const { return tail ? tail->next : nullptr; }

    // ---------------------------------------------------
    // INSERT AT FRONT: O(1)
    // ---------------------------------------------------
    /**
     * Inserts val at the beginning of the circular list.
     * The new node becomes the head; tail->next = new node.
     */
    void insertFront(int val) {
        Node* node = new Node(val);
        if (empty()) {
            node->next = node;             // points to itself
            tail = node;
        } else {
            node->next = tail->next;       // new node → old head
            tail->next = node;             // tail → new head
        }
        size_++;
    }

    // ---------------------------------------------------
    // INSERT AT BACK: O(1)
    // ---------------------------------------------------
    /**
     * Inserts val at the end. The new node becomes the tail.
     */
    void insertBack(int val) {
        Node* node = new Node(val);
        if (empty()) {
            node->next = node;             // self-loop
            tail = node;
        } else {
            node->next = tail->next;       // new node → head
            tail->next = node;             // old tail → new node
            tail       = node;             // update tail
        }
        size_++;
    }

    // ---------------------------------------------------
    // DELETE FROM FRONT: O(1)
    // ---------------------------------------------------
    /**
     * Removes the head node.
     * Edge: single-node list → list becomes empty.
     */
    int deleteFront() {
        if (empty()) { cout << "  deleteFront: empty list!\n"; return -1; }

        Node* oldHead = tail->next;
        int   val     = oldHead->data;

        if (tail == oldHead) {             // only one node
            tail = nullptr;
        } else {
            tail->next = oldHead->next;    // tail skips the old head
        }
        delete oldHead;
        size_--;
        return val;
    }

    // ---------------------------------------------------
    // DELETE FROM BACK: O(n)  — must find node before tail
    // ---------------------------------------------------
    /**
     * Removes the tail node.
     * Must traverse to find the node just before tail.
     */
    int deleteBack() {
        if (empty()) { cout << "  deleteBack: empty list!\n"; return -1; }

        int val = tail->data;

        if (tail == tail->next) {          // single node
            delete tail;
            tail = nullptr;
            size_--;
            return val;
        }

        // Find node just before tail
        Node* curr = tail->next;           // start from head
        while (curr->next != tail) curr = curr->next;

        curr->next = tail->next;           // skip tail (connect to head)
        delete tail;
        tail = curr;                       // new tail
        size_--;
        return val;
    }

    // ---------------------------------------------------
    // DELETE BY VALUE: O(n)
    // ---------------------------------------------------
    /**
     * Deletes the first node with the given value.
     * Returns true if found and deleted.
     */
    bool deleteByValue(int val) {
        if (empty()) return false;

        Node* curr = tail->next;           // start from head
        Node* prev = tail;

        do {
            if (curr->data == val) {
                if (curr == tail->next && curr == tail) {   // single node
                    delete curr;
                    tail = nullptr;
                } else {
                    prev->next = curr->next;               // bypass curr
                    if (curr == tail) tail = prev;         // deleted the tail
                    delete curr;
                }
                size_--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != tail->next);       // stop after full cycle

        return false;   // not found
    }

    // ---------------------------------------------------
    // SEARCH: O(n)
    // ---------------------------------------------------
    bool search(int val) const {
        if (empty()) return false;
        Node* curr = tail->next;           // head
        do {
            if (curr->data == val) return true;
            curr = curr->next;
        } while (curr != tail->next);
        return false;
    }

    // ---------------------------------------------------
    // PRINT: O(n)
    // ---------------------------------------------------
    void print(const string& label = "") const {
        if (!label.empty()) cout << label << "\n";
        if (empty()) { cout << "  [empty list]\n"; return; }

        Node* curr = tail->next;           // start from head
        cout << "  ";
        do {
            cout << "[" << curr->data << "]";
            curr = curr->next;
            if (curr != tail->next) cout << " → ";
        } while (curr != tail->next);
        cout << " → [HEAD] (circular, size=" << size_ << ")\n";
    }

    // ---------------------------------------------------
    // SPLIT INTO TWO HALVES: O(n) — useful for merge sort on CLL
    // ---------------------------------------------------
    /**
     * Splits this CLL into two halves: first and second.
     * Uses Floyd's slow-fast pointer to find midpoint.
     */
    pair<CircularLinkedList, CircularLinkedList> splitHalves() const {
        CircularLinkedList first, second;
        if (empty()) return {first, second};

        Node* slow = tail->next;   // head
        Node* fast = tail->next;   // head

        // Move fast twice, slow once per step to find midpoint
        while (fast->next != tail->next && fast->next->next != tail->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // slow is at midpoint; copy first half
        Node* curr = tail->next;   // head
        while (curr != slow->next) {
            first.insertBack(curr->data);
            curr = curr->next;
        }
        first.insertBack(slow->data);

        // copy second half
        curr = slow->next;
        while (curr != tail->next) {
            second.insertBack(curr->data);
            curr = curr->next;
        }

        return {first, second};
    }
};

// ============================================================
// JOSEPHUS PROBLEM (classic CLL application)
// ============================================================
// n people stand in a circle; every k-th person is eliminated.
// Find the position of the last survivor.
//
// Time: O(n*k)  |  Space: O(n)
// ------------------------------------------------------------ 

int josephus(int n, int k) {
    CircularLinkedList cll;
    for (int i = 1; i <= n; i++) cll.insertBack(i);   // positions 1..n

    Node* curr = cll.head();   // start from person 1

    cout << "Elimination order (n=" << n << ", k=" << k << "): ";
    while (cll.size() > 1) {
        // Advance k-1 steps (we're already on 1st person)
        for (int i = 1; i < k; i++) curr = curr->next;

        cout << curr->data << " ";
        Node* toDelete = curr;
        curr = curr->next;              // move past before deleting
        cll.deleteByValue(toDelete->data);
    }
    cout << "\nSurvivor: " << cll.head()->data << "\n";
    return cll.head()->data;
}

// ============================================================
// MAIN
// ============================================================
int main() {

    CircularLinkedList cll;

    // --- Build list ---
    cout << "=== BUILD CLL ===" << "\n";
    cll.insertBack(10);
    cll.insertBack(20);
    cll.insertBack(30);
    cll.insertFront(5);
    cll.print("After insertBack(10,20,30) and insertFront(5):");

    // --- Delete operations ---
    cout << "\n=== DELETE OPERATIONS ===" << "\n";
    int del = cll.deleteFront();
    cout << "  deleteFront() → " << del << "\n";
    cll.print("After deleteFront:");

    del = cll.deleteBack();
    cout << "  deleteBack() → " << del << "\n";
    cll.print("After deleteBack:");

    bool ok = cll.deleteByValue(20);
    cout << "  deleteByValue(20) → " << (ok ? "deleted" : "not found") << "\n";
    cll.print("After deleteByValue(20):");

    // --- Search ---
    cout << "\n=== SEARCH ===" << "\n";
    cout << "  search(10): " << (cll.search(10) ? "found" : "not found") << "\n";
    cout << "  search(99): " << (cll.search(99) ? "found" : "not found") << "\n";

    // --- Split halves ---
    cout << "\n=== SPLIT INTO HALVES ===" << "\n";
    CircularLinkedList cll2;
    for (int v : {1,2,3,4,5,6}) cll2.insertBack(v);
    cll2.print("Original:");
    auto [h1, h2] = cll2.splitHalves();
    h1.print("First half:");
    h2.print("Second half:");

    // --- Edge: empty list ---
    cout << "\n=== EDGE: EMPTY LIST ===" << "\n";
    CircularLinkedList empty;
    empty.print("Empty CLL:");
    empty.deleteFront();
    empty.deleteBack();

    // --- Josephus Problem ---
    cout << "\n=== JOSEPHUS PROBLEM ===" << "\n";
    josephus(7, 3);   // 7 people, every 3rd eliminated: survivor = 4

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   insertFront   : O(1)
//   insertBack    : O(1) — tail pointer makes this O(1)
//   deleteFront   : O(1)
//   deleteBack    : O(n) — must find node before tail
//   deleteByValue : O(n)
//   search        : O(n)
//   splitHalves   : O(n)
//   josephus(n,k) : O(n*k)
// ============================================================
