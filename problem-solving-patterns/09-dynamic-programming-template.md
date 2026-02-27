# 📊 Dynamic Programming Template

## When to Use
- Problem has **overlapping subproblems** (same computation repeated)
- Problem has **optimal substructure** (optimal solution built from optimal sub-solutions)
- Counting paths, maximizing/minimizing values, string matching

## How to Recognize
Keywords: *minimum/maximum*, *count ways*, *is it possible*, *longest/shortest*, *can you reach*.

## Common Mistakes
1. **Wrong state definition** — state must capture ALL information needed for future decisions
2. **Wrong transition** — recurrence must cover ALL ways to reach current state
3. **Wrong base case** — dp[0] initialization errors cause cascading wrong answers
4. **Forgetting to consider "not taking"** — in knapsack-like problems

---

## 5-Step DP Framework

```
1. DEFINE STATE:    What does dp[i] (or dp[i][j]) represent?
2. BASE CASE:      What are the trivial values?
3. TRANSITION:     How does dp[i] relate to previous states?
4. ORDER:          In which order to fill the table?
5. ANSWER:         Where in the table is the final answer?
```

## Template — 1D DP

```cpp
// C++ — 1D DP (e.g., Climbing Stairs, House Robber)
int solve1D(vector<int>& data) {
    int n = data.size();
    vector<int> dp(n + 1, 0);
    
    // Base cases
    dp[0] = baseValue0;
    dp[1] = baseValue1;
    
    // Fill table
    for (int i = 2; i <= n; i++) {
        dp[i] = transition(dp[i-1], dp[i-2], data[i-1]);
    }
    return dp[n];
}

// Space-optimized (when only last 2 states matter)
int solve1D_optimized(vector<int>& data) {
    int prev2 = base0, prev1 = base1;
    for (int i = 2; i <= (int)data.size(); i++) {
        int curr = transition(prev1, prev2, data[i-1]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

## Template — 2D DP

```cpp
// C++ — 2D DP (e.g., LCS, Knapsack, Edit Distance)
int solve2D(string& a, string& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Base cases (first row and first column)
    for (int i = 0; i <= m; i++) dp[i][0] = baseCaseRow(i);
    for (int j = 0; j <= n; j++) dp[0][j] = baseCaseCol(j);
    
    // Fill table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;  // Match
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);  // No match
            }
        }
    }
    return dp[m][n];
}
```

```java
// Java — 2D DP
public static int solve2D(String a, String b) {
    int m = a.length(), n = b.length();
    int[][] dp = new int[m + 1][n + 1];
    for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) {
        if (a.charAt(i-1) == b.charAt(j-1)) dp[i][j] = dp[i-1][j-1] + 1;
        else dp[i][j] = Math.max(dp[i-1][j], dp[i][j-1]);
    }
    return dp[m][n];
}
```

---

## Example Problems

### 1. Coin Change (Unbounded Knapsack)
**State:** dp[amount] = min coins to make amount. **Transition:** dp[i] = min(dp[i-coin]+1) for each coin.

### 2. Longest Common Subsequence
**State:** dp[i][j] = LCS of first i chars of A and first j chars of B.

### 3. Edit Distance
**State:** dp[i][j] = min edits to convert A[0..i-1] to B[0..j-1].
**Transition:** Match → dp[i-1][j-1]. Insert/Delete/Replace → 1 + min(three options).

---

## Top-Down vs Bottom-Up

| Approach | Pros | Cons |
|---------|------|------|
| **Top-Down (Memo)** | Intuitive, only computes needed states | Recursion overhead, stack limits |
| **Bottom-Up (Tab)** | No recursion, easier to optimize space | Must determine order, computes all states |

## DP Pattern Classification

| Pattern | Example | Key Feature |
|---------|---------|-------------|
| Fibonacci-type | Stairs, House Robber | dp[i] depends on dp[i-1], dp[i-2] |
| Knapsack | 0/1 Knapsack, Coin Change | Take or skip items |
| String DP | LCS, Edit Distance | Two-string comparison |
| Grid DP | Unique Paths, Min Path Sum | Move right/down |
| Interval DP | Matrix Chain, Palindrome | dp[i][j] over range [i,j] |
