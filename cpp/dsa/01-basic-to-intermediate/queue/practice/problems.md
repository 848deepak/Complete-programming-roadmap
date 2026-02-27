# 🔄 Queue — Practice Problems

> **Topic:** Queue | **Level:** Easy → Hard | **Focus:** Interview-Ready Patterns

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Implement Queue using Stacks](#1-implement-queue-using-stacks) | 🟢 Easy | Stack Sim |
| 2 | [Generate Binary Numbers 1 to N](#2-generate-binary-numbers) | 🟢 Easy | BFS-style |
| 3 | [First Non-Repeating Char in Stream](#3-first-non-repeating-char) | 🟢 Easy | Queue + Freq |
| 4 | [Circular Queue Implementation](#4-circular-queue) | 🟢 Easy | Modular Arith |
| 5 | [Reverse First K Elements of Queue](#5-reverse-first-k) | 🟢 Easy | Stack + Queue |
| 6 | [Sliding Window Maximum](#6-sliding-window-maximum) | 🟡 Medium | Deque |
| 7 | [Rotten Oranges (BFS Grid)](#7-rotten-oranges) | 🟡 Medium | Multi-source BFS |
| 8 | [Design Hit Counter](#8-design-hit-counter) | 🟡 Medium | Queue + Cleanup |
| 9 | [Task Scheduler](#9-task-scheduler) | 🟡 Medium | Greedy + Queue |
| 10 | [Interleave First & Second Half](#10-interleave-halves) | 🟡 Medium | Queue Split |
| 11 | [Shortest Path in Binary Matrix](#11-shortest-path-binary-matrix) | 🔴 Hard | BFS |
| 12 | [Snake and Ladder](#12-snake-and-ladder) | 🔴 Hard | BFS |
| 13 | [Design Circular Deque](#13-design-circular-deque) | 🔴 Hard | Array Circular |

---

## 🟢 EASY PROBLEMS

### 1. Implement Queue using Stacks

**Problem:** Build FIFO queue using only stack operations.
**Approach:** Two stacks (input/output). On dequeue, if output empty, transfer all from input.

```cpp
class MyQueue {
    stack<int> in, out;
    void transfer() { while (!in.empty()) { out.push(in.top()); in.pop(); } }
public:
    void push(int x) { in.push(x); }
    int pop() { if (out.empty()) transfer(); int v = out.top(); out.pop(); return v; }
    int peek() { if (out.empty()) transfer(); return out.top(); }
    bool empty() { return in.empty() && out.empty(); }
};
```
```java
class MyQueue {
    Deque<Integer> in = new ArrayDeque<>(), out = new ArrayDeque<>();
    private void transfer() { while (!in.isEmpty()) out.push(in.pop()); }
    public void push(int x) { in.push(x); }
    public int pop() { if (out.isEmpty()) transfer(); return out.pop(); }
    public int peek() { if (out.isEmpty()) transfer(); return out.peek(); }
    public boolean empty() { return in.isEmpty() && out.isEmpty(); }
}
```
**Complexity:** Amortized O(1) per operation.

---

### 2. Generate Binary Numbers 1 to N

**Problem:** Print binary representations of 1 to N using a queue.
```
N=5 → "1", "10", "11", "100", "101"
```

```cpp
vector<string> genBinary(int n) {
    vector<string> res; queue<string> q; q.push("1");
    for (int i = 0; i < n; i++) {
        string s = q.front(); q.pop();
        res.push_back(s); q.push(s+"0"); q.push(s+"1");
    }
    return res;
}
```
```java
public static List<String> genBinary(int n) {
    List<String> res = new ArrayList<>(); Queue<String> q = new LinkedList<>(); q.add("1");
    for (int i = 0; i < n; i++) {
        String s = q.poll(); res.add(s); q.add(s+"0"); q.add(s+"1");
    }
    return res;
}
```
**Complexity:** O(n).

---

### 3. First Non-Repeating Char in Stream

**Problem:** For each character in a stream, find the first non-repeating character so far.
**Approach:** Queue of candidates + frequency map. Pop from front while freq > 1.

```cpp
string firstNonRepeating(string stream) {
    queue<char> q; int freq[26] = {}; string result;
    for (char c : stream) {
        freq[c-'a']++; q.push(c);
        while (!q.empty() && freq[q.front()-'a'] > 1) q.pop();
        result += q.empty() ? '#' : q.front();
    }
    return result;
}
```
```java
public static String firstNonRepeating(String stream) {
    Queue<Character> q = new LinkedList<>(); int[] freq = new int[26]; StringBuilder sb = new StringBuilder();
    for (char c : stream.toCharArray()) {
        freq[c-'a']++; q.add(c);
        while (!q.isEmpty() && freq[q.peek()-'a'] > 1) q.poll();
        sb.append(q.isEmpty() ? '#' : q.peek());
    }
    return sb.toString();
}
```

---

### 4. Circular Queue Implementation

**Problem:** Implement a fixed-size circular queue with enqueue, dequeue, front, rear, isEmpty, isFull.

```cpp
class CircularQueue {
    vector<int> data; int front, rear, sz, cap;
public:
    CircularQueue(int k) : data(k), front(0), rear(-1), sz(0), cap(k) {}
    bool enqueue(int v) { if (sz==cap) return false; rear=(rear+1)%cap; data[rear]=v; sz++; return true; }
    bool dequeue() { if (sz==0) return false; front=(front+1)%cap; sz--; return true; }
    int getFront() { return sz==0?-1:data[front]; }
    int getRear()  { return sz==0?-1:data[rear]; }
    bool isEmpty()  { return sz==0; }
    bool isFull()   { return sz==cap; }
};
```
```java
class CircularQueue {
    int[] data; int front=0, rear=-1, sz=0, cap;
    CircularQueue(int k) { data = new int[k]; cap = k; }
    boolean enqueue(int v) { if (sz==cap) return false; rear=(rear+1)%cap; data[rear]=v; sz++; return true; }
    boolean dequeue() { if (sz==0) return false; front=(front+1)%cap; sz--; return true; }
    int getFront() { return sz==0?-1:data[front]; }
    int getRear()  { return sz==0?-1:data[rear]; }
}
```

---

### 5. Reverse First K Elements of Queue

**Problem:** Reverse the first K elements of a queue, keeping the rest in order.
**Approach:** Pop K elements onto a stack, push them back, then rotate remaining n-K elements.

```cpp
void reverseFirstK(queue<int>& q, int k) {
    stack<int> st;
    for (int i = 0; i < k; i++) { st.push(q.front()); q.pop(); }
    while (!st.empty()) { q.push(st.top()); st.pop(); }
    int n = q.size() - k;
    for (int i = 0; i < n; i++) { q.push(q.front()); q.pop(); }
}
```
```java
public static void reverseFirstK(Queue<Integer> q, int k) {
    Deque<Integer> st = new ArrayDeque<>();
    for (int i = 0; i < k; i++) st.push(q.poll());
    while (!st.isEmpty()) q.add(st.pop());
    int n = q.size() - k;
    for (int i = 0; i < n; i++) q.add(q.poll());
}
```

---

## 🟡 MEDIUM PROBLEMS

### 6. Sliding Window Maximum

**Problem:** Given array and window size k, find maximum in each sliding window.
```
[1,3,-1,-3,5,3,6,7], k=3 → [3,3,5,5,6,7]
```
**Relevance:** Real-time analytics, network throughput monitoring.
**Approach:** Monotonic deque — maintain decreasing order of values. Front is always the max.

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; vector<int> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        while (!dq.empty() && dq.front() <= i-k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k-1) res.push_back(nums[dq.front()]);
    }
    return res;
}
```
```java
public static int[] maxSlidingWindow(int[] nums, int k) {
    Deque<Integer> dq = new ArrayDeque<>(); int[] res = new int[nums.length-k+1]; int idx=0;
    for (int i = 0; i < nums.length; i++) {
        while (!dq.isEmpty() && dq.peekFirst() <= i-k) dq.pollFirst();
        while (!dq.isEmpty() && nums[dq.peekLast()] <= nums[i]) dq.pollLast();
        dq.addLast(i);
        if (i >= k-1) res[idx++] = nums[dq.peekFirst()];
    }
    return res;
}
```
**Complexity:** O(n) time, O(k) space.

---

### 7. Rotten Oranges

**Problem:** Grid of oranges: 0=empty, 1=fresh, 2=rotten. Each minute, rotten ones infect adjacent fresh ones. Return minutes until all rotten, or -1 if impossible.
**Relevance:** Virus spread simulation, network failure propagation.
**Approach:** Multi-source BFS. Start with all rotten oranges in queue.

```cpp
int orangesRotting(vector<vector<int>>& grid) {
    int rows=grid.size(), cols=grid[0].size(), fresh=0, mins=0;
    queue<pair<int,int>> q;
    for (int r=0;r<rows;r++) for (int c=0;c<cols;c++) {
        if (grid[r][c]==2) q.push({r,c});
        else if (grid[r][c]==1) fresh++;
    }
    int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
    while (!q.empty() && fresh > 0) {
        mins++;
        int sz = q.size();
        while (sz--) {
            auto [r,c] = q.front(); q.pop();
            for (int d=0;d<4;d++) {
                int nr=r+dx[d], nc=c+dy[d];
                if (nr>=0&&nr<rows&&nc>=0&&nc<cols&&grid[nr][nc]==1) {
                    grid[nr][nc]=2; fresh--; q.push({nr,nc});
                }
            }
        }
    }
    return fresh==0 ? mins : -1;
}
```
```java
public static int orangesRotting(int[][] grid) {
    int rows=grid.length, cols=grid[0].length, fresh=0, mins=0;
    Queue<int[]> q = new LinkedList<>();
    for (int r=0;r<rows;r++) for (int c=0;c<cols;c++) {
        if (grid[r][c]==2) q.add(new int[]{r,c});
        else if (grid[r][c]==1) fresh++;
    }
    int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    while (!q.isEmpty() && fresh > 0) {
        mins++; int sz = q.size();
        while (sz-->0) {
            int[] p = q.poll();
            for (int[] d : dirs) {
                int nr=p[0]+d[0], nc=p[1]+d[1];
                if (nr>=0&&nr<rows&&nc>=0&&nc<cols&&grid[nr][nc]==1) {
                    grid[nr][nc]=2; fresh--; q.add(new int[]{nr,nc});
                }
            }
        }
    }
    return fresh==0 ? mins : -1;
}
```
**Complexity:** O(rows × cols).

---

### 8. Design Hit Counter

**Problem:** Count hits in the past 5 minutes. `hit(timestamp)`, `getHits(timestamp)`.
**Approach:** Queue of timestamps. On getHits, remove timestamps older than 300 seconds.

```cpp
class HitCounter {
    queue<int> q;
public:
    void hit(int t) { q.push(t); }
    int getHits(int t) {
        while (!q.empty() && q.front() <= t-300) q.pop();
        return q.size();
    }
};
```
```java
class HitCounter {
    Queue<Integer> q = new LinkedList<>();
    void hit(int t) { q.add(t); }
    int getHits(int t) { while (!q.isEmpty()&&q.peek()<=t-300) q.poll(); return q.size(); }
}
```

---

### 9. Task Scheduler

**Problem:** Given tasks and cooldown n, find minimum intervals to execute all tasks.
```
tasks = ['A','A','A','B','B','B'], n = 2  →  8  (A→B→idle→A→B→idle→A→B)
```

```cpp
int leastInterval(vector<char>& tasks, int n) {
    int freq[26]={}; for (char t:tasks) freq[t-'A']++;
    int maxF = *max_element(freq, freq+26);
    int maxCount = count(freq, freq+26, maxF);
    return max((int)tasks.size(), (maxF-1)*(n+1)+maxCount);
}
```
```java
public static int leastInterval(char[] tasks, int n) {
    int[] freq = new int[26]; for (char t:tasks) freq[t-'A']++;
    int maxF = Arrays.stream(freq).max().getAsInt();
    int maxCount = (int)Arrays.stream(freq).filter(f->f==maxF).count();
    return Math.max(tasks.length, (maxF-1)*(n+1)+maxCount);
}
```
**Complexity:** O(n).

---

### 10. Interleave First & Second Half

**Problem:** `[1,2,3,4,5,6,7,8]` → `[1,5,2,6,3,7,4,8]`. Interleave using a queue.

```cpp
void interleave(queue<int>& q) {
    int half = q.size()/2; queue<int> firstHalf;
    for (int i=0;i<half;i++) { firstHalf.push(q.front()); q.pop(); }
    while (!firstHalf.empty()) { q.push(firstHalf.front()); firstHalf.pop(); q.push(q.front()); q.pop(); }
}
```

---

## 🔴 HARD PROBLEMS

### 11. Shortest Path in Binary Matrix

**Problem:** 0-1 grid, find shortest path from (0,0) to (n-1,n-1) moving 8-directionally.
**Approach:** BFS with 8 directions.

```cpp
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] || grid[n-1][n-1]) return -1;
    queue<tuple<int,int,int>> q; q.push({0,0,1}); grid[0][0]=1;
    int dirs[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
    while (!q.empty()) {
        auto [r,c,d] = q.front(); q.pop();
        if (r==n-1&&c==n-1) return d;
        for (auto& dir:dirs) {
            int nr=r+dir[0], nc=c+dir[1];
            if (nr>=0&&nr<n&&nc>=0&&nc<n&&!grid[nr][nc]) { grid[nr][nc]=1; q.push({nr,nc,d+1}); }
        }
    }
    return -1;
}
```
```java
public static int shortestPathBinaryMatrix(int[][] grid) {
    int n = grid.length; if (grid[0][0]==1||grid[n-1][n-1]==1) return -1;
    Queue<int[]> q = new LinkedList<>(); q.add(new int[]{0,0,1}); grid[0][0]=1;
    int[][] dirs = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
    while (!q.isEmpty()) {
        int[] p = q.poll(); if (p[0]==n-1&&p[1]==n-1) return p[2];
        for (int[] d:dirs) {
            int nr=p[0]+d[0], nc=p[1]+d[1];
            if (nr>=0&&nr<n&&nc>=0&&nc<n&&grid[nr][nc]==0) { grid[nr][nc]=1; q.add(new int[]{nr,nc,p[2]+1}); }
        }
    }
    return -1;
}
```

---

### 12. Snake and Ladder

**Problem:** Min dice throws to reach end of snake-and-ladder board. BFS on board positions.

```cpp
int snakesAndLadders(vector<vector<int>>& board) {
    int n = board.size(); vector<int> flat(n*n+1);
    // Flatten board (boustrophedon order)
    int idx = 1;
    for (int r=n-1;r>=0;r--) {
        if ((n-1-r)%2==0) for (int c=0;c<n;c++) flat[idx++]=board[r][c];
        else for (int c=n-1;c>=0;c--) flat[idx++]=board[r][c];
    }
    vector<bool> visited(n*n+1, false);
    queue<pair<int,int>> q; q.push({1,0}); visited[1]=true;
    while (!q.empty()) {
        auto [pos, moves] = q.front(); q.pop();
        for (int dice=1;dice<=6;dice++) {
            int next = pos+dice; if (next>n*n) continue;
            if (flat[next]!=-1) next = flat[next];
            if (next==n*n) return moves+1;
            if (!visited[next]) { visited[next]=true; q.push({next,moves+1}); }
        }
    }
    return -1;
}
```

---

### 13. Design Circular Deque

**Problem:** Implement double-ended circular queue with insertFront, insertLast, deleteFront, deleteLast.

```cpp
class MyCircularDeque {
    vector<int> data; int front, rear, sz, cap;
public:
    MyCircularDeque(int k) : data(k), front(0), rear(k-1), sz(0), cap(k) {}
    bool insertFront(int v) { if(sz==cap) return false; front=(front-1+cap)%cap; data[front]=v; sz++; return true; }
    bool insertLast(int v) { if(sz==cap) return false; rear=(rear+1)%cap; data[rear]=v; sz++; return true; }
    bool deleteFront() { if(sz==0) return false; front=(front+1)%cap; sz--; return true; }
    bool deleteLast() { if(sz==0) return false; rear=(rear-1+cap)%cap; sz--; return true; }
    int getFront() { return sz==0?-1:data[front]; }
    int getRear() { return sz==0?-1:data[rear]; }
    bool isEmpty() { return sz==0; }
    bool isFull() { return sz==cap; }
};
```
```java
class MyCircularDeque {
    int[] data; int front, rear, sz, cap;
    MyCircularDeque(int k) { data=new int[k]; cap=k; front=0; rear=k-1; sz=0; }
    boolean insertFront(int v) { if(sz==cap)return false; front=(front-1+cap)%cap; data[front]=v; sz++; return true; }
    boolean insertLast(int v) { if(sz==cap)return false; rear=(rear+1)%cap; data[rear]=v; sz++; return true; }
    boolean deleteFront() { if(sz==0)return false; front=(front+1)%cap; sz--; return true; }
    boolean deleteLast() { if(sz==0)return false; rear=(rear-1+cap)%cap; sz--; return true; }
    int getFront() { return sz==0?-1:data[front]; }
    int getRear() { return sz==0?-1:data[rear]; }
}
```

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| Monotonic Deque | Sliding Window Maximum |
| Multi-source BFS | Rotten Oranges, Snake & Ladder |
| BFS Shortest Path | Binary Matrix, Snake & Ladder |
| Two Stack Queue | Implement Queue using Stacks |
| Circular Array | Circular Queue, Circular Deque |
