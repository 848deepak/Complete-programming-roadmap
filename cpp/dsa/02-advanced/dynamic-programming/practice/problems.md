# 📈 Dynamic Programming — Practice Problems

> **Topic:** Dynamic Programming | **Level:** Easy → Hard

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Fibonacci (Memoization vs Tabulation)](#1-fibonacci) | 🟢 Easy | Basic DP |
| 2 | [Climbing Stairs](#2-climbing-stairs) | 🟢 Easy | 1D DP |
| 3 | [House Robber](#3-house-robber) | 🟢 Easy | 1D DP |
| 4 | [Min Cost Climbing Stairs](#4-min-cost-stairs) | 🟢 Easy | 1D DP |
| 5 | [Pascal's Triangle](#5-pascals-triangle) | 🟢 Easy | 2D DP |
| 6 | [Longest Common Subsequence](#6-lcs) | 🟡 Medium | 2D DP |
| 7 | [0/1 Knapsack](#7-knapsack) | 🟡 Medium | 2D DP |
| 8 | [Coin Change](#8-coin-change) | 🟡 Medium | Unbounded Knapsack |
| 9 | [Longest Increasing Subsequence](#9-lis) | 🟡 Medium | 1D DP / Binary Search |
| 10 | [Unique Paths](#10-unique-paths) | 🟡 Medium | 2D DP |
| 11 | [Edit Distance](#11-edit-distance) | 🔴 Hard | 2D DP |
| 12 | [Longest Palindromic Subsequence](#12-lps) | 🔴 Hard | 2D DP (LCS variant) |
| 13 | [Matrix Chain Multiplication](#13-mcm) | 🔴 Hard | Interval DP |

---

## 🟢 EASY

### 1. Fibonacci
```cpp
// Top-down (Memoization)
int fib(int n, vector<int>& memo) {
    if (n<=1) return n; if (memo[n]!=-1) return memo[n];
    return memo[n] = fib(n-1,memo)+fib(n-2,memo);
}
// Bottom-up (Tabulation) — O(1) space
int fib(int n) { if(n<=1) return n; int a=0,b=1;
    for(int i=2;i<=n;i++){int c=a+b;a=b;b=c;} return b; }
```
```java
public static int fib(int n) { if(n<=1)return n; int a=0,b=1;
    for(int i=2;i<=n;i++){int c=a+b;a=b;b=c;}return b; }
```

### 2. Climbing Stairs
**Problem:** n stairs, can climb 1 or 2 at a time. Count ways.
```cpp
int climbStairs(int n) { if(n<=2)return n; int a=1,b=2;
    for(int i=3;i<=n;i++){int c=a+b;a=b;b=c;} return b; }
```

### 3. House Robber
**Problem:** Can't rob adjacent houses. Maximize stolen amount.
```cpp
int rob(vector<int>& nums) {
    int prev2=0,prev1=0;
    for (int n:nums) { int curr=max(prev1,prev2+n); prev2=prev1; prev1=curr; }
    return prev1;
}
```
```java
public static int rob(int[] nums) { int p2=0,p1=0;
    for(int n:nums){int c=Math.max(p1,p2+n);p2=p1;p1=c;} return p1; }
```

### 4. Min Cost Climbing Stairs
```cpp
int minCostClimbingStairs(vector<int>& cost) {
    int a=0,b=0;
    for (int i=2;i<=(int)cost.size();i++) { int c=min(b+cost[i-1],a+cost[i-2]); a=b; b=c; }
    return b;
}
```

### 5. Pascal's Triangle
```cpp
vector<vector<int>> generate(int n) {
    vector<vector<int>> res;
    for (int i=0;i<n;i++) {
        vector<int> row(i+1,1);
        for (int j=1;j<i;j++) row[j]=res[i-1][j-1]+res[i-1][j];
        res.push_back(row);
    }
    return res;
}
```

---

## 🟡 MEDIUM

### 6. Longest Common Subsequence
```cpp
int lcs(string& a, string& b) {
    int m=a.size(),n=b.size(); vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for (int i=1;i<=m;i++) for (int j=1;j<=n;j++)
        dp[i][j] = (a[i-1]==b[j-1]) ? dp[i-1][j-1]+1 : max(dp[i-1][j],dp[i][j-1]);
    return dp[m][n];
}
```
```java
public static int lcs(String a, String b) {
    int m=a.length(),n=b.length(); int[][] dp=new int[m+1][n+1];
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++)
        dp[i][j]=a.charAt(i-1)==b.charAt(j-1)?dp[i-1][j-1]+1:Math.max(dp[i-1][j],dp[i][j-1]);
    return dp[m][n];
}
```
**O(m×n).**

### 7. 0/1 Knapsack
```cpp
int knapsack(vector<int>& wt, vector<int>& val, int W) {
    int n=wt.size(); vector<vector<int>> dp(n+1,vector<int>(W+1,0));
    for (int i=1;i<=n;i++) for (int w=0;w<=W;w++) {
        dp[i][w]=dp[i-1][w];
        if (wt[i-1]<=w) dp[i][w]=max(dp[i][w], dp[i-1][w-wt[i-1]]+val[i-1]);
    }
    return dp[n][W];
}
```
**O(n×W).**

### 8. Coin Change
**Problem:** Minimum coins to make amount. `coins=[1,5,11], amount=15 → 3` (5+5+5).

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, INT_MAX); dp[0]=0;
    for (int i=1;i<=amount;i++) for (int c:coins)
        if (c<=i && dp[i-c]!=INT_MAX) dp[i]=min(dp[i],dp[i-c]+1);
    return dp[amount]==INT_MAX?-1:dp[amount];
}
```
```java
public static int coinChange(int[] coins, int amount) {
    int[] dp = new int[amount+1]; Arrays.fill(dp,amount+1); dp[0]=0;
    for(int i=1;i<=amount;i++) for(int c:coins) if(c<=i) dp[i]=Math.min(dp[i],dp[i-c]+1);
    return dp[amount]>amount?-1:dp[amount];
}
```
**O(n × amount).**

### 9. Longest Increasing Subsequence
```cpp
// O(n log n) using binary search
int lis(vector<int>& nums) {
    vector<int> tails;
    for (int n:nums) {
        auto it = lower_bound(tails.begin(),tails.end(),n);
        if (it==tails.end()) tails.push_back(n);
        else *it=n;
    }
    return tails.size();
}
```
```java
public static int lis(int[] nums) {
    List<Integer> tails = new ArrayList<>();
    for (int n:nums) {
        int pos = Collections.binarySearch(tails,n);
        if (pos<0) pos=-(pos+1);
        if (pos==tails.size()) tails.add(n); else tails.set(pos,n);
    }
    return tails.size();
}
```
**O(n log n).**

### 10. Unique Paths
**Problem:** Robot at (0,0), can move right/down. Count paths to (m-1,n-1).
```cpp
int uniquePaths(int m, int n) {
    vector<int> dp(n,1);
    for (int i=1;i<m;i++) for (int j=1;j<n;j++) dp[j]+=dp[j-1];
    return dp[n-1];
}
```

---

## 🔴 HARD

### 11. Edit Distance
**Problem:** Min edits (insert/delete/replace) to convert word1 → word2.

```cpp
int minDistance(string a, string b) {
    int m=a.size(),n=b.size(); vector<vector<int>> dp(m+1,vector<int>(n+1));
    for (int i=0;i<=m;i++) dp[i][0]=i;
    for (int j=0;j<=n;j++) dp[0][j]=j;
    for (int i=1;i<=m;i++) for (int j=1;j<=n;j++) {
        if (a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1];
        else dp[i][j]=1+min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    }
    return dp[m][n];
}
```
```java
public static int minDistance(String a, String b) {
    int m=a.length(),n=b.length(); int[][] dp=new int[m+1][n+1];
    for(int i=0;i<=m;i++) dp[i][0]=i; for(int j=0;j<=n;j++) dp[0][j]=j;
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++)
        dp[i][j]=a.charAt(i-1)==b.charAt(j-1)?dp[i-1][j-1]:1+Math.min(dp[i-1][j-1],Math.min(dp[i-1][j],dp[i][j-1]));
    return dp[m][n];
}
```
**O(m×n).**

### 12. Longest Palindromic Subsequence
**Trick:** LPS(s) = LCS(s, reverse(s)).

```cpp
int longestPalinSubseq(string s) {
    string t = s; reverse(t.begin(),t.end());
    return lcs(s,t);  // reuse LCS function
}
```

### 13. Matrix Chain Multiplication
**Problem:** Given matrix dimensions, find minimum multiplications needed.
```cpp
int matrixChainMul(vector<int>& dims) {
    int n=dims.size()-1; vector<vector<int>> dp(n,vector<int>(n,0));
    for (int len=2;len<=n;len++) for (int i=0;i<=n-len;i++) {
        int j=i+len-1; dp[i][j]=INT_MAX;
        for (int k=i;k<j;k++)
            dp[i][j]=min(dp[i][j], dp[i][k]+dp[k+1][j]+dims[i]*dims[k+1]*dims[j+1]);
    }
    return dp[0][n-1];
}
```
**O(n³).**

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| 1D DP (Fibonacci style) | Fibonacci, Stairs, House Robber |
| 2D DP (Two strings) | LCS, Edit Distance, LPS |
| Knapsack | 0/1 Knapsack, Coin Change |
| Grid DP | Unique Paths, Min Cost |
| Interval DP | Matrix Chain Multiplication |
| DP + Binary Search | LIS |
