// ============================================================
// DSA | Java → Sorting Algorithms
// ============================================================
// DESCRIPTION:
//   All major sorting algorithms implemented in Java:
//   - Bubble Sort, Selection Sort, Insertion Sort
//   - Merge Sort, Quick Sort, Heap Sort
//   - Counting Sort, Radix Sort
//
// COMPILE & RUN:
//   javac SortingAlgorithms.java && java SortingAlgorithms
//
// COMPLEXITY SUMMARY (at bottom of file)
// ============================================================

import java.util.*;

public class SortingAlgorithms {

    // 1. BUBBLE SORT — O(n²) stable, early exit
    static void bubbleSort(int[] arr) {
        int n = arr.length;
        for (int pass = 0; pass < n - 1; pass++) {
            boolean swapped = false;
            for (int j = 0; j < n - 1 - pass; j++) {
                if (arr[j] > arr[j + 1]) {
                    int tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                    swapped = true;
                }
            }
            if (!swapped)
                break; // already sorted
        }
    }

    // 2. SELECTION SORT — O(n²) unstable
    static void selectionSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++)
                if (arr[j] < arr[minIdx])
                    minIdx = j;
            int tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }

    // 3. INSERTION SORT — O(n²) stable, O(n) best
    static void insertionSort(int[] arr) {
        int n = arr.length;
        for (int i = 1; i < n; i++) {
            int key = arr[i], j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // 4. MERGE SORT — O(n log n) stable
    static void mergeSort(int[] arr, int left, int right) {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    static void merge(int[] arr, int left, int mid, int right) {
        int[] tmp = new int[right - left + 1];
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right)
            tmp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
        while (i <= mid)
            tmp[k++] = arr[i++];
        while (j <= right)
            tmp[k++] = arr[j++];
        System.arraycopy(tmp, 0, arr, left, tmp.length);
    }

    // 5. QUICK SORT — O(n log n) avg, O(n²) worst, unstable
    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int partition(int[] arr, int low, int high) {
        int pivot = arr[high], storeIdx = low;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                int tmp = arr[storeIdx];
                arr[storeIdx] = arr[j];
                arr[j] = tmp;
                storeIdx++;
            }
        }
        int tmp = arr[storeIdx];
        arr[storeIdx] = arr[high];
        arr[high] = tmp;
        return storeIdx;
    }

    // 6. HEAP SORT — O(n log n) unstable, in-place
    static void heapSort(int[] arr) {
        int n = arr.length;
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i); // build max-heap
        for (int i = n - 1; i > 0; i--) {
            int tmp = arr[0];
            arr[0] = arr[i];
            arr[i] = tmp; // move max to end
            heapify(arr, i, 0);
        }
    }

    static void heapify(int[] arr, int n, int i) {
        int largest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest])
            largest = l;
        if (r < n && arr[r] > arr[largest])
            largest = r;
        if (largest != i) {
            int tmp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = tmp;
            heapify(arr, n, largest);
        }
    }

    // 7. COUNTING SORT — O(n+k) stable
    static void countingSort(int[] arr) {
        if (arr.length == 0)
            return;
        int max = Arrays.stream(arr).max().getAsInt();
        int[] count = new int[max + 1];
        for (int x : arr)
            count[x]++;
        for (int i = 1; i <= max; i++)
            count[i] += count[i - 1];
        int[] output = new int[arr.length];
        for (int i = arr.length - 1; i >= 0; i--)
            output[--count[arr[i]]] = arr[i];
        System.arraycopy(output, 0, arr, 0, arr.length);
    }

    // 8. RADIX SORT — O(d*(n+k)) stable
    static void radixSort(int[] arr) {
        if (arr.length == 0)
            return;
        int max = Arrays.stream(arr).max().getAsInt();
        for (int exp = 1; max / exp > 0; exp *= 10)
            countByDigit(arr, exp);
    }

    static void countByDigit(int[] arr, int exp) {
        int n = arr.length;
        int[] output = new int[n], count = new int[10];
        for (int v : arr)
            count[(v / exp) % 10]++;
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            output[--count[(arr[i] / exp) % 10]] = arr[i];
        System.arraycopy(output, 0, arr, 0, n);
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {
        int[] original = { 64, 34, 25, 12, 22, 11, 90, 5, 47, 31 };

        System.out.println("=== SORTING ALGORITHMS COMPARISON ===");
        System.out.print("  Original:       ");
        System.out.println(Arrays.toString(original));

        int[] arr;

        arr = original.clone();
        bubbleSort(arr);
        System.out.println("  Bubble Sort:    " + Arrays.toString(arr));

        arr = original.clone();
        selectionSort(arr);
        System.out.println("  Selection Sort: " + Arrays.toString(arr));

        arr = original.clone();
        insertionSort(arr);
        System.out.println("  Insertion Sort: " + Arrays.toString(arr));

        arr = original.clone();
        mergeSort(arr, 0, arr.length - 1);
        System.out.println("  Merge Sort:     " + Arrays.toString(arr));

        arr = original.clone();
        quickSort(arr, 0, arr.length - 1);
        System.out.println("  Quick Sort:     " + Arrays.toString(arr));

        arr = original.clone();
        heapSort(arr);
        System.out.println("  Heap Sort:      " + Arrays.toString(arr));

        arr = original.clone();
        countingSort(arr);
        System.out.println("  Counting Sort:  " + Arrays.toString(arr));

        arr = original.clone();
        radixSort(arr);
        System.out.println("  Radix Sort:     " + Arrays.toString(arr));

        // Edge cases
        System.out.println("\n=== EDGE CASES ===");
        int[] empty = {};
        bubbleSort(empty);
        System.out.println("  Empty array:  " + Arrays.toString(empty));

        int[] single = { 42 };
        quickSort(single, 0, 0);
        System.out.println("  Single elem:  " + Arrays.toString(single));

        int[] dupes = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
        mergeSort(dupes, 0, dupes.length - 1);
        System.out.println("  With dupes:   " + Arrays.toString(dupes));

        int[] neg = { -3, 5, -1, 0, -2, 4 };
        Arrays.sort(neg);
        System.out.println("  Negatives:    " + Arrays.toString(neg));

        // Java built-in comparison
        System.out.println("\n=== JAVA BUILT-IN Arrays.sort() ===");
        arr = original.clone();
        Arrays.sort(arr);
        System.out.println("  Arrays.sort:  " + Arrays.toString(arr));
        String[] words = { "banana", "apple", "cherry", "date" };
        Arrays.sort(words);
        System.out.println("  String sort:  " + Arrays.toString(words));
        // Custom comparator
        Integer[] ints = { 3, 1, 4, 1, 5, 9, 2, 6 };
        Arrays.sort(ints, Comparator.reverseOrder());
        System.out.println("  Reverse sort: " + Arrays.toString(ints));
    }
}

// ============================================================
// COMPLEXITY SUMMARY
// Algorithm | Best | Avg | Worst | Space | Stable
// Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes
// Selection | O(n²) | O(n²) | O(n²) | O(1) | No
// Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes
// Merge | O(nlogn)| O(nlogn)| O(nlogn)| O(n) | Yes
// Quick | O(nlogn)| O(nlogn)| O(n²) | O(logn)| No
// Heap | O(nlogn)| O(nlogn)| O(nlogn)| O(1) | No
// Counting | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes
// Radix | O(dn) | O(dn) | O(dn) | O(n) | Yes
// ============================================================
