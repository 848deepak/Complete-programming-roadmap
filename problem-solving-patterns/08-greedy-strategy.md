# 💰 Greedy Strategy Framework

## When to Use
- Making the **locally optimal choice** leads to a **globally optimal solution**
- Problem has **greedy choice property** + **optimal substructure**
- Sorting the input often reveals the greedy strategy

## How to Recognize
Keywords: *minimum number of*, *maximum number of*, *earliest/latest*, *interval scheduling*, *coins/change*.

## Common Mistakes
1. **Assuming greedy works without proof** — not all optimization problems are greedy-solvable
2. **Wrong sorting criterion** — sort by end time for intervals, by weight/value ratio for knapsack
3. **Not considering all greedy choices** — sometimes you need to try greedy from both directions

---

## Template

```cpp
// C++ — Generic Greedy Template
int greedySolve(vector<Item>& items) {
    // Step 1: Sort by greedy criterion
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        return a.greedyKey < b.greedyKey;
    });
    
    // Step 2: Iterate and make locally optimal choice
    int result = 0;
    State state = initialState;
    
    for (auto& item : items) {
        if (canChoose(item, state)) {
            result += item.value;
            updateState(state, item);
        }
    }
    return result;
}
```

---

## Example Problems

### 1. Activity Selection / Interval Scheduling
**Problem:** Maximum non-overlapping intervals. **Greedy:** Sort by end time, pick earliest-ending.
```cpp
int maxActivities(vector<pair<int,int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b){ return a.second < b.second; });
    int count = 1, lastEnd = intervals[0].second;
    for (int i = 1; i < (int)intervals.size(); i++) {
        if (intervals[i].first >= lastEnd) { count++; lastEnd = intervals[i].second; }
    }
    return count;
}
```

### 2. Fractional Knapsack
**Problem:** Maximize value with weight limit. Items can be fractioned.
**Greedy:** Sort by value/weight ratio descending. Take as much as possible of each.

### 3. Jump Game
**Problem:** Can you reach the last index? Each element = max jump length.
**Greedy:** Track farthest reachable index. If current index > farthest → stuck.
```cpp
bool canJump(vector<int>& nums) {
    int farthest = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > farthest) return false;
        farthest = max(farthest, i + nums[i]);
    }
    return true;
}
```

---

## Greedy vs DP Decision Guide

| Question | If YES → |
|----------|---------|
| Does locally optimal always lead to globally optimal? | Greedy |
| Are there overlapping subproblems? | DP |
| Can you prove the greedy choice property? | Greedy |
| Does choosing an option affect future choices unpredictably? | DP |
