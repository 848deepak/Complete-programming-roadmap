# 📚 Stack — Practice Problems

> **Topic:** Stack | **Level:** Easy → Hard | **Focus:** Interview-Ready Patterns

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Valid Parentheses](#1-valid-parentheses) | 🟢 Easy | Stack Matching |
| 2 | [Implement Stack using Queues](#2-implement-stack-using-queues) | 🟢 Easy | Queue Simulation |
| 3 | [Min Stack](#3-min-stack) | 🟢 Easy | Auxiliary Stack |
| 4 | [Reverse a String using Stack](#4-reverse-a-string-using-stack) | 🟢 Easy | LIFO |
| 5 | [Next Greater Element](#5-next-greater-element) | 🟢 Easy | Monotonic Stack |
| 6 | [Evaluate Reverse Polish Notation](#6-evaluate-rpn) | 🟡 Medium | Stack Eval |
| 7 | [Daily Temperatures](#7-daily-temperatures) | 🟡 Medium | Monotonic Stack |
| 8 | [Largest Rectangle in Histogram](#8-largest-rectangle-in-histogram) | 🟡 Medium | Monotonic Stack |
| 9 | [Decode String](#9-decode-string) | 🟡 Medium | Stack Parsing |
| 10 | [Celebrity Problem](#10-celebrity-problem) | 🟡 Medium | Stack Elimination |
| 11 | [Stock Span Problem](#11-stock-span-problem) | 🔴 Hard | Monotonic Stack |
| 12 | [Max Rectangle in Binary Matrix](#12-max-rectangle-in-binary-matrix) | 🔴 Hard | Histogram+Stack |
| 13 | [Expression Evaluation (Infix)](#13-expression-evaluation) | 🔴 Hard | Two Stack |

---

## 🟢 EASY PROBLEMS

### 1. Valid Parentheses

**Problem:** Given `()[]{}`, check if brackets close in correct order.
**Relevance:** Compiler syntax validation, IDE bracket highlighting.
**Edge Cases:** Empty string → true. Only open brackets → false.

```cpp
// C++
bool isValid(string s) {
    stack<char> st;
    unordered_map<char,char> m = {{')',('('}, {']','['}, {'}','{'}};
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else { if (st.empty() || st.top() != m[c]) return false; st.pop(); }
    }
    return st.empty();
}
```
```java
// Java
public static boolean isValid(String s) {
    Deque<Character> st = new ArrayDeque<>();
    Map<Character,Character> m = Map.of(')', '(', ']', '[', '}', '{');
    for (char c : s.toCharArray()) {
        if ("([{".indexOf(c) >= 0) st.push(c);
        else { if (st.isEmpty() || st.peek() != m.get(c)) return false; st.pop(); }
    }
    return st.isEmpty();
}
```
**Complexity:** O(n) time, O(n) space.

---

### 2. Implement Stack using Queues

**Problem:** Build LIFO stack using only queue operations.
**Approach:** On push(x), enqueue x then rotate all previous elements behind it.

```cpp
class MyStack {
    queue<int> q;
public:
    void push(int x) {
        q.push(x);
        for (int i = 0; i < (int)q.size()-1; i++) { q.push(q.front()); q.pop(); }
    }
    int pop()  { int t = q.front(); q.pop(); return t; }
    int top()  { return q.front(); }
    bool empty(){ return q.empty(); }
};
```
```java
class MyStack {
    Queue<Integer> q = new LinkedList<>();
    public void push(int x) {
        q.offer(x);
        for (int i = 0; i < q.size()-1; i++) q.offer(q.poll());
    }
    public int pop() { return q.poll(); }
    public int top() { return q.peek(); }
}
```
**Complexity:** Push O(n), Pop/Top O(1).

---

### 3. Min Stack

**Problem:** Stack with O(1) `getMin()`.
**Approach:** Maintain auxiliary `minStack` — push when value ≤ current min.

```cpp
class MinStack {
    stack<int> main_st, min_st;
public:
    void push(int v) { main_st.push(v); if (min_st.empty() || v <= min_st.top()) min_st.push(v); }
    void pop() { if (main_st.top() == min_st.top()) min_st.pop(); main_st.pop(); }
    int top()    { return main_st.top(); }
    int getMin() { return min_st.top(); }
};
```
```java
class MinStack {
    Deque<Integer> s = new ArrayDeque<>(), m = new ArrayDeque<>();
    void push(int v) { s.push(v); if (m.isEmpty() || v <= m.peek()) m.push(v); }
    void pop() { if (s.peek().equals(m.peek())) m.pop(); s.pop(); }
    int top() { return s.peek(); }
    int getMin() { return m.peek(); }
}
```
**Complexity:** All operations O(1).

---

### 4. Reverse a String using Stack

**Problem:** Use LIFO property to reverse a string.

```cpp
string reverseStr(string s) {
    stack<char> st;
    for (char c : s) st.push(c);
    string r; while (!st.empty()) { r += st.top(); st.pop(); }
    return r;
}
```
```java
public static String reverse(String s) {
    Deque<Character> st = new ArrayDeque<>();
    for (char c : s.toCharArray()) st.push(c);
    StringBuilder sb = new StringBuilder();
    while (!st.isEmpty()) sb.append(st.pop());
    return sb.toString();
}
```
**Complexity:** O(n) time, O(n) space.

---

### 5. Next Greater Element

**Problem:** For each element, find next greater element to its right. Return -1 if none.
```
Input:  [4, 5, 2, 10, 8]  →  Output: [5, 10, 10, -1, -1]
```
**Relevance:** Stock market "next higher price day", weather "next warmer day".
**Approach:** Monotonic stack, traverse right-to-left.

```cpp
vector<int> nextGreater(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = n-1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] <= nums[i]) st.pop();
        if (!st.empty()) res[i] = nums[st.top()];
        st.push(i);
    }
    return res;
}
```
```java
public static int[] nextGreater(int[] nums) {
    int n = nums.length; int[] res = new int[n]; Arrays.fill(res, -1);
    Deque<Integer> st = new ArrayDeque<>();
    for (int i = n-1; i >= 0; i--) {
        while (!st.isEmpty() && nums[st.peek()] <= nums[i]) st.pop();
        if (!st.isEmpty()) res[i] = nums[st.peek()];
        st.push(i);
    }
    return res;
}
```
**Complexity:** O(n) amortized time, O(n) space.

---

## 🟡 MEDIUM PROBLEMS

### 6. Evaluate RPN

**Problem:** Evaluate postfix expression. `["2","1","+","3","*"]` → 9.
**Relevance:** JVM/Python bytecode evaluation, calculator engines.

```cpp
int evalRPN(vector<string>& tokens) {
    stack<long long> st;
    for (auto& t : tokens) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            long long b = st.top(); st.pop(); long long a = st.top(); st.pop();
            if (t=="+") st.push(a+b); else if (t=="-") st.push(a-b);
            else if (t=="*") st.push(a*b); else st.push(a/b);
        } else st.push(stoll(t));
    }
    return st.top();
}
```
```java
public static int evalRPN(String[] tokens) {
    Deque<Long> st = new ArrayDeque<>();
    for (String t : tokens) {
        if ("+-*/".contains(t) && t.length() == 1) {
            long b = st.pop(), a = st.pop();
            st.push(switch(t) { case "+"->a+b; case "-"->a-b; case "*"->a*b; default->a/b; });
        } else st.push(Long.parseLong(t));
    }
    return st.pop().intValue();
}
```
**Complexity:** O(n) time, O(n) space.

---

### 7. Daily Temperatures

**Problem:** Days until warmer temperature. `[73,74,75,71,69,72,76,73]` → `[1,1,4,2,1,1,0,0]`.
**Approach:** Monotonic decreasing stack of indices.

```cpp
vector<int> dailyTemperatures(vector<int>& T) {
    int n = T.size(); vector<int> ans(n, 0); stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && T[i] > T[st.top()]) { ans[st.top()] = i - st.top(); st.pop(); }
        st.push(i);
    }
    return ans;
}
```
```java
public static int[] dailyTemperatures(int[] T) {
    int n = T.length; int[] ans = new int[n]; Deque<Integer> st = new ArrayDeque<>();
    for (int i = 0; i < n; i++) {
        while (!st.isEmpty() && T[i] > T[st.peek()]) { int j = st.pop(); ans[j] = i-j; }
        st.push(i);
    }
    return ans;
}
```
**Complexity:** O(n) time, O(n) space.

---

### 8. Largest Rectangle in Histogram

**Problem:** Find largest rectangle area in a bar chart. `[2,1,5,6,2,3]` → 10.
**Relevance:** Billboard placement, skyline analysis, computational geometry.
**Approach:** Monotonic increasing stack. Sentinel 0 at end flushes remaining bars.

```cpp
int largestRectangle(vector<int>& h) {
    stack<int> st; int maxA = 0, n = h.size();
    for (int i = 0; i <= n; i++) {
        int cur = (i == n) ? 0 : h[i];
        while (!st.empty() && cur < h[st.top()]) {
            int ht = h[st.top()]; st.pop();
            int w = st.empty() ? i : i - st.top() - 1;
            maxA = max(maxA, ht * w);
        }
        st.push(i);
    }
    return maxA;
}
```
```java
public static int largestRectangle(int[] h) {
    Deque<Integer> st = new ArrayDeque<>(); int maxA = 0, n = h.length;
    for (int i = 0; i <= n; i++) {
        int cur = (i == n) ? 0 : h[i];
        while (!st.isEmpty() && cur < h[st.peek()]) {
            int ht = h[st.pop()]; int w = st.isEmpty() ? i : i - st.peek() - 1;
            maxA = Math.max(maxA, ht * w);
        }
        st.push(i);
    }
    return maxA;
}
```
**Complexity:** O(n) time, O(n) space.

---

### 9. Decode String

**Problem:** `"3[a2[c]]"` → `"accaccacc"`. Nested bracket decoding.
**Relevance:** RLE decoding, template expansion.
**Approach:** Two stacks — one for counts, one for partial strings.

```cpp
string decodeString(string s) {
    stack<int> counts; stack<string> strs; string cur; int k = 0;
    for (char c : s) {
        if (isdigit(c)) k = k*10+(c-'0');
        else if (c == '[') { counts.push(k); k=0; strs.push(cur); cur=""; }
        else if (c == ']') {
            int rep = counts.top(); counts.pop();
            string prev = strs.top(); strs.pop();
            for (int i = 0; i < rep; i++) prev += cur;
            cur = prev;
        } else cur += c;
    }
    return cur;
}
```
```java
public static String decodeString(String s) {
    Deque<Integer> counts = new ArrayDeque<>();
    Deque<String> strs = new ArrayDeque<>();
    StringBuilder cur = new StringBuilder(); int k = 0;
    for (char c : s.toCharArray()) {
        if (Character.isDigit(c)) k = k*10+(c-'0');
        else if (c == '[') { counts.push(k); k=0; strs.push(cur.toString()); cur = new StringBuilder(); }
        else if (c == ']') {
            int rep = counts.pop(); String prev = strs.pop();
            String chunk = cur.toString(); cur = new StringBuilder(prev);
            for (int i = 0; i < rep; i++) cur.append(chunk);
        } else cur.append(c);
    }
    return cur.toString();
}
```
**Complexity:** O(output length).

---

### 10. Celebrity Problem

**Problem:** Among n people, find celebrity (known by all, knows nobody). Uses `knows(a,b)`.
**Approach:** Stack elimination — compare two at a time, eliminate non-celebrity.

```cpp
int findCelebrity(int n) {
    stack<int> st;
    for (int i = 0; i < n; i++) st.push(i);
    while (st.size() > 1) {
        int a = st.top(); st.pop(); int b = st.top(); st.pop();
        st.push(knows(a, b) ? b : a);
    }
    int c = st.top();
    for (int i = 0; i < n; i++)
        if (i != c && (knows(c, i) || !knows(i, c))) return -1;
    return c;
}
```
```java
public static int findCelebrity(int n) {
    Deque<Integer> st = new ArrayDeque<>();
    for (int i = 0; i < n; i++) st.push(i);
    while (st.size() > 1) { int a = st.pop(), b = st.pop(); st.push(knows(a,b)?b:a); }
    int c = st.pop();
    for (int i = 0; i < n; i++)
        if (i != c && (knows(c, i) || !knows(i, c))) return -1;
    return c;
}
```
**Complexity:** O(n) time, O(n) space.

---

## 🔴 HARD PROBLEMS

### 11. Stock Span Problem

**Problem:** For each day, count consecutive prior days with price ≤ today.
```
[100, 80, 60, 70, 60, 75, 85] → [1, 1, 1, 2, 1, 4, 6]
```
**Relevance:** RSI computation, momentum indicators in trading.
**Approach:** Monotonic stack of (price, span) pairs. Collapse entries with price ≤ current.

```cpp
vector<int> stockSpan(vector<int>& prices) {
    int n = prices.size(); vector<int> span(n);
    stack<pair<int,int>> st;
    for (int i = 0; i < n; i++) {
        int s = 1;
        while (!st.empty() && st.top().first <= prices[i]) { s += st.top().second; st.pop(); }
        span[i] = s; st.push({prices[i], s});
    }
    return span;
}
```
```java
public static int[] stockSpan(int[] prices) {
    int n = prices.length; int[] span = new int[n];
    Deque<int[]> st = new ArrayDeque<>();
    for (int i = 0; i < n; i++) {
        int s = 1;
        while (!st.isEmpty() && st.peek()[0] <= prices[i]) s += st.pop()[1];
        span[i] = s; st.push(new int[]{prices[i], s});
    }
    return span;
}
```
**Complexity:** O(n) amortized.

---

### 12. Max Rectangle in Binary Matrix

**Problem:** Largest rectangle of 1s in a binary matrix. Extension of histogram problem.
**Approach:** Build histogram row-by-row, apply Largest Rectangle in Histogram on each.

```cpp
int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int cols = matrix[0].size(); vector<int> h(cols, 0); int maxA = 0;
    for (auto& row : matrix) {
        for (int c = 0; c < cols; c++) h[c] = (row[c]=='1') ? h[c]+1 : 0;
        maxA = max(maxA, largestRectangle(h));  // reuse histogram function
    }
    return maxA;
}
```
```java
public static int maximalRectangle(char[][] matrix) {
    if (matrix.length == 0) return 0;
    int cols = matrix[0].length, maxA = 0; int[] h = new int[cols];
    for (char[] row : matrix) {
        for (int c = 0; c < cols; c++) h[c] = (row[c]=='1') ? h[c]+1 : 0;
        maxA = Math.max(maxA, largestRectangle(h));
    }
    return maxA;
}
```
**Complexity:** O(rows × cols) time, O(cols) space.

---

### 13. Expression Evaluation

**Problem:** Evaluate infix: `"3+5*2"` → 13, `"(3+5)*2"` → 16.
**Relevance:** Calculator engines, spreadsheet formulas, compiler front-ends.
**Approach:** Two stacks (values + operators), apply by precedence.

```cpp
int applyOp(int a, int b, char op) {
    if (op=='+') return a+b; if (op=='-') return a-b;
    if (op=='*') return a*b; return a/b;
}
int prec(char op) { return (op=='+'||op=='-') ? 1 : (op=='*'||op=='/') ? 2 : 0; }

int evaluate(const string& expr) {
    stack<int> vals; stack<char> ops;
    for (int i = 0; i < (int)expr.size(); i++) {
        if (isspace(expr[i])) continue;
        if (isdigit(expr[i])) {
            int n = 0; while (i < (int)expr.size() && isdigit(expr[i])) n = n*10+(expr[i++]-'0');
            i--; vals.push(n);
        } else if (expr[i] == '(') ops.push('(');
        else if (expr[i] == ')') {
            while (ops.top()!='(') { int b=vals.top();vals.pop();int a=vals.top();vals.pop(); vals.push(applyOp(a,b,ops.top()));ops.pop(); }
            ops.pop();
        } else {
            while (!ops.empty() && prec(ops.top()) >= prec(expr[i])) { int b=vals.top();vals.pop();int a=vals.top();vals.pop(); vals.push(applyOp(a,b,ops.top()));ops.pop(); }
            ops.push(expr[i]);
        }
    }
    while (!ops.empty()) { int b=vals.top();vals.pop();int a=vals.top();vals.pop(); vals.push(applyOp(a,b,ops.top()));ops.pop(); }
    return vals.top();
}
```
```java
public static int evaluate(String expr) {
    Deque<Integer> vals = new ArrayDeque<>(); Deque<Character> ops = new ArrayDeque<>();
    for (int i = 0; i < expr.length(); i++) {
        char c = expr.charAt(i); if (c==' ') continue;
        if (Character.isDigit(c)) {
            int n = 0; while (i<expr.length()&&Character.isDigit(expr.charAt(i))) n=n*10+(expr.charAt(i++)-'0');
            i--; vals.push(n);
        } else if (c=='(') ops.push(c);
        else if (c==')') {
            while(ops.peek()!='('){int b=vals.pop(),a=vals.pop();vals.push(applyOp(a,b,ops.pop()));}ops.pop();
        } else {
            while(!ops.isEmpty()&&prec(ops.peek())>=prec(c)){int b=vals.pop(),a=vals.pop();vals.push(applyOp(a,b,ops.pop()));}
            ops.push(c);
        }
    }
    while(!ops.isEmpty()){int b=vals.pop(),a=vals.pop();vals.push(applyOp(a,b,ops.pop()));}
    return vals.pop();
}
```
**Complexity:** O(n) time, O(n) space.

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| Monotonic Stack | Next Greater, Daily Temps, Histogram, Stock Span |
| Auxiliary Stack | Min Stack |
| Two Stack | Expression Eval, Decode String |
| Stack Matching | Valid Parentheses |
| Stack Elimination | Celebrity Problem |
| Histogram Extension | Max Rectangle in Binary Matrix |
