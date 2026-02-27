// ============================================================
// DSA | Java → Stack & Queue: Implementations + Applications
// ============================================================
// DESCRIPTION:
//   - Stack using array and LinkedList
//   - Queue using LinkedList and ArrayDeque
//   - Monotonic Stack applications
//   - Priority Queue (min/max heap) using Java's PriorityQueue
//
// COMPILE & RUN:
//   javac StackAndQueue.java && java StackAndQueue
// ============================================================

import java.util.*;

public class StackAndQueue {

    // ============================================================
    // SECTION 1: STACK USING ARRAY
    // ============================================================
    static class ArrayStack {
        int[] data;
        int top;
        int capacity;

        ArrayStack(int capacity) {
            this.capacity = capacity;
            data = new int[capacity];
            top = -1;
        }

        void push(int val) {
            if (top == capacity - 1)
                throw new RuntimeException("Stack overflow");
            data[++top] = val;
        }

        int pop() {
            if (top == -1)
                throw new EmptyStackException();
            return data[top--];
        }

        int peek() {
            if (top == -1)
                throw new EmptyStackException();
            return data[top];
        }

        boolean isEmpty() {
            return top == -1;
        }

        int size() {
            return top + 1;
        }
    }

    // ============================================================
    // SECTION 2: STACK USING LINKED LIST
    // ============================================================
    static class Node {
        int data;
        Node next;

        Node(int v) {
            data = v;
        }
    }

    static class LinkedStack {
        Node head;
        int size;

        void push(int val) {
            Node n = new Node(val);
            n.next = head;
            head = n;
            size++;
        }

        int pop() {
            if (head == null)
                throw new EmptyStackException();
            int val = head.data;
            head = head.next;
            size--;
            return val;
        }

        int peek() {
            if (head == null)
                throw new EmptyStackException();
            return head.data;
        }

        boolean isEmpty() {
            return head == null;
        }

        int size() {
            return size;
        }
    }

    // ============================================================
    // SECTION 3: STACK APPLICATIONS
    // ============================================================

    /** Balanced parentheses check. O(n) */
    static boolean isBalanced(String s) {
        Deque<Character> stk = new ArrayDeque<>();
        Map<Character, Character> match = Map.of(')', '(', ']', '[', '}', '{');
        for (char ch : s.toCharArray()) {
            if ("([{".indexOf(ch) >= 0) {
                stk.push(ch);
            } else if (match.containsKey(ch)) {
                if (stk.isEmpty() || stk.peek() != match.get(ch))
                    return false;
                stk.pop();
            }
        }
        return stk.isEmpty();
    }

    /** Postfix expression evaluation. O(n) */
    static int evalPostfix(String expr) {
        Deque<Integer> stk = new ArrayDeque<>();
        for (String token : expr.split(" ")) {
            switch (token) {
                case "+": {
                    int b = stk.pop(), a = stk.pop();
                    stk.push(a + b);
                    break;
                }
                case "-": {
                    int b = stk.pop(), a = stk.pop();
                    stk.push(a - b);
                    break;
                }
                case "*": {
                    int b = stk.pop(), a = stk.pop();
                    stk.push(a * b);
                    break;
                }
                case "/": {
                    int b = stk.pop(), a = stk.pop();
                    stk.push(a / b);
                    break;
                }
                default:
                    stk.push(Integer.parseInt(token));
            }
        }
        return stk.pop();
    }

    /** Next Greater Element using monotonic stack. O(n) */
    static int[] nextGreater(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        java.util.Arrays.fill(result, -1);
        Deque<Integer> stk = new ArrayDeque<>(); // stores indices

        for (int i = 0; i < n; i++) {
            while (!stk.isEmpty() && arr[i] > arr[stk.peek()])
                result[stk.pop()] = arr[i];
            stk.push(i);
        }
        return result;
    }

    /** Largest rectangle in histogram. O(n) */
    static int largestRect(int[] heights) {
        Deque<Integer> stk = new ArrayDeque<>();
        int maxArea = 0, n = heights.length;
        for (int i = 0; i <= n; i++) {
            int h = (i == n) ? 0 : heights[i];
            while (!stk.isEmpty() && h < heights[stk.peek()]) {
                int height = heights[stk.pop()];
                int width = stk.isEmpty() ? i : i - stk.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stk.push(i);
        }
        return maxArea;
    }

    // ============================================================
    // SECTION 4: QUEUE USING JAVA DEQUE
    // ============================================================

    static void demoQueue() {
        System.out.println("=== QUEUE (ArrayDeque) ===");
        Deque<Integer> queue = new ArrayDeque<>();
        // Enqueue with offer, dequeue with poll (FIFO)
        queue.offer(10);
        queue.offer(20);
        queue.offer(30);
        System.out.println("  Queue front: " + queue.peek());
        System.out.println("  Dequeue: " + queue.poll() + " → " + queue.poll());
        System.out.println("  Remaining size: " + queue.size());
    }

    // ============================================================
    // SECTION 5: SLIDING WINDOW MAXIMUM using Deque
    // ============================================================
    static int[] slidingWindowMax(int[] arr, int k) {
        Deque<Integer> dq = new ArrayDeque<>(); // stores indices (decreasing values)
        int n = arr.length;
        int[] result = new int[n - k + 1];

        for (int i = 0; i < n; i++) {
            // Remove out-of-window indices from front
            while (!dq.isEmpty() && dq.peek() < i - k + 1)
                dq.poll();
            // Remove smaller elements from back
            while (!dq.isEmpty() && arr[dq.peekLast()] <= arr[i])
                dq.pollLast();
            dq.offer(i);
            if (i >= k - 1)
                result[i - k + 1] = arr[dq.peek()];
        }
        return result;
    }

    // ============================================================
    // SECTION 6: PRIORITY QUEUE
    // ============================================================
    static void demoPriorityQueue() {
        System.out.println("\n=== PRIORITY QUEUE ===");

        // Min Heap (default)
        PriorityQueue<Integer> minPQ = new PriorityQueue<>();
        for (int v : new int[] { 5, 3, 8, 1, 9, 2, 7 })
            minPQ.offer(v);
        System.out.print("  Min PQ extract: ");
        while (!minPQ.isEmpty())
            System.out.print(minPQ.poll() + " ");
        System.out.println();

        // Max Heap
        PriorityQueue<Integer> maxPQ = new PriorityQueue<>(Collections.reverseOrder());
        for (int v : new int[] { 5, 3, 8, 1, 9, 2, 7 })
            maxPQ.offer(v);
        System.out.print("  Max PQ extract: ");
        while (!maxPQ.isEmpty())
            System.out.print(maxPQ.poll() + " ");
        System.out.println();

        // K-th largest using min-heap of size K
        int[] arr = { 3, 2, 1, 5, 6, 4 };
        int k = 2;
        PriorityQueue<Integer> kPQ = new PriorityQueue<>();
        for (int v : arr) {
            kPQ.offer(v);
            if (kPQ.size() > k)
                kPQ.poll();
        }
        System.out.println("  " + k + "-th largest of [3,2,1,5,6,4]: " + kPQ.peek()); // 5

        // LeetCode 778: Merge K sorted lists using heap
        int[][] lists = { { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 } };
        PriorityQueue<int[]> heap = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        for (int i = 0; i < lists.length; i++)
            heap.offer(new int[] { lists[i][0], i, 0 });
        System.out.print("  Merge 3 sorted arrays: ");
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            System.out.print(curr[0] + " ");
            int row = curr[1], col = curr[2];
            if (col + 1 < lists[row].length)
                heap.offer(new int[] { lists[row][col + 1], row, col + 1 });
        }
        System.out.println();
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {

        // --- Array Stack ---
        System.out.println("=== ARRAY STACK ===");
        ArrayStack astk = new ArrayStack(5);
        astk.push(10);
        astk.push(20);
        astk.push(30);
        System.out.println("  peek: " + astk.peek() + "  size: " + astk.size());
        System.out.println("  pop: " + astk.pop() + " → " + astk.pop());
        System.out.println("  size after pops: " + astk.size());

        // --- Linked Stack ---
        System.out.println("\n=== LINKED STACK ===");
        LinkedStack lstk = new LinkedStack();
        lstk.push(1);
        lstk.push(2);
        lstk.push(3);
        System.out.print("  Popping: ");
        while (!lstk.isEmpty())
            System.out.print(lstk.pop() + " ");
        System.out.println();

        // --- Applications ---
        System.out.println("\n=== STACK APPLICATIONS ===");
        System.out.println("  isBalanced(\"()[]{}\"):    " + isBalanced("()[]{}"));
        System.out.println("  isBalanced(\"([)]\"):      " + isBalanced("([)]"));
        System.out.println("  evalPostfix(\"5 1 2 + 4 * + 3 -\"): " + evalPostfix("5 1 2 + 4 * + 3 -"));

        int[] arr = { 4, 5, 2, 10, 8 };
        int[] nge = nextGreater(arr);
        System.out.print("  nextGreater([4,5,2,10,8]): [");
        for (int i = 0; i < nge.length; i++)
            System.out.print(nge[i] + (i + 1 < nge.length ? "," : ""));
        System.out.println("]");

        System.out.println("  largestRect([2,1,5,6,2,3]): " + largestRect(new int[] { 2, 1, 5, 6, 2, 3 }));

        // --- Queue ---
        demoQueue();

        // --- Sliding Window Max ---
        System.out.println("\n=== SLIDING WINDOW MAX (k=3) ===");
        int[] sw = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int[] maxArr = slidingWindowMax(sw, 3);
        System.out.print("  [1,3,-1,-3,5,3,6,7] k=3: [");
        for (int i = 0; i < maxArr.length; i++)
            System.out.print(maxArr[i] + (i + 1 < maxArr.length ? "," : ""));
        System.out.println("]"); // [3,3,5,5,6,7]

        // --- Priority Queue ---
        demoPriorityQueue();
    }
}
