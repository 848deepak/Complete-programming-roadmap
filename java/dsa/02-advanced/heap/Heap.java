// ============================================================
// DSA | Java → Heap: Min Heap, Max Heap, Heap Sort, Applications
// ============================================================
// DESCRIPTION:
//   Complete heap implementation in Java covering:
//   - Min Heap and Max Heap from scratch
//   - Build heap in O(n) (bottom-up heapify)
//   - Heap Sort
//   - K-th largest/smallest using heap
//   - Merge K sorted arrays
//   - Java PriorityQueue (built-in) vs scratch
//
// COMPILE & RUN:
//   javac Heap.java && java Heap
//
// BINARY HEAP ARRAY REPRESENTATION:
//   Node at index i :
//     parent     = (i-1)/2
//     leftChild  = 2*i+1
//     rightChild = 2*i+2
//
//   MaxHeap: parent >= children  (root = maximum)
//   MinHeap: parent <= children  (root = minimum)
// ============================================================

import java.util.*;

public class Heap {

    // ============================================================
    // SECTION 1: MIN HEAP (from scratch)
    // ============================================================

    static class MinHeap {
        private int[] heap;
        private int size;

        MinHeap(int capacity) {
            heap = new int[capacity];
            size = 0;
        }

        // Convenience constructor that builds from an existing array (O(n))
        MinHeap(int[] arr) {
            heap = arr.clone();
            size = arr.length;
            // Bottom-up heapify: start from last non-leaf
            for (int i = size / 2 - 1; i >= 0; i--)
                siftDown(i);
        }

        private int parent(int i) {
            return (i - 1) / 2;
        }

        private int left(int i) {
            return 2 * i + 1;
        }

        private int right(int i) {
            return 2 * i + 2;
        }

        private void swap(int i, int j) {
            int t = heap[i];
            heap[i] = heap[j];
            heap[j] = t;
        }

        /**
         * Bubble element at index i UP to restore min-heap property.
         * Used after insertion. Time: O(log n)
         */
        private void siftUp(int i) {
            while (i > 0 && heap[parent(i)] > heap[i]) {
                swap(parent(i), i);
                i = parent(i);
            }
        }

        /**
         * Push element at index i DOWN to restore min-heap property.
         * Used after extraction. Time: O(log n)
         */
        private void siftDown(int i) {
            while (true) {
                int smallest = i, l = left(i), r = right(i);
                if (l < size && heap[l] < heap[smallest])
                    smallest = l;
                if (r < size && heap[r] < heap[smallest])
                    smallest = r;
                if (smallest == i)
                    break;
                swap(i, smallest);
                i = smallest;
            }
        }

        /** Insert element. Time: O(log n) */
        void push(int val) {
            if (size == heap.length)
                throw new RuntimeException("Heap overflow");
            heap[size++] = val;
            siftUp(size - 1);
        }

        /** Extract minimum. Time: O(log n) */
        int pop() {
            if (size == 0)
                throw new NoSuchElementException("Heap empty");
            int min = heap[0];
            heap[0] = heap[--size];
            siftDown(0);
            return min;
        }

        /** Peek minimum without removing. Time: O(1) */
        int peek() {
            if (size == 0)
                throw new NoSuchElementException("Heap empty");
            return heap[0];
        }

        boolean isEmpty() {
            return size == 0;
        }

        int size() {
            return size;
        }

        void print(String label) {
            System.out.print("  " + label + ": [");
            for (int i = 0; i < size; i++)
                System.out.print(heap[i] + (i + 1 < size ? "," : ""));
            System.out.println("]  min=" + (size > 0 ? heap[0] : "N/A"));
        }
    }

    // ============================================================
    // SECTION 2: MAX HEAP (from scratch)
    // ============================================================

    static class MaxHeap {
        private int[] heap;
        private int size;

        MaxHeap(int capacity) {
            heap = new int[capacity];
            size = 0;
        }

        MaxHeap(int[] arr) {
            heap = arr.clone();
            size = arr.length;
            for (int i = size / 2 - 1; i >= 0; i--)
                siftDown(i);
        }

        private int parent(int i) {
            return (i - 1) / 2;
        }

        private int left(int i) {
            return 2 * i + 1;
        }

        private int right(int i) {
            return 2 * i + 2;
        }

        private void swap(int i, int j) {
            int t = heap[i];
            heap[i] = heap[j];
            heap[j] = t;
        }

        private void siftUp(int i) {
            while (i > 0 && heap[parent(i)] < heap[i]) {
                swap(parent(i), i);
                i = parent(i);
            }
        }

        private void siftDown(int i) {
            while (true) {
                int largest = i, l = left(i), r = right(i);
                if (l < size && heap[l] > heap[largest])
                    largest = l;
                if (r < size && heap[r] > heap[largest])
                    largest = r;
                if (largest == i)
                    break;
                swap(i, largest);
                i = largest;
            }
        }

        void push(int val) {
            if (size == heap.length)
                throw new RuntimeException("Heap overflow");
            heap[size++] = val;
            siftUp(size - 1);
        }

        int pop() {
            if (size == 0)
                throw new NoSuchElementException("Heap empty");
            int max = heap[0];
            heap[0] = heap[--size];
            siftDown(0);
            return max;
        }

        int peek() {
            if (size == 0)
                throw new NoSuchElementException("Heap empty");
            return heap[0];
        }

        boolean isEmpty() {
            return size == 0;
        }

        int size() {
            return size;
        }

        /**
         * In-place heap sort using this MaxHeap.
         * Returns a new ascending-sorted array.
         * Time: O(n log n) | Space: O(1) (sorts the internal array)
         */
        int[] heapSort() {
            int[] copy = Arrays.copyOf(heap, size);
            int n = size;
            // Extract max one by one
            for (int i = n - 1; i > 0; i--) {
                swap(0, i); // move max to end
                size--; // shrink heap
                siftDown(0);
            }
            size = n; // restore
            return Arrays.copyOf(heap, n); // ascending sorted
        }

        void print(String label) {
            System.out.print("  " + label + ": [");
            for (int i = 0; i < size; i++)
                System.out.print(heap[i] + (i + 1 < size ? "," : ""));
            System.out.println("]  max=" + (size > 0 ? heap[0] : "N/A"));
        }
    }

    // ============================================================
    // SECTION 3: K-TH LARGEST / SMALLEST
    // ============================================================

    /**
     * Returns the K-th largest element.
     * Uses a MinHeap of size K — the root = K-th largest.
     * Time: O(n log k)
     */
    static int kthLargest(int[] arr, int k) {
        MinHeap minH = new MinHeap(arr.length);
        for (int x : arr) {
            minH.push(x);
            if (minH.size() > k)
                minH.pop(); // keep only k largest
        }
        return minH.peek();
    }

    /**
     * Returns the K-th smallest element.
     * Uses a MaxHeap of size K — the root = K-th smallest.
     * Time: O(n log k)
     */
    static int kthSmallest(int[] arr, int k) {
        MaxHeap maxH = new MaxHeap(arr.length);
        for (int x : arr) {
            maxH.push(x);
            if (maxH.size() > k)
                maxH.pop(); // keep only k smallest
        }
        return maxH.peek();
    }

    // ============================================================
    // SECTION 4: TOP-K FREQUENT ELEMENTS
    // ============================================================

    /**
     * Returns the K most frequent elements.
     * Uses a MinHeap keyed on frequency.
     * Time: O(n log k)
     */
    static int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int n : nums)
            freq.merge(n, 1, Integer::sum);

        // MinHeap of {frequency, value}
        PriorityQueue<int[]> minPQ = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        for (Map.Entry<Integer, Integer> e : freq.entrySet()) {
            minPQ.offer(new int[] { e.getValue(), e.getKey() });
            if (minPQ.size() > k)
                minPQ.poll(); // remove least frequent
        }

        int[] result = new int[k];
        for (int i = k - 1; i >= 0; i--)
            result[i] = minPQ.poll()[1];
        return result;
    }

    // ============================================================
    // SECTION 5: MERGE K SORTED ARRAYS
    // ============================================================

    /**
     * Merges K sorted arrays into one sorted array.
     * Uses a MinHeap to always extract the global minimum.
     * Time: O(N log K) — N total elements, K arrays
     */
    static int[] mergeKSorted(int[][] arrays) {
        int total = 0;
        for (int[] a : arrays)
            total += a.length;

        // MinHeap: {value, arrayIndex, elementIndex}
        PriorityQueue<int[]> minPQ = new PriorityQueue<>(Comparator.comparingInt(x -> x[0]));
        for (int i = 0; i < arrays.length; i++) {
            if (arrays[i].length > 0)
                minPQ.offer(new int[] { arrays[i][0], i, 0 });
        }

        int[] result = new int[total];
        int idx = 0;
        while (!minPQ.isEmpty()) {
            int[] curr = minPQ.poll();
            result[idx++] = curr[0];
            int row = curr[1], col = curr[2];
            if (col + 1 < arrays[row].length)
                minPQ.offer(new int[] { arrays[row][col + 1], row, col + 1 });
        }
        return result;
    }

    // ============================================================
    // SECTION 6: MEDIAN FROM DATA STREAM
    // ============================================================
    /**
     * MedianFinder using two heaps:
     * - maxHeap (lower half) — top = median candidate from left
     * - minHeap (upper half) — top = median candidate from right
     *
     * Invariant: maxHeap.size() == minHeap.size()
     * or maxHeap.size() == minHeap.size() + 1 (odd total)
     *
     * Time: addNum O(log n), findMedian O(1)
     */
    static class MedianFinder {
        PriorityQueue<Integer> maxH = new PriorityQueue<>(Collections.reverseOrder()); // lower half
        PriorityQueue<Integer> minH = new PriorityQueue<>(); // upper half

        void addNum(int num) {
            maxH.offer(num); // always push to max heap first
            minH.offer(maxH.poll()); // balance: push max of lower to upper

            if (minH.size() > maxH.size()) // maintain maxH.size >= minH.size
                maxH.offer(minH.poll());
        }

        double findMedian() {
            if (maxH.size() > minH.size())
                return maxH.peek(); // odd count
            return (maxH.peek() + minH.peek()) / 2.0; // even count
        }
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {

        // --- Min Heap ---
        System.out.println("=== MIN HEAP ===");
        MinHeap minH = new MinHeap(20);
        for (int v : new int[] { 5, 3, 8, 1, 9, 2, 7 })
            minH.push(v);
        minH.print("After insert {5,3,8,1,9,2,7}");
        System.out.print("  Extract in order: ");
        while (!minH.isEmpty())
            System.out.print(minH.pop() + " ");
        System.out.println();

        // --- Build Heap O(n) ---
        System.out.println("\n=== BUILD MIN HEAP O(n) ===");
        MinHeap built = new MinHeap(new int[] { 4, 10, 3, 5, 1, 8 });
        built.print("Built from {4,10,3,5,1,8}");

        // --- Max Heap ---
        System.out.println("\n=== MAX HEAP ===");
        MaxHeap maxH = new MaxHeap(20);
        for (int v : new int[] { 5, 3, 8, 1, 9, 2, 7 })
            maxH.push(v);
        maxH.print("After insert {5,3,8,1,9,2,7}");

        // --- Heap Sort ---
        System.out.println("\n=== HEAP SORT ===");
        MaxHeap sortHeap = new MaxHeap(new int[] { 5, 3, 8, 1, 9, 2, 7, 4, 6 });
        int[] sorted = sortHeap.heapSort();
        System.out.println("  Sorted: " + Arrays.toString(sorted));

        // --- K-th largest / smallest ---
        System.out.println("\n=== K-TH LARGEST / SMALLEST ===");
        int[] arr = { 3, 2, 1, 5, 6, 4 };
        System.out.println("  Array: " + Arrays.toString(arr));
        System.out.println("  2nd largest:  " + kthLargest(arr, 2)); // 5
        System.out.println("  3rd largest:  " + kthLargest(arr, 3)); // 4
        System.out.println("  2nd smallest: " + kthSmallest(arr, 2)); // 2
        System.out.println("  3rd smallest: " + kthSmallest(arr, 3)); // 3

        // --- Top K Frequent ---
        System.out.println("\n=== TOP K FREQUENT ===");
        int[] nums = { 1, 1, 1, 2, 2, 3 };
        System.out.println("  Input: [1,1,1,2,2,3]");
        System.out.println("  Top 2 frequent: " + Arrays.toString(topKFrequent(nums, 2))); // [1,2]

        // --- Merge K Sorted Arrays ---
        System.out.println("\n=== MERGE K SORTED ARRAYS ===");
        int[][] arrays = { { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 }, { 0, 10 } };
        System.out.println("  Merged: " + Arrays.toString(mergeKSorted(arrays)));

        // --- Median from Stream ---
        System.out.println("\n=== MEDIAN FROM DATA STREAM ===");
        MedianFinder mf = new MedianFinder();
        for (int v : new int[] { 1, 2, 3, 4, 5 }) {
            mf.addNum(v);
            System.out.println("  After adding " + v + ": median = " + mf.findMedian());
        }

        // --- STL PriorityQueue comparison ---
        System.out.println("\n=== JAVA PriorityQueue (built-in) ===");
        PriorityQueue<Integer> javaPQ = new PriorityQueue<>(); // min by default
        for (int v : new int[] { 5, 3, 8, 1, 9, 2, 7 })
            javaPQ.offer(v);
        System.out.print("  Java PQ (min): ");
        while (!javaPQ.isEmpty())
            System.out.print(javaPQ.poll() + " ");
        System.out.println();
    }
}

// ============================================================
// COMPLEXITY SUMMARY
// push : O(log n)
// pop : O(log n)
// peek : O(1)
// buildHeap(arr) : O(n) ← bottom-up heapify
// heapSort : O(n log n), O(1) extra space
// kthLargest(k) : O(n log k) ← better than O(n log n) full sort
// topKFrequent : O(n log k)
// mergeKSorted : O(N log K) — N=total elements, K=number of arrays
// median addNum : O(log n), findMedian: O(1)
// ============================================================
