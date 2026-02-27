# 🏔️ Heap / Priority Queue — Practice Problems

> **Topic:** Min Heap, Max Heap, Priority Queue | **Level:** Easy → Hard

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Kth Largest Element](#1-kth-largest) | 🟢 Easy | Min Heap of size K |
| 2 | [Sort Nearly Sorted Array](#2-sort-nearly-sorted) | 🟢 Easy | Min Heap of size K |
| 3 | [Last Stone Weight](#3-last-stone-weight) | 🟢 Easy | Max Heap |
| 4 | [Check if Array is Min Heap](#4-check-min-heap) | 🟢 Easy | Property Check |
| 5 | [Heap Sort](#5-heap-sort) | 🟢 Easy | Build + Extract |
| 6 | [Top K Frequent Elements](#6-top-k-frequent) | 🟡 Medium | Heap + Map |
| 7 | [K Closest Points to Origin](#7-k-closest) | 🟡 Medium | Max Heap of size K |
| 8 | [Merge K Sorted Lists](#8-merge-k-sorted) | 🟡 Medium | Min Heap |
| 9 | [Running Median (Two Heaps)](#9-running-median) | 🟡 Medium | Max + Min Heap |
| 10 | [Reorganize String](#10-reorganize-string) | 🟡 Medium | Max Heap |
| 11 | [Smallest Range Covering K Lists](#11-smallest-range) | 🔴 Hard | Min Heap |
| 12 | [IPO — Maximize Capital](#12-ipo) | 🔴 Hard | Two Heaps |
| 13 | [Skyline Problem](#13-skyline) | 🔴 Hard | Sweep + Multiset |

---

## 🟢 EASY

### 1. Kth Largest Element
**Approach:** Maintain min-heap of size k. Top is kth largest.

```cpp
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minH;
    for (int n:nums) { minH.push(n); if ((int)minH.size()>k) minH.pop(); }
    return minH.top();
}
```
```java
public static int findKthLargest(int[] nums, int k) {
    PriorityQueue<Integer> minH = new PriorityQueue<>();
    for (int n:nums) { minH.offer(n); if (minH.size()>k) minH.poll(); }
    return minH.peek();
}
```
**O(n log k).**

### 2. Sort Nearly Sorted Array
**Problem:** Each element is at most k positions away from its sorted position.
```cpp
void sortNearlySorted(vector<int>& arr, int k) {
    priority_queue<int,vector<int>,greater<int>> minH;
    int idx=0;
    for (int i=0;i<(int)arr.size();i++) { minH.push(arr[i]);
        if ((int)minH.size()>k) { arr[idx++]=minH.top(); minH.pop(); }
    }
    while (!minH.empty()) { arr[idx++]=minH.top(); minH.pop(); }
}
```
**O(n log k).**

### 3. Last Stone Weight
```cpp
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> maxH(stones.begin(), stones.end());
    while (maxH.size()>1) { int a=maxH.top();maxH.pop(); int b=maxH.top();maxH.pop();
        if (a!=b) maxH.push(a-b);
    }
    return maxH.empty()?0:maxH.top();
}
```

### 4. Check Min Heap Property
```cpp
bool isMinHeap(vector<int>& arr) {
    int n=arr.size();
    for (int i=0;i<n;i++) {
        if (2*i+1<n && arr[i]>arr[2*i+1]) return false;
        if (2*i+2<n && arr[i]>arr[2*i+2]) return false;
    }
    return true;
}
```

### 5. Heap Sort
```cpp
void heapify(vector<int>& a, int n, int i) {
    int largest=i, l=2*i+1, r=2*i+2;
    if (l<n&&a[l]>a[largest]) largest=l;
    if (r<n&&a[r]>a[largest]) largest=r;
    if (largest!=i) { swap(a[i],a[largest]); heapify(a,n,largest); }
}
void heapSort(vector<int>& a) {
    int n=a.size();
    for (int i=n/2-1;i>=0;i--) heapify(a,n,i);
    for (int i=n-1;i>0;i--) { swap(a[0],a[i]); heapify(a,i,0); }
}
```
**O(n log n).**

---

## 🟡 MEDIUM

### 6. Top K Frequent Elements
```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq; for(int n:nums) freq[n]++;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> minH;
    for (auto& [v,c]:freq) { minH.push({c,v}); if((int)minH.size()>k) minH.pop(); }
    vector<int> res; while(!minH.empty()){res.push_back(minH.top().second);minH.pop();}
    return res;
}
```

### 7. K Closest Points to Origin
```cpp
vector<vector<int>> kClosest(vector<vector<int>>& pts, int k) {
    auto cmp=[](auto&a,auto&b){return a[0]*a[0]+a[1]*a[1]<b[0]*b[0]+b[1]*b[1];};
    priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> maxH(cmp);
    for (auto& p:pts) { maxH.push(p); if((int)maxH.size()>k) maxH.pop(); }
    vector<vector<int>> res; while(!maxH.empty()){res.push_back(maxH.top());maxH.pop();}
    return res;
}
```

### 8. Merge K Sorted Lists
*(See Linked List practice #11 for full solution)*

### 9. Running Median (Two Heaps)
**Problem:** Find median after each insertion. Classic two-heap technique.

```cpp
class MedianFinder {
    priority_queue<int> maxH;  // lower half
    priority_queue<int,vector<int>,greater<int>> minH;  // upper half
public:
    void addNum(int num) {
        maxH.push(num);
        minH.push(maxH.top()); maxH.pop();
        if (minH.size()>maxH.size()) { maxH.push(minH.top()); minH.pop(); }
    }
    double findMedian() {
        return maxH.size()>minH.size() ? maxH.top() : (maxH.top()+minH.top())/2.0;
    }
};
```
```java
class MedianFinder {
    PriorityQueue<Integer> maxH = new PriorityQueue<>(Collections.reverseOrder());
    PriorityQueue<Integer> minH = new PriorityQueue<>();
    void addNum(int num) {
        maxH.offer(num); minH.offer(maxH.poll());
        if (minH.size()>maxH.size()) maxH.offer(minH.poll());
    }
    double findMedian() { return maxH.size()>minH.size()?maxH.peek():(maxH.peek()+minH.peek())/2.0; }
}
```
**O(log n) per insert, O(1) query.**

### 10. Reorganize String
**Problem:** Rearrange so no two adjacent characters are the same. `"aab"→"aba"`.

```cpp
string reorganizeString(string s) {
    int freq[26]={}; for(char c:s) freq[c-'a']++;
    priority_queue<pair<int,char>> pq;
    for (int i=0;i<26;i++) if (freq[i]) pq.push({freq[i],(char)('a'+i)});
    string res; pair<int,char> prev={0,' '};
    while (!pq.empty()) {
        auto [cnt,ch]=pq.top(); pq.pop();
        res+=ch;
        if (prev.first>0) pq.push(prev);
        prev={cnt-1,ch};
    }
    return res.size()==s.size()?res:"";
}
```

---

## 🔴 HARD

### 11. Smallest Range Covering K Lists
**Problem:** Find smallest range [a,b] that includes at least one number from each of k sorted lists.
**Approach:** Min heap + track current max. Window = [heap_min, current_max].

```cpp
vector<int> smallestRange(vector<vector<int>>& nums) {
    using T = tuple<int,int,int>; // val, listIdx, elemIdx
    priority_queue<T,vector<T>,greater<T>> minH;
    int curMax = INT_MIN;
    for (int i=0;i<(int)nums.size();i++) { minH.push({nums[i][0],i,0}); curMax=max(curMax,nums[i][0]); }
    int bestL=0, bestR=INT_MAX;
    while (true) {
        auto [val,li,ei]=minH.top(); minH.pop();
        if (curMax-val < bestR-bestL) { bestL=val; bestR=curMax; }
        if (ei+1>=(int)nums[li].size()) break;
        int next=nums[li][ei+1]; minH.push({next,li,ei+1}); curMax=max(curMax,next);
    }
    return {bestL,bestR};
}
```

### 12. IPO — Maximize Capital
**Problem:** Start with capital W. Pick at most k projects each with profit and minimum capital required. Maximize final capital.
**Approach:** Sort by capital. Use max-heap of profits for affordable projects.

```cpp
int findMaximizedCapital(int k, int W, vector<int>& profits, vector<int>& capital) {
    int n=profits.size();
    vector<pair<int,int>> proj(n); for(int i=0;i<n;i++) proj[i]={capital[i],profits[i]};
    sort(proj.begin(),proj.end());
    priority_queue<int> maxH; int idx=0;
    while (k-->0) {
        while (idx<n && proj[idx].first<=W) { maxH.push(proj[idx].second); idx++; }
        if (maxH.empty()) break;
        W+=maxH.top(); maxH.pop();
    }
    return W;
}
```

### 13. Skyline Problem
*(Architecture: sweep line with multiset/priority queue. See detailed competitive programming resources.)*

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| Min Heap of size K | Kth Largest, K Closest |
| Max Heap | Last Stone, Reorganize |
| Two Heaps | Running Median, IPO |
| Heap + Map | Top K Frequent |
| Sort + Heap | Nearly Sorted, Smallest Range |
