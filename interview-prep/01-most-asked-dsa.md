# 🏆 Most Asked DSA Problems (Based on Real Interviews)

> Curated from patterns seen at FAANG, startups, and service companies. Grouped by topic with approach hints.

---

## Arrays & Strings (Most Frequent)

| # | Problem | Key Pattern | Difficulty |
|---|---------|-------------|-----------|
| 1 | Two Sum | Hash Map | Easy |
| 2 | Best Time to Buy & Sell Stock | Track Min | Easy |
| 3 | Contains Duplicate | Hash Set | Easy |
| 4 | Maximum Subarray (Kadane's) | DP/Greedy | Medium |
| 5 | 3Sum | Sort + Two Pointer | Medium |
| 6 | Longest Substring Without Repeat | Sliding Window | Medium |
| 7 | Trapping Rain Water | Two Pointer | Hard |
| 8 | Merge Intervals | Sorting | Medium |

### 📌 Interview Tip
> For array problems, always ask: "Is the array sorted?" This single question determines whether you use binary search or hash maps.

### ⚠️ Common Trap
> Students jump to O(n²) brute force. **Always** ask yourself: "Can a hash map reduce this to O(n)?" before coding.

---

## Linked List

| # | Problem | Key Pattern |
|---|---------|-------------|
| 9 | Reverse Linked List | Iterative 3-pointer |
| 10 | Detect Cycle | Floyd's |
| 11 | Merge Two Sorted Lists | Dummy head |
| 12 | LRU Cache | DLL + HashMap |

### 📌 Interview Tip
> Always clarify: singly or doubly linked? That changes your approach. Always use a **dummy head** node to simplify edge cases.

---

## Stack & Queue

| # | Problem | Key Pattern |
|---|---------|-------------|
| 13 | Valid Parentheses | Stack matching |
| 14 | Min Stack | Auxiliary stack |
| 15 | Largest Rectangle in Histogram | Monotonic stack |
| 16 | Sliding Window Maximum | Monotonic deque |

### ⚠️ Common Trap
> "Next Greater Element" type problems — students try brute force O(n²). The **monotonic stack** pattern gives O(n).

---

## Trees

| # | Problem | Key Pattern |
|---|---------|-------------|
| 17 | Max Depth | DFS |
| 18 | Validate BST | Range check |
| 19 | Lowest Common Ancestor | Recursive DFS |
| 20 | Serialize/Deserialize Tree | Preorder + null markers |
| 21 | Max Path Sum | DFS + global max |

### 📌 Interview Tip
> Most tree problems follow one of two patterns: **top-down** (pass info to children) or **bottom-up** (return info to parent). Identify which before coding.

---

## Graphs

| # | Problem | Key Pattern |
|---|---------|-------------|
| 22 | Number of Islands | DFS/BFS on grid |
| 23 | Course Schedule | Topological sort |
| 24 | Clone Graph | BFS + HashMap |
| 25 | Word Ladder | BFS shortest path |

---

## Dynamic Programming

| # | Problem | Key Pattern |
|---|---------|-------------|
| 26 | Climbing Stairs | 1D DP |
| 27 | Coin Change | Unbounded Knapsack |
| 28 | Longest Common Subsequence | 2D DP |
| 29 | Edit Distance | 2D DP |
| 30 | Longest Increasing Subsequence | DP + Binary Search |

### 📌 Interview Tip
> For DP, always start by defining: "What does dp[i] represent?" If you can't clearly answer this, you don't have the right state yet.

### ⚠️ Common Trap
> Students memorize solutions instead of understanding the 5-step framework (state → base → transition → order → answer). Interviewers ask follow-ups that break memorized solutions.

---

## Strategy for Each Round

| Round | Focus | Time Per Problem |
|-------|-------|-----------------|
| Phone Screen | Easy-Medium from top 15 | 15-20 min |
| Onsite Round 1 | Medium from any topic | 25-30 min |
| Onsite Round 2 | Medium-Hard, often DP/Graph | 30-40 min |
| System Design | Data structures + design | 45 min |
