# 🔍 Searching & Sorting — Practice Problems

> **Topic:** Binary Search, Sorting Variants | **Level:** Easy → Hard

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Binary Search](#1-binary-search) | 🟢 Easy | Classic BS |
| 2 | [First & Last Position in Sorted Array](#2-first-last-position) | 🟢 Easy | Lower/Upper Bound |
| 3 | [Search Insert Position](#3-search-insert-position) | 🟢 Easy | Lower Bound |
| 4 | [Square Root (Integer)](#4-square-root) | 🟢 Easy | BS on Answer |
| 5 | [Count Occurrences in Sorted Array](#5-count-occurrences) | 🟢 Easy | Lower+Upper Bound |
| 6 | [Search in Rotated Sorted Array](#6-search-rotated) | 🟡 Medium | Modified BS |
| 7 | [Find Peak Element](#7-find-peak) | 🟡 Medium | BS on Condition |
| 8 | [Kth Smallest Element (Quickselect)](#8-kth-smallest) | 🟡 Medium | Quickselect |
| 9 | [Merge Sort — Count Inversions](#9-count-inversions) | 🟡 Medium | Modified Merge Sort |
| 10 | [Aggressive Cows / Magnetic Balls](#10-aggressive-cows) | 🟡 Medium | BS on Answer |
| 11 | [Median of Two Sorted Arrays](#11-median-two-sorted) | 🔴 Hard | BS on Partition |
| 12 | [Allocate Minimum Pages](#12-allocate-pages) | 🔴 Hard | BS on Answer |
| 13 | [Find in Row-Column Sorted Matrix](#13-sorted-matrix-search) | 🔴 Hard | Staircase Search |

---

## 🟢 EASY PROBLEMS

### 1. Binary Search
```cpp
int binarySearch(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size()-1;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid+1;
        else hi = mid-1;
    }
    return -1;
}
```
```java
public static int binarySearch(int[] arr, int target) {
    int lo=0, hi=arr.length-1;
    while (lo<=hi) { int mid=lo+(hi-lo)/2; if (arr[mid]==target) return mid; else if (arr[mid]<target) lo=mid+1; else hi=mid-1; }
    return -1;
}
```
**O(log n) time, O(1) space.**

---

### 2. First & Last Position in Sorted Array
**Problem:** Find first and last index of target in sorted array. `[5,7,7,8,8,10], 8 → [3,4]`.
**Approach:** Two binary searches — one for lower bound, one for upper bound.

```cpp
int lowerBound(vector<int>& a, int t) {
    int lo=0, hi=a.size()-1, res=-1;
    while (lo<=hi) { int mid=lo+(hi-lo)/2; if (a[mid]==t) { res=mid; hi=mid-1; } else if (a[mid]<t) lo=mid+1; else hi=mid-1; }
    return res;
}
int upperBound(vector<int>& a, int t) {
    int lo=0, hi=a.size()-1, res=-1;
    while (lo<=hi) { int mid=lo+(hi-lo)/2; if (a[mid]==t) { res=mid; lo=mid+1; } else if (a[mid]<t) lo=mid+1; else hi=mid-1; }
    return res;
}
```
```java
static int lower(int[] a, int t) { int lo=0,hi=a.length-1,r=-1; while(lo<=hi){int m=lo+(hi-lo)/2;if(a[m]==t){r=m;hi=m-1;}else if(a[m]<t)lo=m+1;else hi=m-1;}return r; }
static int upper(int[] a, int t) { int lo=0,hi=a.length-1,r=-1; while(lo<=hi){int m=lo+(hi-lo)/2;if(a[m]==t){r=m;lo=m+1;}else if(a[m]<t)lo=m+1;else hi=m-1;}return r; }
```

---

### 3. Search Insert Position
**Problem:** Find index to insert target to keep array sorted. Returns lower bound.

```cpp
int searchInsert(vector<int>& nums, int target) {
    int lo=0, hi=nums.size()-1;
    while (lo<=hi) { int mid=lo+(hi-lo)/2; if (nums[mid]<target) lo=mid+1; else hi=mid-1; }
    return lo;
}
```
```java
public static int searchInsert(int[] nums, int target) {
    int lo=0,hi=nums.length-1; while(lo<=hi){int m=lo+(hi-lo)/2;if(nums[m]<target)lo=m+1;else hi=m-1;} return lo;
}
```

---

### 4. Square Root (Integer)
**Problem:** Compute floor(√x) without using sqrt function.
**Approach:** Binary search on answer [0, x]. Check if mid*mid <= x.

```cpp
int mySqrt(int x) {
    if (x<2) return x;
    long lo=1,hi=x/2,ans=0;
    while (lo<=hi) { long mid=lo+(hi-lo)/2; if (mid<=x/mid) { ans=mid; lo=mid+1; } else hi=mid-1; }
    return ans;
}
```
```java
public static int mySqrt(int x) {
    if (x<2) return x;
    long lo=1,hi=x/2,ans=0;
    while(lo<=hi){long m=lo+(hi-lo)/2;if(m<=x/m){ans=m;lo=m+1;}else hi=m-1;}
    return (int)ans;
}
```

---

### 5. Count Occurrences in Sorted Array
**Problem:** Count how many times target appears.
**Approach:** `upperBound - lowerBound + 1`.

```cpp
int countOccurrences(vector<int>& a, int t) {
    int first = lowerBound(a, t), last = upperBound(a, t);
    return (first == -1) ? 0 : last - first + 1;
}
```

---

## 🟡 MEDIUM PROBLEMS

### 6. Search in Rotated Sorted Array
**Problem:** Sorted array rotated at unknown pivot. Find target in O(log n).
```
[4,5,6,7,0,1,2], target=0 → 4
```
**Approach:** Modified BS. Determine which half is sorted, check if target lies there.

```cpp
int search(vector<int>& nums, int target) {
    int lo=0, hi=nums.size()-1;
    while (lo<=hi) {
        int mid=lo+(hi-lo)/2;
        if (nums[mid]==target) return mid;
        if (nums[lo]<=nums[mid]) { // Left half sorted
            if (target>=nums[lo]&&target<nums[mid]) hi=mid-1; else lo=mid+1;
        } else { // Right half sorted
            if (target>nums[mid]&&target<=nums[hi]) lo=mid+1; else hi=mid-1;
        }
    }
    return -1;
}
```
```java
public static int search(int[] nums, int target) {
    int lo=0,hi=nums.length-1;
    while(lo<=hi){
        int mid=lo+(hi-lo)/2;
        if(nums[mid]==target)return mid;
        if(nums[lo]<=nums[mid]){if(target>=nums[lo]&&target<nums[mid])hi=mid-1;else lo=mid+1;}
        else{if(target>nums[mid]&&target<=nums[hi])lo=mid+1;else hi=mid-1;}
    }
    return -1;
}
```
**O(log n).**

---

### 7. Find Peak Element
**Problem:** Find any local peak (element > neighbors) in O(log n).
**Approach:** BS — if mid > mid+1, peak is on left side (including mid). Else right side.

```cpp
int findPeakElement(vector<int>& nums) {
    int lo=0, hi=nums.size()-1;
    while (lo<hi) { int mid=lo+(hi-lo)/2; if (nums[mid]>nums[mid+1]) hi=mid; else lo=mid+1; }
    return lo;
}
```
```java
public static int findPeakElement(int[] nums) {
    int lo=0,hi=nums.length-1;
    while(lo<hi){int mid=lo+(hi-lo)/2;if(nums[mid]>nums[mid+1])hi=mid;else lo=mid+1;}
    return lo;
}
```

---

### 8. Kth Smallest Element (Quickselect)
**Problem:** Find kth smallest element in unsorted array in average O(n).

```cpp
int quickselect(vector<int>& nums, int lo, int hi, int k) {
    int pivot = nums[hi], i = lo;
    for (int j=lo;j<hi;j++) if (nums[j]<=pivot) swap(nums[i++],nums[j]);
    swap(nums[i],nums[hi]);
    if (i==k) return nums[i];
    return i<k ? quickselect(nums,i+1,hi,k) : quickselect(nums,lo,i-1,k);
}
int kthSmallest(vector<int>& nums, int k) { return quickselect(nums,0,nums.size()-1,k-1); }
```
```java
static int quickselect(int[] a, int lo, int hi, int k) {
    int pivot=a[hi], i=lo;
    for(int j=lo;j<hi;j++) if(a[j]<=pivot){int t=a[i];a[i]=a[j];a[j]=t;i++;}
    int t=a[i];a[i]=a[hi];a[hi]=t;
    if(i==k)return a[i];
    return i<k?quickselect(a,i+1,hi,k):quickselect(a,lo,i-1,k);
}
```
**Average O(n), worst O(n²).**

---

### 9. Merge Sort — Count Inversions
**Problem:** Count pairs (i,j) where i < j but arr[i] > arr[j].
**Relevance:** Measures how "unsorted" data is. Used in recommendation engines and ranking.

```cpp
long long mergeCount(vector<int>& a, int lo, int hi) {
    if (lo>=hi) return 0;
    int mid=(lo+hi)/2;
    long long count = mergeCount(a,lo,mid) + mergeCount(a,mid+1,hi);
    vector<int> tmp; int i=lo, j=mid+1;
    while (i<=mid && j<=hi) {
        if (a[i]<=a[j]) tmp.push_back(a[i++]);
        else { tmp.push_back(a[j++]); count += mid-i+1; }
    }
    while (i<=mid) tmp.push_back(a[i++]);
    while (j<=hi) tmp.push_back(a[j++]);
    for (int k=lo;k<=hi;k++) a[k]=tmp[k-lo];
    return count;
}
```
**O(n log n).**

---

### 10. Aggressive Cows / Magnetic Balls
**Problem:** Place k cows in n stalls. Maximize minimum distance between any two cows.
**Approach:** Binary search on answer (minimum distance). Greedy check if placement is feasible.

```cpp
bool canPlace(vector<int>& stalls, int k, int minDist) {
    int count=1, last=stalls[0];
    for (int i=1;i<(int)stalls.size();i++) {
        if (stalls[i]-last>=minDist) { count++; last=stalls[i]; }
        if (count>=k) return true;
    }
    return false;
}
int aggressiveCows(vector<int>& stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int lo=1, hi=stalls.back()-stalls[0], ans=0;
    while (lo<=hi) {
        int mid=lo+(hi-lo)/2;
        if (canPlace(stalls,k,mid)) { ans=mid; lo=mid+1; } else hi=mid-1;
    }
    return ans;
}
```
**O(n log(max_dist)).**

---

## 🔴 HARD PROBLEMS

### 11. Median of Two Sorted Arrays
**Problem:** Find median of two sorted arrays in O(log(min(m,n))).
**Approach:** Binary search on partition of the smaller array.

```cpp
double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
    if (a.size()>b.size()) swap(a,b);
    int m=a.size(), n=b.size(), lo=0, hi=m;
    while (lo<=hi) {
        int i=lo+(hi-lo)/2, j=(m+n+1)/2-i;
        int lA=(i==0?INT_MIN:a[i-1]), rA=(i==m?INT_MAX:a[i]);
        int lB=(j==0?INT_MIN:b[j-1]), rB=(j==n?INT_MAX:b[j]);
        if (lA<=rB && lB<=rA) {
            if ((m+n)%2) return max(lA,lB);
            return (max(lA,lB)+min(rA,rB))/2.0;
        }
        if (lA>rB) hi=i-1; else lo=i+1;
    }
    return 0;
}
```
```java
public static double findMedianSortedArrays(int[] a, int[] b) {
    if (a.length>b.length){int[] t=a;a=b;b=t;}
    int m=a.length,n=b.length,lo=0,hi=m;
    while(lo<=hi){
        int i=lo+(hi-lo)/2, j=(m+n+1)/2-i;
        int lA=i==0?Integer.MIN_VALUE:a[i-1], rA=i==m?Integer.MAX_VALUE:a[i];
        int lB=j==0?Integer.MIN_VALUE:b[j-1], rB=j==n?Integer.MAX_VALUE:b[j];
        if(lA<=rB&&lB<=rA) return (m+n)%2==1?Math.max(lA,lB):(Math.max(lA,lB)+Math.min(rA,rB))/2.0;
        if(lA>rB)hi=i-1;else lo=i+1;
    }
    return 0;
}
```
**O(log(min(m,n))).**

---

### 12. Allocate Minimum Pages
**Problem:** Divide n books among k students minimizing maximum pages any student reads. Each student gets contiguous books.
**Approach:** BS on answer (max pages). Check if allocation is feasible with greedy.

```cpp
bool canAllocate(vector<int>& pages, int k, int maxPages) {
    int students=1, sum=0;
    for (int p:pages) {
        if (p>maxPages) return false;
        if (sum+p>maxPages) { students++; sum=p; } else sum+=p;
    }
    return students<=k;
}
int allocatePages(vector<int>& pages, int k) {
    int lo=*max_element(pages.begin(),pages.end()), hi=accumulate(pages.begin(),pages.end(),0), ans=hi;
    while (lo<=hi) {
        int mid=lo+(hi-lo)/2;
        if (canAllocate(pages,k,mid)) { ans=mid; hi=mid-1; } else lo=mid+1;
    }
    return ans;
}
```
**O(n log(sum)).**

---

### 13. Find in Row-Column Sorted Matrix
**Problem:** Search in matrix where rows and columns are sorted.
**Approach:** Start from top-right. If target < current, go left. If target > current, go down.

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int r=0, c=matrix[0].size()-1;
    while (r<(int)matrix.size() && c>=0) {
        if (matrix[r][c]==target) return true;
        else if (matrix[r][c]>target) c--;
        else r++;
    }
    return false;
}
```
```java
public static boolean searchMatrix(int[][] matrix, int target) {
    int r=0,c=matrix[0].length-1;
    while(r<matrix.length&&c>=0){if(matrix[r][c]==target)return true;else if(matrix[r][c]>target)c--;else r++;}
    return false;
}
```
**O(m + n) time, O(1) space.**

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| Classic Binary Search | BS, Search Insert, Count Occurrences |
| Lower/Upper Bound | First & Last Position, Count Occurrences |
| BS on Answer | Square Root, Aggressive Cows, Allocate Pages |
| Modified BS | Rotated Array, Peak Element |
| BS on Partition | Median of Two Sorted Arrays |
| Quickselect | Kth Smallest |
| Modified Merge Sort | Count Inversions |
| Staircase Search | Row-Column Sorted Matrix |
