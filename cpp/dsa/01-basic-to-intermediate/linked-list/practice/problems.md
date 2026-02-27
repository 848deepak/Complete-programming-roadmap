# 🔗 Linked List — Practice Problems

> **Topic:** Linked List | **Level:** Easy → Hard | **Focus:** Interview-Ready Patterns
>
> All solutions include **C++ and Java** implementations. Study the pointer manipulation patterns carefully — they form the foundation of most linked list interview questions.

---

## Table of Contents

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Reverse a Linked List](#1-reverse-a-linked-list) | 🟢 Easy | Iterative Pointer |
| 2 | [Find Middle of Linked List](#2-find-middle-of-linked-list) | 🟢 Easy | Fast & Slow Pointer |
| 3 | [Detect Cycle in Linked List](#3-detect-cycle-in-linked-list) | 🟢 Easy | Floyd's Algorithm |
| 4 | [Merge Two Sorted Lists](#4-merge-two-sorted-lists) | 🟢 Easy | Two Pointer Merge |
| 5 | [Remove Nth Node from End](#5-remove-nth-node-from-end) | 🟢 Easy | Two Pointer Gap |
| 6 | [Add Two Numbers as Linked Lists](#6-add-two-numbers-as-linked-lists) | 🟡 Medium | Carry Propagation |
| 7 | [Find Start of Cycle](#7-find-start-of-cycle) | 🟡 Medium | Floyd's Extended |
| 8 | [Flatten a Multilevel Linked List](#8-flatten-a-multilevel-linked-list) | 🟡 Medium | DFS / Recursion |
| 9 | [Reorder List (L0→Ln→L1→Ln-1...)](#9-reorder-list) | 🟡 Medium | Find Mid + Reverse + Merge |
| 10 | [Copy List with Random Pointer](#10-copy-list-with-random-pointer) | 🟡 Medium | Hash Map Cloning |
| 11 | [Merge k Sorted Linked Lists](#11-merge-k-sorted-linked-lists) | 🔴 Hard | Min Heap |
| 12 | [Reverse Nodes in k-Group](#12-reverse-nodes-in-k-group) | 🔴 Hard | Group Reversal |
| 13 | [LRU Cache Implementation](#13-lru-cache-implementation) | 🔴 Hard | DLL + Hash Map |

---

## Node Structure

```cpp
// C++
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

```java
// Java
class ListNode {
    int val;
    ListNode next;
    ListNode(int x) { val = x; }
}
```

---

## 🟢 EASY PROBLEMS

---

### 1. Reverse a Linked List

#### Problem Statement
Reverse a singly linked list **in-place** and return the new head.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5 → null
Output: 5 → 4 → 3 → 2 → 1 → null
```

#### 🌍 Real-World Relevance
Undo stacks, reversing command histories, parsing expressions right-to-left. The iterative reversal pattern is a mandatory pre-requisite for complex problems like "Reverse in k-Groups" and "Reorder List".

#### 💡 Approach
Use three pointers: `prev = null`, `curr = head`, `next`. At each step:
1. Save `next = curr->next`
2. Point `curr->next = prev`
3. Move `prev = curr`, `curr = next`

#### ⚠️ Edge Cases
- Empty list → return null
- Single node → return itself
- Two-node list

#### ✅ C++ Solution
```cpp
#include <iostream>
using namespace std;

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr) {
        ListNode* nextNode = curr->next;  // Save next
        curr->next = prev;                 // Reverse link
        prev = curr;                       // Advance prev
        curr = nextNode;                   // Advance curr
    }
    return prev;  // prev is the new head
}

// Helper: print list
void printList(ListNode* head) {
    while (head) { cout << head->val; if (head->next) cout << " → "; head = head->next; }
    cout << " → null\n";
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    head = reverseList(head);
    printList(head);  // 5 → 4 → 3 → 2 → 1 → null
    return 0;
}
```

#### ✅ Java Solution
```java
public class ReverseLinkedList {
    static class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }

    public static ListNode reverseList(ListNode head) {
        ListNode prev = null, curr = head;
        while (curr != null) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    public static void main(String[] args) {
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        ListNode rev = reverseList(head);
        while (rev != null) { System.out.print(rev.val + " "); rev = rev.next; }
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 2. Find Middle of Linked List

#### Problem Statement
Find the **middle node** of a linked list. If there are two middle nodes, return the **second** one.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5
Output: Node with value 3

Input:  1 → 2 → 3 → 4
Output: Node with value 3  (second middle)
```

#### 🌍 Real-World Relevance
Used in merge sort on linked lists (split at midpoint). Finding the median in a stream. Foundation of many hard problems (Palindrome Check on list, Reorder List).

#### 💡 Approach — Fast & Slow Pointer
- `slow` moves 1 step, `fast` moves 2 steps.
- When `fast` reaches the end, `slow` is at the middle.

#### ⚠️ Edge Cases
- Single node → return itself
- Two nodes → return second node
- Even vs odd length lists

#### ✅ C++ Solution
```cpp
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;  // slow is at middle
}
```

#### ✅ Java Solution
```java
public static ListNode middleNode(ListNode head) {
    ListNode slow = head, fast = head;
    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
    }
    return slow;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 3. Detect Cycle in Linked List

#### Problem Statement
Given a linked list, determine if it has a cycle. A cycle exists if a node's `next` pointer points to a previously visited node.

**Example:**
```
Input:  3 → 2 → 0 → -4 → (back to 2)
Output: true
```

#### 🌍 Real-World Relevance
Detecting infinite loops in process scheduling graphs, circular dependency detection in build systems, deadlock detection.

#### 💡 Approach — Floyd's Cycle Detection
Use fast & slow pointers. If they ever **meet**, a cycle exists. If `fast` reaches null, no cycle.

#### ⚠️ Edge Cases
- Empty list → false
- Single node with no cycle → false
- Single node pointing to itself → true

#### ✅ C++ Solution
```cpp
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;  // They met inside the cycle
    }
    return false;
}
```

#### ✅ Java Solution
```java
public static boolean hasCycle(ListNode head) {
    ListNode slow = head, fast = head;
    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow == fast) return true;
    }
    return false;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 4. Merge Two Sorted Lists

#### Problem Statement
Merge two sorted linked lists and return the merged list (also sorted).

**Example:**
```
Input:  1 → 2 → 4    and    1 → 3 → 4
Output: 1 → 1 → 2 → 3 → 4 → 4
```

#### 🌍 Real-World Relevance
Merging sorted result sets from two database queries, merging log streams ordered by timestamp, merge step of merge sort.

#### 💡 Approach
Use a **dummy head** node to simplify edge cases. Compare heads of both lists, attach smaller one, advance that pointer.

#### ⚠️ Edge Cases
- One or both lists empty
- Lists of very different lengths → append remaining portion

#### ✅ C++ Solution
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);       // Dummy head simplifies edge cases
    ListNode* curr = &dummy;

    while (l1 && l2) {
        if (l1->val <= l2->val) { curr->next = l1; l1 = l1->next; }
        else                    { curr->next = l2; l2 = l2->next; }
        curr = curr->next;
    }
    curr->next = l1 ? l1 : l2;  // Attach remaining portion
    return dummy.next;
}
```

#### ✅ Java Solution
```java
public static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    ListNode dummy = new ListNode(0);
    ListNode curr = dummy;
    while (l1 != null && l2 != null) {
        if (l1.val <= l2.val) { curr.next = l1; l1 = l1.next; }
        else                  { curr.next = l2; l2 = l2.next; }
        curr = curr.next;
    }
    curr.next = (l1 != null) ? l1 : l2;
    return dummy.next;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(m + n) | O(1) |

---

### 5. Remove Nth Node from End

#### Problem Statement
Given a linked list, remove the **nth node from the end** in a single pass and return the head.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5,  n = 2
Output: 1 → 2 → 3 → 5
```

#### 🌍 Real-World Relevance
Rolling window deletion in real-time data streams. Efficient removal without knowing the list length upfront.

#### 💡 Approach — Two Pointer Gap
- Use **dummy head** to handle edge case (removing head).
- Advance `fast` pointer by `n+1` steps ahead of `slow`.
- Move both until `fast` reaches null.
- `slow->next` is the target node to remove.

#### ⚠️ Edge Cases
- n equals the list length → remove the head
- Single node list, n=1

#### ✅ C++ Solution
```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    // Move fast n+1 steps ahead
    for (int i = 0; i <= n; i++) fast = fast->next;

    // Move both until fast hits end
    while (fast) { slow = slow->next; fast = fast->next; }

    // Remove node
    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;
    return dummy.next;
}
```

#### ✅ Java Solution
```java
public static ListNode removeNthFromEnd(ListNode head, int n) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;
    ListNode fast = dummy, slow = dummy;
    for (int i = 0; i <= n; i++) fast = fast.next;
    while (fast != null) { slow = slow.next; fast = fast.next; }
    slow.next = slow.next.next;
    return dummy.next;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) single pass | O(1) |

---

## 🟡 MEDIUM PROBLEMS

---

### 6. Add Two Numbers as Linked Lists

#### Problem Statement
Two non-empty linked lists represent two non-negative integers (digits stored in **reverse order**). Add the two numbers and return the result as a linked list.

**Example:**
```
Input:  (2 → 4 → 3) + (5 → 6 → 4)    = 342 + 465
Output: 7 → 0 → 8                       = 807
```

#### 🌍 Real-World Relevance
Arbitrary-precision arithmetic (BigInteger implementation). Used in cryptography libraries, scientific computing. Models exactly how long addition works by hand, digit by digit.

#### 💡 Approach
Traverse both lists simultaneously, add digits + carry. Create new node for each digit of the result. Handle the final carry after the loop.

#### ⚠️ Edge Cases
- Lists of different lengths
- Result has more digits than both inputs (carry at the end): `5 + 5 = 10`
- Both numbers are 0

#### ✅ C++ Solution
```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }

        carry = sum / 10;
        curr->next = new ListNode(sum % 10);
        curr = curr->next;
    }
    return dummy.next;
}
```

#### ✅ Java Solution
```java
public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    ListNode dummy = new ListNode(0);
    ListNode curr = dummy;
    int carry = 0;

    while (l1 != null || l2 != null || carry != 0) {
        int sum = carry;
        if (l1 != null) { sum += l1.val; l1 = l1.next; }
        if (l2 != null) { sum += l2.val; l2 = l2.next; }
        carry = sum / 10;
        curr.next = new ListNode(sum % 10);
        curr = curr.next;
    }
    return dummy.next;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(max(m, n)) | O(max(m, n)) for result |

---

### 7. Find Start of Cycle

#### Problem Statement
If a linked list has a cycle, return the **node where the cycle begins**. Return null if no cycle.

**Example:**
```
Input:  3 → 2 → 0 → -4 → (back to 2)
Output: Node with value 2
```

#### 🌍 Real-World Relevance
Debugging infinite loops in process graphs. Finding the entry point of circular dependencies. Used in compiler analysis.

#### 💡 Approach — Floyd's Extended Algorithm
1. Use fast & slow pointers to detect meeting point inside the cycle.
2. Reset one pointer to `head`.
3. Move both pointers one step at a time — they will meet at the **cycle start**.

**Mathematical Proof:** If the meeting point is at distance `k` from cycle start, and cycle start is at distance `d` from head, then `d = cycle_length - k`. Moving one pointer from head and one from meeting point will bring them together at the cycle entry.

#### ⚠️ Edge Cases
- No cycle → return null
- Cycle at the very head (pos = 0)

#### ✅ C++ Solution
```cpp
ListNode* detectCycleStart(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // Phase 1: Detect meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Phase 2: Find cycle start
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;  // Cycle entry
        }
    }
    return nullptr;  // No cycle
}
```

#### ✅ Java Solution
```java
public static ListNode detectCycleStart(ListNode head) {
    ListNode slow = head, fast = head;
    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) { slow = slow.next; fast = fast.next; }
            return slow;
        }
    }
    return null;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) |

---

### 8. Flatten a Multilevel Linked List

#### Problem Statement
A doubly linked list where each node has a `child` pointer that may point to another doubly linked list. Flatten all levels into a single-level list. Child lists come after their parent node.

**Example:**
```
1 - 2 - 3 - 4 - 5 - 6 - null
        |
        7 - 8 - 9 - 10 - null
            |
            11 - 12 - null

Output: 1-2-3-7-8-11-12-9-10-4-5-6-null
```

#### 🌍 Real-World Relevance
Flattening nested menus / hierarchical UI components, processing nested JSON/XML structures, flattening directory trees.

#### 💡 Approach
At each node, if it has a child:
1. Find the tail of the child list.
2. Connect: `node → child_list → next_of_node`.

#### ⚠️ Edge Cases
- No child nodes → return as-is
- Child at the last node (next is null)
- Multiple levels of nesting

#### ✅ C++ Solution
```cpp
struct Node {
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

Node* flatten(Node* head) {
    Node* curr = head;
    while (curr) {
        if (curr->child) {
            Node* child = curr->child;
            Node* nextNode = curr->next;

            // Find tail of child list
            Node* tail = child;
            while (tail->next) tail = tail->next;

            // Connect current to child
            curr->next = child;
            child->prev = curr;
            curr->child = nullptr;

            // Connect child tail to next
            tail->next = nextNode;
            if (nextNode) nextNode->prev = tail;
        }
        curr = curr->next;
    }
    return head;
}
```

#### ✅ Java Solution
```java
class Node {
    int val; Node prev, next, child;
}

public static Node flatten(Node head) {
    Node curr = head;
    while (curr != null) {
        if (curr.child != null) {
            Node child = curr.child;
            Node nextNode = curr.next;
            Node tail = child;
            while (tail.next != null) tail = tail.next;

            curr.next = child;   child.prev = curr;   curr.child = null;
            tail.next = nextNode; if (nextNode != null) nextNode.prev = tail;
        }
        curr = curr.next;
    }
    return head;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) — each node visited once | O(1) |

---

### 9. Reorder List

#### Problem Statement
Given a linked list `L0→L1→…→Ln`, reorder it to `L0→Ln→L1→Ln-1→L2→Ln-2→…` **in-place**.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5
Output: 1 → 5 → 2 → 4 → 3
```

#### 🌍 Real-World Relevance
Interleaving two data streams, zipping two queues in alternating fashion. Combines three fundamental linked list operations into one problem.

#### 💡 Approach — 3 Steps
1. **Find middle** using fast & slow pointer.
2. **Reverse** second half.
3. **Merge** two halves alternately.

#### ⚠️ Edge Cases
- Less than 3 nodes → trivial
- Even vs odd length

#### ✅ C++ Solution
```cpp
void reorderList(ListNode* head) {
    if (!head || !head->next) return;

    // Step 1: Find middle
    ListNode* slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse second half
    ListNode* prev = nullptr, *curr = slow->next;
    slow->next = nullptr;  // Split the list
    while (curr) {
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }

    // Step 3: Merge two halves
    ListNode* first = head, *second = prev;
    while (second) {
        ListNode* tmp1 = first->next;
        ListNode* tmp2 = second->next;
        first->next = second;
        second->next = tmp1;
        first = tmp1;
        second = tmp2;
    }
}
```

#### ✅ Java Solution
```java
public static void reorderList(ListNode head) {
    if (head == null || head.next == null) return;

    // Find middle
    ListNode slow = head, fast = head;
    while (fast.next != null && fast.next.next != null) {
        slow = slow.next; fast = fast.next.next;
    }

    // Reverse second half
    ListNode prev = null, curr = slow.next;
    slow.next = null;
    while (curr != null) {
        ListNode nxt = curr.next; curr.next = prev; prev = curr; curr = nxt;
    }

    // Merge
    ListNode first = head, second = prev;
    while (second != null) {
        ListNode t1 = first.next, t2 = second.next;
        first.next = second; second.next = t1;
        first = t1; second = t2;
    }
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(1) — in-place |

---

### 10. Copy List with Random Pointer

#### Problem Statement
A linked list where each node has a `next` and a `random` pointer (which may point to any node or null). Create a **deep copy** of this list.

**Example:**
```
Input:  [[7,null],[13,0],[11,4],[10,2],[1,0]]
              ↑ Each pair is [val, random_index]
Output: A completely new deep-copied list
```

#### 🌍 Real-World Relevance
Deep cloning complex object graphs (serialization/deserialization), copying game state with object references, duplicating graph structures.

#### 💡 Approach — Hash Map O(n) space
Map each original node to its clone. Then wire `.next` and `.random` using the map.

#### ⚠️ Edge Cases
- Random pointing to null
- Random pointing to the node itself (self-loop)
- Empty list

#### ✅ C++ Solution
```cpp
struct NodeRand {
    int val;
    NodeRand* next;
    NodeRand* random;
    NodeRand(int x) : val(x), next(nullptr), random(nullptr) {}
};

NodeRand* copyRandomList(NodeRand* head) {
    if (!head) return nullptr;
    unordered_map<NodeRand*, NodeRand*> cloneMap;

    // Pass 1: Create all clones
    NodeRand* curr = head;
    while (curr) {
        cloneMap[curr] = new NodeRand(curr->val);
        curr = curr->next;
    }

    // Pass 2: Wire next and random pointers
    curr = head;
    while (curr) {
        cloneMap[curr]->next   = cloneMap[curr->next];
        cloneMap[curr]->random = cloneMap[curr->random];
        curr = curr->next;
    }
    return cloneMap[head];
}
```

#### ✅ Java Solution
```java
import java.util.HashMap;
import java.util.Map;

class NodeRand {
    int val; NodeRand next, random;
    NodeRand(int x) { val = x; }
}

public static NodeRand copyRandomList(NodeRand head) {
    if (head == null) return null;
    Map<NodeRand, NodeRand> map = new HashMap<>();
    NodeRand curr = head;
    while (curr != null) { map.put(curr, new NodeRand(curr.val)); curr = curr.next; }
    curr = head;
    while (curr != null) {
        map.get(curr).next   = map.get(curr.next);
        map.get(curr).random = map.get(curr.random);
        curr = curr.next;
    }
    return map.get(head);
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(n) for hash map |

---

## 🔴 HARD PROBLEMS

---

### 11. Merge k Sorted Linked Lists

#### Problem Statement
Merge k sorted linked lists into one sorted linked list.

**Example:**
```
Input:  [1→4→5], [1→3→4], [2→6]
Output: 1→1→2→3→4→4→5→6
```

#### 🌍 Real-World Relevance
Core operation in external merge sort (used in databases for sorting data larger than memory), merging k server response streams ordered by timestamp.

#### 💡 Approach — Min Heap
Push the head of each list into a min heap. Repeatedly extract the minimum, add its next node to the heap.

#### ⚠️ Edge Cases
- k = 0 or all lists empty
- k = 1 → return the single list
- Some lists are null

#### ✅ C++ Solution
```cpp
#include <queue>
using namespace std;

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minHeap(cmp);

    for (ListNode* list : lists) {
        if (list) minHeap.push(list);
    }

    ListNode dummy(0);
    ListNode* curr = &dummy;

    while (!minHeap.empty()) {
        ListNode* node = minHeap.top(); minHeap.pop();
        curr->next = node;
        curr = curr->next;
        if (node->next) minHeap.push(node->next);
    }
    return dummy.next;
}
```

#### ✅ Java Solution
```java
import java.util.PriorityQueue;
import java.util.List;

public static ListNode mergeKLists(List<ListNode> lists) {
    PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> a.val - b.val);
    for (ListNode l : lists) if (l != null) minHeap.offer(l);

    ListNode dummy = new ListNode(0), curr = dummy;
    while (!minHeap.isEmpty()) {
        ListNode node = minHeap.poll();
        curr.next = node;
        curr = curr.next;
        if (node.next != null) minHeap.offer(node.next);
    }
    return dummy.next;
}
```

#### 📊 Complexity
Let N = total nodes, k = number of lists.
| Time | Space |
|------|-------|
| O(N log k) | O(k) for heap |

---

### 12. Reverse Nodes in k-Group

#### Problem Statement
Reverse the nodes of a linked list `k` at a time. If the number of nodes is not a multiple of k, leave the remaining nodes as-is.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5,  k = 2
Output: 2 → 1 → 4 → 3 → 5

Input:  1 → 2 → 3 → 4 → 5,  k = 3
Output: 3 → 2 → 1 → 4 → 5
```

#### 🌍 Real-World Relevance
Batch-processing tasks in fixed chunks, reversing segments in command queues, processing network packets in fixed-size frames.

#### 💡 Approach
1. Check if at least k nodes remain.
2. Reverse the k nodes.
3. Connect reversed group to the next group (recursively or iteratively).

#### ⚠️ Edge Cases
- k = 1 → no change
- Fewer than k nodes remaining → do not reverse
- k = list length → reverse entire list

#### ✅ C++ Solution
```cpp
// Helper: reverse k nodes starting from head, return {new_head, new_tail}
pair<ListNode*, ListNode*> reverseKNodes(ListNode* head, int k) {
    ListNode* prev = nullptr, *curr = head;
    for (int i = 0; i < k; i++) {
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return {prev, head};  // {new_head, old_head which is now tail}
}

ListNode* reverseKGroup(ListNode* head, int k) {
    // Check if k nodes remain
    ListNode* check = head;
    for (int i = 0; i < k; i++) {
        if (!check) return head;  // Fewer than k nodes — do not reverse
        check = check->next;
    }

    auto [newHead, tail] = reverseKNodes(head, k);
    tail->next = reverseKGroup(check, k);  // Recurse on remainder
    return newHead;
}
```

#### ✅ Java Solution
```java
public static ListNode reverseKGroup(ListNode head, int k) {
    ListNode check = head;
    for (int i = 0; i < k; i++) {
        if (check == null) return head;
        check = check.next;
    }
    // Reverse k nodes
    ListNode prev = null, curr = head;
    for (int i = 0; i < k; i++) {
        ListNode nxt = curr.next;
        curr.next = prev;
        prev = curr;
        curr = nxt;
    }
    head.next = reverseKGroup(curr, k);  // head is now the tail of reversed group
    return prev;
}
```

#### 📊 Complexity
| Time | Space |
|------|-------|
| O(n) | O(n/k) recursion stack |

---

### 13. LRU Cache Implementation

#### Problem Statement
Design a data structure that follows the **Least Recently Used (LRU)** cache eviction policy. Implement `get(key)` and `put(key, value)` — both must run in **O(1)**.

**Example:**
```
LRUCache cache = LRUCache(2);  // capacity = 2
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);     // returns 1
cache.put(3, 3);  // evicts key 2
cache.get(2);     // returns -1 (not found)
```

#### 🌍 Real-World Relevance
Web browser cache, OS page replacement algorithms, database buffer pool management, CDN edge caching. One of the most commonly asked system-design-meets-coding interview questions.

#### 💡 Approach — Doubly Linked List + Hash Map
- **DLL** maintains order: most recently used at tail, least recently used at head.
- **Hash map** maps key → DLL node for O(1) access.
- On `get`: move node to tail (mark as recently used).
- On `put`: insert at tail, evict from head if over capacity.

#### ⚠️ Edge Cases
- get on a non-existent key → return -1
- Capacity = 1
- Updating existing key (should move it to tail)

#### ✅ C++ Solution
```cpp
#include <unordered_map>
using namespace std;

class LRUCache {
    struct DLLNode {
        int key, val;
        DLLNode* prev;
        DLLNode* next;
        DLLNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, DLLNode*> cache;
    DLLNode* head;  // Dummy head (LRU end)
    DLLNode* tail;  // Dummy tail (MRU end)

    void remove(DLLNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertAtTail(DLLNode* node) {
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

public:
    LRUCache(int cap) : capacity(cap) {
        head = new DLLNode(-1, -1);
        tail = new DLLNode(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) return -1;
        DLLNode* node = cache[key];
        remove(node);
        insertAtTail(node);  // Mark as recently used
        return node->val;
    }

    void put(int key, int value) {
        if (cache.count(key)) {
            remove(cache[key]);
            delete cache[key];
        } else if ((int)cache.size() >= capacity) {
            DLLNode* lru = head->next;  // Least Recently Used
            remove(lru);
            cache.erase(lru->key);
            delete lru;
        }
        DLLNode* node = new DLLNode(key, value);
        insertAtTail(node);
        cache[key] = node;
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << "\n";   // 1
    cache.put(3, 3);                 // evicts 2
    cout << cache.get(2) << "\n";   // -1
    return 0;
}
```

#### ✅ Java Solution
```java
import java.util.HashMap;
import java.util.Map;

public class LRUCache {
    private class DLLNode {
        int key, val;
        DLLNode prev, next;
        DLLNode(int k, int v) { key = k; val = v; }
    }

    private final int capacity;
    private final Map<Integer, DLLNode> cache = new HashMap<>();
    private final DLLNode head = new DLLNode(-1, -1);  // Dummy LRU end
    private final DLLNode tail = new DLLNode(-1, -1);  // Dummy MRU end

    public LRUCache(int capacity) {
        this.capacity = capacity;
        head.next = tail; tail.prev = head;
    }

    private void remove(DLLNode node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    private void insertAtTail(DLLNode node) {
        node.prev = tail.prev; node.next = tail;
        tail.prev.next = node; tail.prev = node;
    }

    public int get(int key) {
        if (!cache.containsKey(key)) return -1;
        DLLNode node = cache.get(key);
        remove(node); insertAtTail(node);
        return node.val;
    }

    public void put(int key, int value) {
        if (cache.containsKey(key)) remove(cache.get(key));
        else if (cache.size() >= capacity) {
            DLLNode lru = head.next;
            remove(lru); cache.remove(lru.key);
        }
        DLLNode node = new DLLNode(key, value);
        insertAtTail(node); cache.put(key, node);
    }

    public static void main(String[] args) {
        LRUCache cache = new LRUCache(2);
        cache.put(1, 1); cache.put(2, 2);
        System.out.println(cache.get(1));   // 1
        cache.put(3, 3);
        System.out.println(cache.get(2));   // -1
    }
}
```

#### 📊 Complexity
| Operation | Time | Space |
|-----------|------|-------|
| get | O(1) | — |
| put | O(1) | O(capacity) |

---

## 🗺️ Pattern Summary for Linked Lists

| Pattern | Problems Using It |
|---------|------------------|
| Iterative Reversal | Reverse List, Reverse in k-Groups |
| Fast & Slow Pointer | Find Middle, Detect Cycle, Find Cycle Start |
| Floyd's Algorithm | Detect Cycle, Find Cycle Start |
| Dummy Head Node | Merge Two/k Lists, Remove Nth from End, Add Two Numbers |
| Two Pointer Gap | Remove Nth from End |
| DLL + Hash Map | LRU Cache |
| Min Heap | Merge k Sorted Lists |
| Hash Map Cloning | Copy List with Random Pointer |

---

*Next: [Stack Practice](../../stack/practice/problems.md) →*
