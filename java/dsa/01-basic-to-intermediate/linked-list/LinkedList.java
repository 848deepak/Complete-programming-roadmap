// ============================================================
// DSA | Java → Linked List: Singly, Doubly, Cycle Detection
// ============================================================
// DESCRIPTION:
//   Complete linked list implementation in Java covering:
//   - Singly Linked List with standard operations
//   - Doubly Linked List
//   - Floyd's Cycle Detection
//   - Merge two sorted lists
//   - Reverse linked list (iterative + recursive)
//
// COMPILE & RUN:
//   javac LinkedList.java && java LinkedList
// ============================================================

import java.util.HashSet;

public class LinkedList {

    // ============================================================
    // NODE
    // ============================================================
    static class Node {
        int  data;
        Node next, prev;   // prev only used in DLL
        Node(int val) { data = val; next = prev = null; }
    }

    // ============================================================
    // SINGLY LINKED LIST
    // ============================================================
    static class SinglyLL {
        Node head;
        int  size;

        void addFront(int val) {
            Node node = new Node(val);
            node.next = head;
            head      = node;
            size++;
        }

        void addBack(int val) {
            Node node = new Node(val);
            if (head == null) { head = node; size++; return; }
            Node curr = head;
            while (curr.next != null) curr = curr.next;
            curr.next = node;
            size++;
        }

        /** Delete first node with given value. O(n) */
        boolean delete(int val) {
            if (head == null) return false;
            if (head.data == val) { head = head.next; size--; return true; }
            Node curr = head;
            while (curr.next != null && curr.next.data != val)
                curr = curr.next;
            if (curr.next == null) return false;
            curr.next = curr.next.next;
            size--;
            return true;
        }

        /** Reverse singly LL iteratively. O(n) */
        void reverse() {
            Node prev = null, curr = head, next;
            while (curr != null) {
                next      = curr.next;
                curr.next = prev;
                prev      = curr;
                curr      = next;
            }
            head = prev;
        }

        /** Reverse recursively. O(n) */
        Node reverseRec(Node node) {
            if (node == null || node.next == null) return node;
            Node newHead  = reverseRec(node.next);
            node.next.next = node;
            node.next      = null;
            return newHead;
        }

        /** Find middle node using slow/fast pointer. O(n) */
        Node findMiddle() {
            Node slow = head, fast = head;
            while (fast != null && fast.next != null) {
                slow = slow.next;
                fast = fast.next.next;
            }
            return slow;
        }

        /** Check if list is a palindrome. O(n) */
        boolean isPalindrome() {
            if (head == null || head.next == null) return true;
            Node mid = findMiddle();
            // Reverse second half
            Node prev = null, curr = mid;
            while (curr != null) {
                Node nxt = curr.next;
                curr.next = prev;
                prev = curr;
                curr = nxt;
            }
            // Compare
            Node p1 = head, p2 = prev;
            while (p2 != null) {
                if (p1.data != p2.data) return false;
                p1 = p1.next;
                p2 = p2.next;
            }
            return true;
        }

        /** Merge sort on singly LL. O(n log n) */
        Node mergeSort(Node h) {
            if (h == null || h.next == null) return h;
            Node mid   = getMid(h);
            Node right = mid.next;
            mid.next   = null;
            Node leftSorted  = mergeSort(h);
            Node rightSorted = mergeSort(right);
            return mergeSorted(leftSorted, rightSorted);
        }

        Node getMid(Node h) {
            Node slow = h, fast = h.next;
            while (fast != null && fast.next != null) {
                slow = slow.next;
                fast = fast.next.next;
            }
            return slow;
        }

        Node mergeSorted(Node l1, Node l2) {
            Node dummy = new Node(0), tail = dummy;
            while (l1 != null && l2 != null) {
                if (l1.data <= l2.data) { tail.next = l1; l1 = l1.next; }
                else                    { tail.next = l2; l2 = l2.next; }
                tail = tail.next;
            }
            tail.next = (l1 != null) ? l1 : l2;
            return dummy.next;
        }

        void print(String label) {
            System.out.print("  " + label + ": ");
            Node curr = head;
            while (curr != null) {
                System.out.print(curr.data + (curr.next != null ? " → " : ""));
                curr = curr.next;
            }
            System.out.println(" → null  (size=" + size + ")");
        }
    }

    // ============================================================
    // FLOYD'S CYCLE DETECTION
    // ============================================================

    /** Returns meeting point node or null if no cycle. */
    static Node detectCycle(Node head) {
        Node slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) return slow;
        }
        return null;   // no cycle
    }

    /** Returns the cycle start node or null. */
    static Node cycleStart(Node head) {
        Node meet = detectCycle(head);
        if (meet == null) return null;
        slow: {
            Node p1 = head;
            while (p1 != meet) { p1 = p1.next; meet = meet.next; }
            return p1;   // cycle start
        }
    }

    /** Removes cycle if one exists. */
    static void removeCycle(Node head) {
        Node meet = detectCycle(head);
        if (meet == null) return;
        // Find node before cycle start
        Node p1 = head, p2 = meet;
        if (p1 == p2) {
            while (p2.next != p1) p2 = p2.next;
        } else {
            while (p1.next != p2.next) { p1 = p1.next; p2 = p2.next; }
        }
        p2.next = null;   // break cycle
    }

    // ============================================================
    // DOUBLY LINKED LIST
    // ============================================================
    static class DoublyLL {
        Node head, tail;
        int  size;

        void addBack(int val) {
            Node node = new Node(val);
            if (head == null) { head = tail = node; size++; return; }
            tail.next = node;
            node.prev = tail;
            tail      = node;
            size++;
        }

        void addFront(int val) {
            Node node = new Node(val);
            if (head == null) { head = tail = node; size++; return; }
            node.next  = head;
            head.prev  = node;
            head       = node;
            size++;
        }

        int popFront() {
            if (head == null) throw new IllegalStateException("empty");
            int val = head.data;
            head    = head.next;
            if (head != null) head.prev = null;
            else              tail = null;
            size--;
            return val;
        }

        int popBack() {
            if (tail == null) throw new IllegalStateException("empty");
            int val = tail.data;
            tail    = tail.prev;
            if (tail != null) tail.next = null;
            else              head = null;
            size--;
            return val;
        }

        void printForward(String label) {
            System.out.print("  " + label + ": HEAD ↔ ");
            Node curr = head;
            while (curr != null) {
                System.out.print("[" + curr.data + "]" + (curr.next != null ? " ↔ " : ""));
                curr = curr.next;
            }
            System.out.println(" ↔ NULL  (size=" + size + ")");
        }

        void printBackward(String label) {
            System.out.print("  " + label + ": TAIL ↔ ");
            Node curr = tail;
            while (curr != null) {
                System.out.print("[" + curr.data + "]" + (curr.prev != null ? " ↔ " : ""));
                curr = curr.prev;
            }
            System.out.println(" ↔ NULL");
        }
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {

        // --- Singly LL ---
        System.out.println("=== SINGLY LINKED LIST ===");
        SinglyLL sll = new SinglyLL();
        sll.addBack(10); sll.addBack(20); sll.addBack(30);
        sll.addFront(5);
        sll.print("After addFront(5) + addBack(10,20,30)");

        sll.delete(20);
        sll.print("After delete(20)");

        System.out.println("  Middle: " + sll.findMiddle().data);

        sll.reverse();
        sll.print("After reverse");

        // Palindrome check
        SinglyLL pal = new SinglyLL();
        for (int v : new int[]{1,2,3,2,1}) pal.addBack(v);
        System.out.println("  [1,2,3,2,1] isPalindrome: " + pal.isPalindrome());
        SinglyLL notPal = new SinglyLL();
        for (int v : new int[]{1,2,3}) notPal.addBack(v);
        System.out.println("  [1,2,3] isPalindrome: " + notPal.isPalindrome());

        // Merge sort
        System.out.println("\n=== MERGE SORT ON LINKED LIST ===");
        SinglyLL unsorted = new SinglyLL();
        for (int v : new int[]{5,1,8,3,9,2,7,4,6}) unsorted.addBack(v);
        unsorted.print("Before sort");
        unsorted.head = unsorted.mergeSort(unsorted.head);
        unsorted.print("After mergeSort");

        // --- Cycle Detection ---
        System.out.println("\n=== FLOYD'S CYCLE DETECTION ===");
        SinglyLL cycleList = new SinglyLL();
        for (int v : new int[]{1,2,3,4,5}) cycleList.addBack(v);
        System.out.println("  No cycle: " + (detectCycle(cycleList.head) == null ? "no cycle ✓" : "cycle?"));

        // Create cycle: tail → node with value 3
        Node cycleEntry = cycleList.head.next.next;  // node with value 3
        Node tail = cycleList.head;
        while (tail.next != null) tail = tail.next;
        tail.next = cycleEntry;   // create cycle

        System.out.println("  With cycle: " + (detectCycle(cycleList.head) != null ? "cycle detected ✓" : "no cycle?"));
        Node start = cycleStart(cycleList.head);
        System.out.println("  Cycle start value: " + (start != null ? start.data : "none"));

        removeCycle(cycleList.head);
        System.out.println("  After remove cycle: " + (detectCycle(cycleList.head) == null ? "no cycle ✓" : "still has cycle?"));

        // --- Doubly LL ---
        System.out.println("\n=== DOUBLY LINKED LIST ===");
        DoublyLL dll = new DoublyLL();
        dll.addBack(10); dll.addBack(20); dll.addBack(30);
        dll.addFront(5);
        dll.printForward("Forward");
        dll.printBackward("Backward");
        System.out.println("  popFront() → " + dll.popFront());
        System.out.println("  popBack()  → " + dll.popBack());
        dll.printForward("After pops");
    }
}
