# 🔙 Backtracking Template

## When to Use
- **Generate all combinations/permutations/subsets**
- **Constraint satisfaction** problems (N-Queens, Sudoku)
- **Search all paths** in a graph/grid
- You need **exhaustive search but with pruning**

## How to Recognize
Keywords: *all combinations*, *all permutations*, *generate all*, *find all valid*, *N-Queens*, *Sudoku*.

## Common Mistakes
1. **Forgetting to undo choice** — the "backtrack" step (`path.pop_back()`, unmark visited)
2. **Not pruning early** — without pruning, backtracking is just brute force
3. **Duplicate results** — sort input + skip duplicates, or use `start` index

---

## Template

```cpp
// C++ — Generic Backtracking
void backtrack(vector<int>& choices, vector<int>& path, 
               vector<vector<int>>& results, int start) {
    
    // Base case: valid solution found
    if (/* solution is complete */) {
        results.push_back(path);
        return;
    }
    
    for (int i = start; i < (int)choices.size(); i++) {
        // Pruning: skip invalid choices
        if (/* choice is invalid */) continue;
        
        // Skip duplicates (if input sorted)
        if (i > start && choices[i] == choices[i-1]) continue;
        
        path.push_back(choices[i]);     // Make choice
        backtrack(choices, path, results, i + 1);  // Recurse
        path.pop_back();                // Undo choice (BACKTRACK)
    }
}
```

```java
public static void backtrack(int[] choices, List<Integer> path,
                             List<List<Integer>> results, int start) {
    if (/* solution complete */) {
        results.add(new ArrayList<>(path));  // Copy!
        return;
    }
    for (int i = start; i < choices.length; i++) {
        if (i > start && choices[i] == choices[i-1]) continue;
        path.add(choices[i]);
        backtrack(choices, path, results, i + 1);
        path.remove(path.size() - 1);  // Backtrack
    }
}
```

---

## Example Problems

### 1. Subsets
**Problem:** Generate all subsets of a set.
**Apply:** At each index, choose to include or exclude. No base-case check needed — every `path` is a valid subset.
```cpp
void subsets(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {
    res.push_back(path);  // Every partial path is a subset
    for (int i = start; i < (int)nums.size(); i++) {
        path.push_back(nums[i]);
        subsets(nums, i+1, path, res);
        path.pop_back();
    }
}
```

### 2. N-Queens
**Problem:** Place N queens on N×N board so no two attack each other.
**Apply:** Place queen row by row. Prune columns and diagonals using sets.

### 3. Combination Sum
**Problem:** Find all combinations that sum to target (can reuse elements).
**Key twist:** Use `i` (not `i+1`) in recursive call to allow reuse.

---

## Backtracking vs Recursion vs DFS

| Concept | Key Difference |
|---------|---------------|
| **Recursion** | General technique of self-calling functions |
| **DFS** | Traversal strategy on graphs/trees |
| **Backtracking** | Recursion + **undo step** to explore all paths |
