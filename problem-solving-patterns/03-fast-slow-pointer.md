# 🐢🐇 Fast & Slow Pointer (Floyd's Tortoise & Hare)

## When to Use
- **Cycle detection** in linked lists or sequences
- **Finding middle** of a linked list in one pass
- **Finding cycle entry point** (Floyd's extended)
- **Happy number** detection

## How to Recognize
Keywords: *cycle*, *loop*, *circular*, *middle element*, *repeated sequence*.

## Common Mistakes
1. **Not handling null/end** — always check `fast && fast->next` before advancing
2. **Confusing meeting point with cycle start** — they're different; need Phase 2
3. **Forgetting odd/even length** — middle node definition varies

---

## Template — Cycle Detection

```cpp
// C++ — Detect cycle in linked list
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;           // 1 step
        fast = fast->next->next;     // 2 steps
        if (slow == fast) return true;  // Met inside cycle
    }
    return false;  // fast reached end → no cycle
}
```

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

## Template — Find Cycle Start

```cpp
// C++ — Phase 2: after detecting meeting point, find cycle entry
ListNode* findCycleStart(ListNode* head) {
    ListNode* slow = head, *fast = head;
    
    // Phase 1: Find meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Phase 2: Move one pointer to head, advance both by 1
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;  // Cycle entry point
        }
    }
    return nullptr;  // No cycle
}
```

## Template — Find Middle

```cpp
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;  // Middle (or 2nd middle for even length)
}
```

---

## Example Problems

### 1. Linked List Cycle II (Find Entry Point)
**Apply:** Phase 1 detects cycle, Phase 2 finds entry by resetting slow to head.

### 2. Find the Duplicate Number (Array as Linked List)
**Problem:** Array of n+1 integers in [1,n]. Find the duplicate.
**Key insight:** Treat index→value as next pointer. Duplicate creates a cycle. Apply Floyd's.

### 3. Happy Number
**Problem:** Repeatedly sum squares of digits. Returns to 1 → happy. Otherwise loops.
**Apply:** Slow computes one step, fast computes two. If they meet at 1 → happy.

---

## Why It Works (Mathematical Proof)

Let distance from head to cycle start = `d`, cycle length = `c`.
- When slow enters cycle, fast is `d mod c` steps ahead.
- They meet after `c - (d mod c)` more steps inside the cycle.
- Meeting point is `c - (d mod c)` from cycle start.
- Moving from head at speed 1 and from meeting point at speed 1 → they meet at cycle start after `d` steps.
