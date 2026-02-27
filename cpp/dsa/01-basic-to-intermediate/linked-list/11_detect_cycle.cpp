// ============================================================
// DSA | C++ → Linked Lists: Detect Cycle
// ============================================================
// DESCRIPTION:
//   Algorithms to detect and handle cycles in a singly linked list.
//
// ALGORITHMS COVERED:
//   1. Floyd's Cycle Detection (Tortoise & Hare) — O(n) time, O(1) space
//   2. Find cycle start node — O(n) time, O(1) space
//   3. Find cycle length — O(n) time, O(1) space
//   4. Remove the cycle — O(n) time, O(1) space
//   5. Hash set method (simpler but O(n) space)
//
// COMPILE & RUN:
//   g++ -std=c++17 11_detect_cycle.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <unordered_set>
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
// UTILITY: Build a list from values
// ============================================================
Node* buildList(const int vals[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(vals[0]);
    Node* curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = new Node(vals[i]);
        curr = curr->next;
    }
    return head;
}

// ============================================================
// UTILITY: Create a cycle at position `pos` (0-indexed)
// Returns the tail node (useful for removing cycle later)
// ============================================================
Node* createCycle(Node* head, int pos) {
    if (!head || pos < 0) return nullptr;
    Node* tail = head;
    Node* cycleEntry = nullptr;
    int idx = 0;

    while (tail->next) {
        if (idx == pos) cycleEntry = tail;
        idx++;
        tail = tail->next;
    }
    if (idx == pos) cycleEntry = tail;   // last node is the entry

    tail->next = cycleEntry;             // create the cycle
    return tail;                         // return tail for later removal
}

// ============================================================
// SECTION 1: FLOYD'S CYCLE DETECTION (Tortoise & Hare)
// ============================================================
// Two pointers: slow moves 1 step, fast moves 2 steps.
// If there IS a cycle, fast will eventually lap slow and they meet.
// If no cycle, fast will reach nullptr.
//
// Time:  O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Returns true if the linked list has a cycle.
 *
 * @param head  First node of the list
 */
bool hasCycle(Node* head) {
    Node* slow = head;   // tortoise: moves 1 step at a time
    Node* fast = head;   // hare    : moves 2 steps at a time

    while (fast && fast->next) {
        slow = slow->next;          // 1 step
        fast = fast->next->next;    // 2 steps

        if (slow == fast) return true;   // pointers met → cycle exists
    }

    return false;   // fast reached nullptr → no cycle
}

// ============================================================
// SECTION 2: FIND THE START OF THE CYCLE
// ============================================================
// After meeting point is found (Floyd's step 1):
//   - Reset one pointer to head
//   - Move both one step at a time
//   - They meet at the CYCLE ENTRY NODE
//
// Proof (mathematical):
//   Let F = distance from head to cycle entry
//       L = length of cycle
//       k = distance from cycle entry to meeting point
//   At meeting: slow traveled F+k, fast traveled F+k+mL (some m)
//   2(F+k) = F+k+mL  →  F = mL - k = (m-1)L + (L-k)
//   This means: distance from head to entry = distance from
//   meeting point to entry (going around the cycle).
//
// Time: O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Returns the node where the cycle begins, or nullptr if no cycle.
 */
Node* findCycleStart(Node* head) {
    Node* slow = head;
    Node* fast = head;

    // Phase 1: Detect cycle
    bool cycleFound = false;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { cycleFound = true; break; }
    }

    if (!cycleFound) return nullptr;

    // Phase 2: Find cycle start
    slow = head;            // reset slow to head
    // fast stays at meeting point
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;  // now both move 1 step
    }

    return slow;   // meeting point is the cycle start
}

// ============================================================
// SECTION 3: FIND CYCLE LENGTH
// ============================================================
// Once we have the meeting point, keep fast moving 1 step
// and count until it returns to the meeting point.
//
// Time: O(L) where L = cycle length  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Returns the length of the cycle, or 0 if no cycle.
 */
int cycleLength(Node* head) {
    Node* slow = head;
    Node* fast = head;
    int   len  = 0;

    // Detect
    bool found = false;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { found = true; break; }
    }
    if (!found) return 0;

    // Count cycle length from meeting point
    Node* curr = fast;
    do {
        curr = curr->next;
        len++;
    } while (curr != fast);

    return len;
}

// ============================================================
// SECTION 4: REMOVE THE CYCLE
// ============================================================
// Find the node JUST BEFORE the cycle start (the tail).
// Set tail->next = nullptr.
//
// Time: O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Removes the cycle from the linked list (modifies in-place).
 * Does nothing if no cycle exists.
 */
void removeCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    bool  found = false;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { found = true; break; }
    }
    if (!found) return;

    // Find cycle start (phase 2)
    slow = head;
    // Edge: cycle starts at head
    if (slow == fast) {
        // Find the node just before meeting point (tail of cycle)
        while (fast->next != slow) fast = fast->next;
        fast->next = nullptr;
        return;
    }
    while (slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    fast->next = nullptr;   // break the cycle
}

// ============================================================
// SECTION 5: HASH SET METHOD (simpler, O(n) space)
// ============================================================

/**
 * Detects and returns the cycle start using a hash set.
 * Stores visited node addresses.
 *
 * Time: O(n)  |  Space: O(n)
 */
Node* detectCycleHashSet(Node* head) {
    unordered_set<Node*> visited;
    Node* curr = head;
    while (curr) {
        if (visited.count(curr)) return curr;   // first revisit = cycle start
        visited.insert(curr);
        curr = curr->next;
    }
    return nullptr;
}

// ============================================================
// UTILITY: Print list (stops if no cycle or max 20 nodes)
// ============================================================
void printList(Node* head, const string& label = "") {
    if (!label.empty()) cout << label << "\n";
    cout << "  ";
    int count = 0;
    while (head && count < 15) {
        cout << head->data;
        if (head->next) cout << " → ";
        head = head->next;
        count++;
    }
    if (count == 15) cout << "... (cycle)";
    cout << "\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- No cycle list ---
    cout << "=== LIST WITHOUT CYCLE ===" << "\n";
    int vals[] = {1, 2, 3, 4, 5};
    Node* head = buildList(vals, 5);
    printList(head, "List:");
    cout << "  hasCycle: " << (hasCycle(head) ? "YES" : "NO") << "\n";
    cout << "  findCycleStart: " << (findCycleStart(head) ? "found" : "nullptr (no cycle)") << "\n";
    cout << "  cycleLength: " << cycleLength(head) << "\n";

    // --- Cycle at position 1 (node with value 2) ---
    cout << "\n=== LIST WITH CYCLE (entry at pos=1, value=2) ===" << "\n";
    Node* head2 = buildList(vals, 5);
    createCycle(head2, 1);   // tail->next = node at index 1

    cout << "  hasCycle (Floyd): " << (hasCycle(head2) ? "YES" : "NO") << "\n";
    Node* entry = findCycleStart(head2);
    cout << "  cycleStart value: " << (entry ? to_string(entry->data) : "none") << "\n";
    cout << "  cycleLength: " << cycleLength(head2) << "\n";

    Node* entry2 = detectCycleHashSet(head2);
    cout << "  cycleStart (hash): " << (entry2 ? to_string(entry2->data) : "none") << "\n";

    removeCycle(head2);
    cout << "  After removeCycle:\n";
    printList(head2, "  List (no cycle):");
    cout << "  hasCycle after removal: " << (hasCycle(head2) ? "YES" : "NO") << "\n";

    // --- Cycle at position 0 (starts from head) ---
    cout << "\n=== LIST WITH CYCLE AT HEAD (pos=0) ===" << "\n";
    Node* head3 = buildList(vals, 5);
    createCycle(head3, 0);
    cout << "  hasCycle: " << (hasCycle(head3) ? "YES" : "NO") << "\n";
    Node* e3 = findCycleStart(head3);
    cout << "  cycleStart value: " << (e3 ? to_string(e3->data) : "none") << "\n";
    cout << "  cycleLength: " << cycleLength(head3) << "\n";
    removeCycle(head3);
    cout << "  hasCycle after removal: " << (hasCycle(head3) ? "YES" : "NO") << "\n";

    // --- Single node no cycle ---
    cout << "\n=== SINGLE NODE (no cycle) ===" << "\n";
    Node* single = new Node(42);
    cout << "  hasCycle: " << (hasCycle(single) ? "YES" : "NO") << "\n";
    delete single;

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   hasCycle           : O(n) time, O(1) space  ← Floyd's
//   findCycleStart     : O(n) time, O(1) space
//   cycleLength        : O(n) time, O(1) space
//   removeCycle        : O(n) time, O(1) space
//   detectCycleHashSet : O(n) time, O(n) space  ← simpler but uses memory
//
// WHY FLOYD'S WORKS:
//   fast moves 2× speed of slow → eventually laps slow in cycle
//   Phase 2 math guarantees they meet at cycle entry node
// ============================================================
