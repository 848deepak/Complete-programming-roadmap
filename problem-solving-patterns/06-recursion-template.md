# 🔄 Recursion Template

## When to Use
- Problem can be broken into **smaller identical subproblems**
- **Tree/graph traversal** (inherently recursive)
- **Mathematical recurrences** (factorial, Fibonacci, power)
- Problems with **nested structure** (parentheses, directories)

## How to Recognize
Keywords: *compute recursively*, *nested*, *self-similar*, *tree structure*, *subproblem*.

## Common Mistakes
1. **Missing base case** → infinite recursion, stack overflow
2. **Redundant computation** → add memoization for overlapping subproblems
3. **Not trusting the recursion** — trying to trace every call instead of reasoning about one level

---

## Template — The 3-Step Framework

```
1. BASE CASE:    What is the simplest input? Return directly.
2. RECURSIVE CASE: Break problem into smaller version(s) of itself.
3. COMBINE:      Merge subproblem results into final answer.
```

```cpp
// C++ — Generic recursion template
ReturnType solve(InputType input) {
    // Step 1: Base case
    if (isBaseCase(input)) {
        return baseCaseResult;
    }
    
    // Step 2: Recursive call(s) on smaller input
    ReturnType subResult = solve(smallerInput(input));
    
    // Step 3: Combine and return
    return combine(input, subResult);
}
```

## Template — With Memoization

```cpp
unordered_map<int, int> memo;

int solve(int n) {
    if (n <= 1) return n;                    // Base case
    if (memo.count(n)) return memo[n];       // Already computed
    memo[n] = solve(n-1) + solve(n-2);      // Compute + store
    return memo[n];
}
```

```java
Map<Integer, Integer> memo = new HashMap<>();

int solve(int n) {
    if (n <= 1) return n;
    if (memo.containsKey(n)) return memo.get(n);
    int result = solve(n-1) + solve(n-2);
    memo.put(n, result);
    return result;
}
```

---

## Example Problems

### 1. Tower of Hanoi
**Problem:** Move n disks from source to target using auxiliary peg.
```cpp
void hanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoi(n-1, from, aux, to);         // Move n-1 to auxiliary
    cout << from << " → " << to << "\n"; // Move largest disk
    hanoi(n-1, aux, to, from);         // Move n-1 from auxiliary to target
}
```

### 2. Generate All Parentheses
**Problem:** Generate all valid combinations of n pairs of parentheses.
**Base:** open==n && close==n. **Recurse:** add '(' if open < n, add ')' if close < open.

### 3. Power Function (x^n)
**Problem:** Compute x^n efficiently in O(log n).
```cpp
double myPow(double x, long n) {
    if (n == 0) return 1;
    if (n < 0) { x = 1/x; n = -n; }
    double half = myPow(x, n/2);
    return (n % 2 == 0) ? half * half : half * half * x;
}
```

---

## Recursion → Iteration Conversion

| Recursion Type | Iterative Equivalent |
|---------------|---------------------|
| Tail recursion | Simple loop |
| Linear recursion | Stack-based iteration |
| Tree recursion | Explicit stack or BFS queue |
| Memoized recursion | Bottom-up DP table |
