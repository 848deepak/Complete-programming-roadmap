// ============================================================
// DSA | C++ → Linked Lists: Doubly Linked List
// ============================================================
// DESCRIPTION:
//   A doubly linked list (DLL) has nodes with pointers to both
//   the NEXT and PREVIOUS node. This allows O(1) insertion and
//   deletion at both ends and O(1) backward traversal.
//
// STRUCTURE:
//   NULL ← [prev|data|next] ↔ [prev|data|next] ↔ [prev|data|next] → NULL
//
// COMPILE & RUN:
//   g++ -std=c++17 09_doubly_linked_list.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   Forward:  [10] ↔ [20] ↔ [30] ↔ NULL
//   Backward: [30] ↔ [20] ↔ [10] ↔ NULL
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ============================================================
// NODE STRUCTURE
// ============================================================

struct Node {
    int   data;    // value stored in this node
    Node* next;    // pointer to NEXT node
    Node* prev;    // pointer to PREVIOUS node

    explicit Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// ============================================================
// DOUBLY LINKED LIST CLASS
// ============================================================

class DoublyLinkedList {
private:
    Node* head;   // pointer to first node
    Node* tail;   // pointer to last node (for O(1) push_back)
    int   size_;  // number of nodes

public:
    // Constructor: initialise empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

    // Destructor: free all heap-allocated nodes
    ~DoublyLinkedList() {
        Node* curr = head;
        while (curr) {
            Node* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }

    int size() const { return size_; }
    bool empty() const { return head == nullptr; }

    // -------------------------------------------------------
    // INSERT AT FRONT: O(1)
    // -------------------------------------------------------
    /**
     * Prepends a new node with value `val` at the beginning.
     * New node's next → old head; old head's prev ← new node.
     */
    void pushFront(int val) {
        Node* node = new Node(val);
        if (empty()) {
            head = tail = node;   // first node — also the tail
        } else {
            node->next  = head;   // link new node to old head
            head->prev  = node;   // back-link old head to new node
            head        = node;   // update head pointer
        }
        size_++;
    }

    // -------------------------------------------------------
    // INSERT AT BACK: O(1) — thanks to tail pointer
    // -------------------------------------------------------
    /**
     * Appends a new node with value `val` at the end.
     */
    void pushBack(int val) {
        Node* node = new Node(val);
        if (empty()) {
            head = tail = node;
        } else {
            tail->next  = node;   // link old tail to new node
            node->prev  = tail;   // back-link new node to old tail
            tail        = node;   // update tail pointer
        }
        size_++;
    }

    // -------------------------------------------------------
    // INSERT AFTER A GIVEN NODE: O(1)
    // -------------------------------------------------------
    /**
     * Inserts `val` immediately after `prevNode`.
     * If prevNode is tail, also updates tail.
     */
    void insertAfter(Node* prevNode, int val) {
        if (!prevNode) return;
        Node* node = new Node(val);
        node->next = prevNode->next;
        node->prev = prevNode;

        if (prevNode->next)
            prevNode->next->prev = node;   // update next node's back-link
        else
            tail = node;                   // prevNode was tail → update tail

        prevNode->next = node;
        size_++;
    }

    // -------------------------------------------------------
    // DELETE FROM FRONT: O(1)
    // -------------------------------------------------------
    /**
     * Removes the head node. Returns the deleted value.
     * Edge: empty list → prints warning, returns -1.
     */
    int popFront() {
        if (empty()) {
            cout << "  popFront: list is empty!\n";
            return -1;
        }
        Node* tmp  = head;
        int   val  = head->data;
        head       = head->next;

        if (head) head->prev = nullptr;   // new head has no predecessor
        else      tail = nullptr;         // list is now empty

        delete tmp;
        size_--;
        return val;
    }

    // -------------------------------------------------------
    // DELETE FROM BACK: O(1)
    // -------------------------------------------------------
    /**
     * Removes the tail node. Returns the deleted value.
     */
    int popBack() {
        if (empty()) {
            cout << "  popBack: list is empty!\n";
            return -1;
        }
        Node* tmp = tail;
        int   val = tail->data;
        tail      = tail->prev;

        if (tail) tail->next = nullptr;   // new tail points to nothing forward
        else      head = nullptr;         // list became empty

        delete tmp;
        size_--;
        return val;
    }

    // -------------------------------------------------------
    // DELETE A SPECIFIC NODE: O(1) given pointer
    // -------------------------------------------------------
    /**
     * Removes an arbitrary node by pointer.
     * No need to traverse — doubly linked allows direct re-linking.
     */
    void deleteNode(Node* node) {
        if (!node) return;

        if (node->prev) node->prev->next = node->next;   // bypass this node
        else            head             = node->next;   // was head

        if (node->next) node->next->prev = node->prev;   // update back-link
        else            tail             = node->prev;   // was tail

        delete node;
        size_--;
    }

    // -------------------------------------------------------
    // SEARCH: O(n)
    // -------------------------------------------------------
    /**
     * Finds the first node with the given value.
     * @return  Pointer to node if found, nullptr otherwise.
     */
    Node* search(int val) const {
        Node* curr = head;
        while (curr) {
            if (curr->data == val) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    // -------------------------------------------------------
    // REVERSE: O(n)
    // -------------------------------------------------------
    /**
     * Reverses the DLL in-place by swapping next and prev pointers of every node.
     */
    void reverse() {
        Node* curr = head;
        Node* tmp  = nullptr;

        // Swap next and prev for every node
        while (curr) {
            tmp        = curr->prev;   // save prev
            curr->prev = curr->next;   // prev ← next
            curr->next = tmp;          // next ← (old prev)
            curr       = curr->prev;   // move forward (using new prev = old next)
        }

        // Swap head and tail
        swap(head, tail);
    }

    // -------------------------------------------------------
    // PRINT (forward): O(n)
    // -------------------------------------------------------
    void printForward(const string& label = "") const {
        if (!label.empty()) cout << label << "\n";
        cout << "  HEAD ↔ ";
        Node* curr = head;
        while (curr) {
            cout << "[" << curr->data << "]";
            if (curr->next) cout << " ↔ ";
            curr = curr->next;
        }
        cout << " ↔ NULL  (size=" << size_ << ")\n";
    }

    // -------------------------------------------------------
    // PRINT (backward): O(n)
    // -------------------------------------------------------
    void printBackward(const string& label = "") const {
        if (!label.empty()) cout << label << "\n";
        cout << "  TAIL ↔ ";
        Node* curr = tail;
        while (curr) {
            cout << "[" << curr->data << "]";
            if (curr->prev) cout << " ↔ ";
            curr = curr->prev;
        }
        cout << " ↔ NULL\n";
    }

    // Expose head ptr for demos
    Node* getHead() const { return head; }
};

// ============================================================
// MAIN
// ============================================================
int main() {

    DoublyLinkedList dll;

    // --- Build list with pushBack & pushFront ---
    cout << "=== BUILD LIST ===" << "\n";
    dll.pushBack(20);
    dll.pushBack(30);
    dll.pushBack(40);
    dll.pushFront(10);
    dll.pushFront(5);
    dll.printForward("After pushFront(10,5) and pushBack(20,30,40):");
    dll.printBackward("Backward traversal:");

    // --- Insert after ---
    cout << "\n=== INSERT AFTER ===" << "\n";
    Node* node20 = dll.search(20);
    if (node20) dll.insertAfter(node20, 25);
    dll.printForward("After insertAfter(20, 25):");

    // --- Pop operations ---
    cout << "\n=== POP OPERATIONS ===" << "\n";
    int popped = dll.popFront();
    cout << "  popFront() → " << popped << "\n";
    dll.printForward("After popFront:");

    popped = dll.popBack();
    cout << "  popBack() → " << popped << "\n";
    dll.printForward("After popBack:");

    // --- Delete by pointer ---
    cout << "\n=== DELETE BY POINTER ===" << "\n";
    Node* node25 = dll.search(25);
    if (node25) {
        cout << "  Deleting node with value 25...\n";
        dll.deleteNode(node25);
    }
    dll.printForward("After delete(25):");

    // --- Search ---
    cout << "\n=== SEARCH ===" << "\n";
    Node* found = dll.search(30);
    cout << "  search(30): " << (found ? "found" : "not found") << "\n";
    found = dll.search(99);
    cout << "  search(99): " << (found ? "found" : "not found") << "\n";

    // --- Reverse ---
    cout << "\n=== REVERSE ===" << "\n";
    dll.printForward("Before reverse:");
    dll.reverse();
    dll.printForward("After reverse:");
    dll.printBackward("Backward after reverse:");

    // --- Edge case: empty list ---
    cout << "\n=== EDGE CASES ===" << "\n";
    DoublyLinkedList empty;
    empty.popFront();   // should print warning
    empty.popBack();    // should print warning

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   pushFront / pushBack     : O(1) — both head and tail available
//   insertAfter (by pointer) : O(1)
//   popFront / popBack       : O(1)
//   deleteNode (by pointer)  : O(1) ← key advantage over singly-LL
//   search                   : O(n)
//   reverse                  : O(n)
//   printForward / Backward  : O(n)
//
// VS SINGLY LINKED LIST:
//   DLL uses more memory (extra `prev` pointer per node)
//   DLL allows O(1) deletion from any node (with pointer)
//   DLL allows O(n) backward traversal
// ============================================================
