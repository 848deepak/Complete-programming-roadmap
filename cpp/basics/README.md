# C++ Basics

> **Folder:** `cpp/basics/` | **Level:** Beginner → Pre-Intermediate  
> **Files:** `01_variables.cpp` · `02_control_flow.cpp` · `03_functions_recursion.cpp` · `04_arrays_strings.cpp` · `05_operators.cpp` · `06_patterns.cpp`

---

## 1. Introduction

This module covers the complete foundation of C++ programming — everything you need to write, compile, and reason about a C++ program before moving to OOP or DSA. Every concept here is backed by working code in the corresponding `.cpp` file.

> **How to compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Core Concepts

### 2.1 Variables & Data Types (`01_variables.cpp`)

C++ is a **statically typed** language — every variable has a fixed type determined at compile time.

#### Primitive Types

| Type | Size | Range / Notes |
|------|------|---------------|
| `int` | 4 bytes | −2,147,483,648 to 2,147,483,647 |
| `long long` | 8 bytes | −9.2×10¹⁸ to 9.2×10¹⁸ |
| `short` | 2 bytes | −32,768 to 32,767 |
| `unsigned int` | 4 bytes | 0 to 4,294,967,295 |
| `float` | 4 bytes | ~7 decimal digits of precision |
| `double` | 8 bytes | ~15 decimal digits of precision |
| `char` | 1 byte | ASCII value 0–127 |
| `bool` | 1 byte | `true` (1) or `false` (0) |

#### `std::string`
A class from the standard library that manages a dynamic sequence of characters. Key methods: `.length()`, `.substr()`, `.find()`, `toupper()`.

#### `auto` (C++11)
`auto` lets the compiler **infer** the type from the initializer:
```cpp
auto x = 42;          // int
auto y = 3.14;        // double
auto z = string("Hi"); // string
```
Use `auto` when the type is obvious (e.g., iterators, return values of complex expressions).

#### `const`
`const` makes a variable **read-only** after initialization. Always use `const` for mathematical constants and values that must not change.
```cpp
const double PI = 3.14159265358979;
```

#### Integer Limits (`<climits>`)
- `INT_MAX` = 2,147,483,647
- `INT_MIN` = −2,147,483,648
- `LLONG_MAX` = 9,223,372,036,854,775,807

**Overflow warning:** Adding 1 to `INT_MAX` wraps around to `INT_MIN` — undefined behavior for signed integers!

#### Type Casting
```cpp
double d = 9.99;
(int)d;                        // C-style cast → 9 (truncates)
static_cast<double>(5) / 2;   // C++ preferred → 2.5
```
`static_cast` is **safer** than C-style casts and should be preferred.

---

### 2.2 Operators (`05_operators.cpp`)

#### Arithmetic Operators

| Operator | Meaning | Example | Result |
|----------|---------|---------|--------|
| `+` | Addition | `5 + 3` | `8` |
| `-` | Subtraction | `5 - 3` | `2` |
| `*` | Multiplication | `5 * 3` | `15` |
| `/` | Division | `5 / 3` | `1` (integer division!) |
| `%` | Modulus | `5 % 3` | `2` |

> **Critical:** `5 / 2 = 2` (truncates). To get `2.5`, use `5.0 / 2` or `static_cast<double>(5) / 2`.

#### Relational Operators
`==`, `!=`, `<`, `>`, `<=`, `>=` — all return `bool`.

#### Logical Operators
- `&&` (AND): true only if **both** operands are true. Short-circuits at first `false`.
- `||` (OR): true if **at least one** is true. Short-circuits at first `true`.
- `!` (NOT): inverts the value.

#### Bitwise Operators

| Operator | Operation | Example (`12=1100`, `10=1010`) | Result |
|----------|-----------|-------------------------------|--------|
| `&` | AND | `12 & 10` | `8` (1000) |
| `\|` | OR | `12 \| 10` | `14` (1110) |
| `^` | XOR | `12 ^ 10` | `6` (0110) |
| `~` | NOT | `~12` | `-13` |
| `<<` | Left shift | `12 << 1` | `24` (×2) |
| `>>` | Right shift | `12 >> 1` | `6` (÷2) |

**Useful bitwise tricks:**
```cpp
n & 1           // check if odd (1=odd, 0=even)
n & (n - 1)     // check if power of 2 (result = 0 means yes)
```

#### Assignment Operators
`+=`, `-=`, `*=`, `/=`, `%=`, `<<=`, `>>=` — shorthand for `var = var op value`.

#### Increment / Decrement
```cpp
int c = 5;
c++;   // post-increment: returns 5, then c becomes 6
++c;   // pre-increment: c becomes 7, returns 7
```

#### Ternary Operator
```cpp
condition ? value_if_true : value_if_false
string grade = (score >= 90) ? "A" : (score >= 80) ? "B" : "C";
```

#### `sizeof` Operator
Returns the size (in bytes) of a type or variable at **compile time**:
```cpp
sizeof(int)      // 4
sizeof(arr)      // total bytes, not number of elements!
sizeof(arr) / sizeof(arr[0])  // correct way to get array length
```

---

### 2.3 Control Flow (`02_control_flow.cpp`)

#### if / else-if / else
```cpp
if      (marks >= 90) cout << "A";
else if (marks >= 80) cout << "B";
else if (marks >= 70) cout << "C";
else                  cout << "F";
```

#### Ternary for Concise Conditions
```cpp
bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
cout << (leap ? "leap year" : "not a leap year");
```

#### switch Statement
Use `switch` instead of chained `if-else` when comparing one variable to multiple **integer/char constants**.
```cpp
switch (day) {
    case 1: cout << "Monday"; break;
    case 2: cout << "Tuesday"; break;
    default: cout << "Invalid";
}
```
> **Always include `break`** unless you intentionally want fall-through behavior.

#### Loops

| Loop | When to Use | Condition Check |
|------|------------|-----------------|
| `for` | Known number of iterations | Before each iteration |
| `while` | Unknown iterations, may skip entirely | Before each iteration |
| `do-while` | Must execute at least once | After each iteration |

```cpp
// Range-based for (C++11) — preferred for collections
for (const string& lang : langs) cout << lang;

// Classic for — when index is needed
for (int i = 0; i < n; i++) ...

// While — unknown iterations
while (p < 1000) { p *= 2; }

// Do-while — input validation, menus
do { /* execute first */ } while (condition);
```

#### `break` and `continue`
- `break`: immediately **exits** the enclosing loop
- `continue`: **skips** the rest of the current iteration

---

### 2.4 Functions & Recursion (`03_functions_recursion.cpp`)

#### Function Declaration vs Definition
Always **declare before use** (or define before `main`). Declarations go in header files for multi-file projects.

#### Function Overloading
Multiple functions with the **same name** but different parameter types or counts. The compiler chooses based on argument types:
```cpp
int    add(int a, int b)        { return a + b; }
double add(double a, double b)  { return a + b; }
int    add(int a, int b, int c) { return a + b + c; }
```

#### Default Arguments
```cpp
void greet(string name, string msg = "Hello") { ... }
greet("Deepak");              // uses default "Hello"
greet("Deepak", "Good morning"); // overrides default
```
Default values must be on the **rightmost** parameters.

#### Pass by Value vs Pass by Reference
```cpp
// Pass by value — function gets a COPY; original unchanged
void printVal(int x) { x = 99; } // caller's variable unaffected

// Pass by reference — function gets the ORIGINAL
void swapRef(int& a, int& b) { int t = a; a = b; b = t; } // modifies caller's variables
```

#### Recursion
A function that calls itself. Every recursive function needs:
1. **Base case** — stops the recursion
2. **Recursive case** — reduces the problem towards the base case

| Function | Time | Space | Notes |
|----------|------|-------|-------|
| `factorial(n)` | O(n) | O(n) | One stack frame per call |
| `fibMemo(n)` | O(n) | O(n) | Memoization avoids recomputation |
| `gcd(a, b)` | O(log min) | O(log n) | Euclid's algorithm |
| `fastPow(x, n)` | O(log n) | O(log n) | Divide-and-conquer |
| `hanoi(n)` | O(2ⁿ) | O(n) | Minimum moves = 2ⁿ − 1 |
| `subsets(arr)` | O(2ⁿ) | O(n) | Each element: include or exclude |

**Memoization pattern:**
```cpp
// Initialize cache with -1 (= "not computed yet")
vector<long long> memo(n + 1, -1);
if (memo[n] != -1) return memo[n];  // return cached result
memo[n] = ...;                      // compute and cache
```

#### Lambda Functions (C++11)
```cpp
// [capture](params) -> return_type { body }
auto square = [](int x) { return x * x; };       // no capture
auto scale  = [factor](int x) { return x * factor; }; // capture by value
```

---

### 2.5 Arrays & Strings (`04_arrays_strings.cpp`)

#### One-Dimensional Arrays
```cpp
int arr[] = {64, 23, 87, 12, 45};  // stack-allocated, fixed size
sort(arr, arr + n);                  // ascending — O(n log n)
sort(arr, arr + n, greater<int>()); // descending
```

#### Two-Pointer Technique — Reverse
```cpp
for (int l = 0, r = n - 1; l < r; l++, r--) swap(arr[l], arr[r]);
// Time: O(n) | Space: O(1)
```

#### Three-Reversal Trick — Rotate Array by k
```cpp
k %= n;                        // handle k > n
reverse(arr, arr + n);         // reverse all
reverse(arr, arr + k);         // reverse first k
reverse(arr + k, arr + n);     // reverse remaining
// Time: O(n) | Space: O(1)
```

#### Sliding Window — Max Sum of k Consecutive Elements
```cpp
// Build first window
for (int i = 0; i < k; i++) winSum += arr[i];
maxSum = winSum;
// Slide: add new element, remove outgoing element
for (int i = k; i < n; i++) {
    winSum += arr[i] - arr[i - k];
    maxSum = max(maxSum, winSum);
}
// Time: O(n) | Space: O(1)
```

#### Missing Number (Math Formula)
```cpp
// For array of 1..N with one missing element:
int expected = N * (N + 1) / 2;
int missing = expected - actualSum;
// Time: O(n) | Space: O(1)
```

#### 2D Arrays — Matrix Transpose
```cpp
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
        swap(mat[i][j], mat[j][i]);  // in-place, upper triangle only
// Time: O(n²) | Space: O(1)
```

#### String Operations

| Operation | Method | Notes |
|-----------|--------|-------|
| Length | `.length()` / `.size()` | Same result |
| Substring | `.substr(pos, len)` | 0-indexed |
| Find | `.find(char/str)` | Returns `string::npos` if not found |
| Reverse | `reverse(s.begin(), s.end())` | In-place |
| To int | `stoi(s)` | Throws `invalid_argument` if invalid |
| To string | `to_string(n)` | Works for int, double |

#### Palindrome Check (Two-Pointer)
```cpp
int l = 0, r = str.size() - 1;
while (l < r) {
    if (str[l] != str[r]) return false;
    l++; r--;
}
return true;
// Time: O(n) | Space: O(1)
```

#### Anagram Check
Sort both strings and compare:
```cpp
sort(a.begin(), a.end());
sort(b.begin(), b.end());
return a == b;
// Time: O(n log n) | Space: O(1) if sorted in-place
```

#### Longest Substring Without Repeating Characters
```cpp
unordered_map<char, int> lastSeen;
int left = 0, maxLen = 0;
for (int right = 0; right < str.size(); right++) {
    char c = str[right];
    if (lastSeen.count(c) && lastSeen[c] >= left)
        left = lastSeen[c] + 1;  // shrink window
    lastSeen[c] = right;
    maxLen = max(maxLen, right - left + 1);
}
// Time: O(n) | Space: O(min(n, charset))
```

---

### 2.6 Pattern Programs (`06_patterns.cpp`)

Patterns are asked in interviews and exams to test **loop control and spatial reasoning**.

| Pattern | Key Logic | Outer Loop | Inner Loop |
|---------|-----------|------------|------------|
| Right-angle triangle | `j <= i` stars | `i: 1→n` | `j: 1→i` |
| Inverted triangle | `j <= i` stars | `i: n→1` | `j: 1→i` |
| Pyramid (centred) | `(n-i)` spaces + `(2i-1)` stars | `i: 1→n` | Two inner loops |
| Inverted pyramid | Same as above, reversed | `i: n→1` | Two inner loops |
| Diamond | Upper + lower pyramid | Two separate outer loops | — |
| Hollow square | Star on border only | `i: 1→n` | Conditional print |
| Number triangle | `j` instead of `*` | `i: 1→n` | `j: 1→i` |
| Floyd's triangle | Consecutive numbers | `i: 1→n` | `num++` |
| Alphabet triangle | `'A' + j` | `i: 0→n` | `j: 0→i` |
| Pascal's triangle | Binomial coefficient `C(i,j)` | `i: 0→n` | Compute with `val = val*(i-j)/(j+1)` |

> **Time:** O(n²) for all patterns | **Space:** O(1)

---

## 3. Internal Working

### Stack vs Heap
- **Local variables** (declared inside functions) live on the **stack** — automatically allocated and deallocated.
- **Dynamic memory** (`new`/`delete`) lives on the **heap** — manual management. (Covered in intermediate module.)

### Compilation Process
```
Source (.cpp)  →  Preprocessor  →  Compiler  →  Assembler  →  Linker  →  Executable
```
- **Preprocessor:** Handles `#include`, `#define`, macro expansion
- **Compiler:** Translates to assembly, checks types and syntax
- **Assembler:** Converts assembly to machine code (object file `.o`)
- **Linker:** Combines object files with libraries into the final executable

### Memory Layout of a Variable
```
int x = 10;
// x occupies 4 bytes on the stack
// Address: e.g., 0x7ffee3b2a1c4
// Value stored: 00 00 00 0A (little-endian)
```

### Recursion Call Stack
Each recursive call adds a **stack frame** holding the local variables and return address. Stack depth = O(n) for linear recursion. Stack **overflow** occurs if recursion is too deep without a base case.

---

## 4. Operations & Techniques

### Operator Precedence (Simplified)
Higher precedence = evaluated first:
```
:: > () [] -> . > ! ~ ++ -- (unary) > * / % > + - > << >> > < > <= >= > == != > & > ^ > | > && > || > ?: > = op= > ,
```
> **Rule of thumb:** When in doubt, use parentheses.

### Input / Output
```cpp
#include <iostream>
using namespace std;

cin >> x;            // reads until whitespace
cin >> x >> y;       // chain multiple reads
getline(cin, str);   // reads entire line including spaces
cout << "val: " << x << endl;   // endl flushes buffer
cout << "val: " << x << "\n";   // faster (no flush)
```

---

## 5. Time & Space Complexity Table

| Concept / Operation | Time | Space | File Reference |
|--------------------|------|-------|---------------|
| Variable declaration | O(1) | O(1) | `01_variables.cpp` |
| Type casting | O(1) | O(1) | `01_variables.cpp` |
| if-else / switch | O(1) | O(1) | `02_control_flow.cpp` |
| for / while loop | O(n) | O(1) | `02_control_flow.cpp` |
| Nested loops (patterns) | O(n²) | O(1) | `06_patterns.cpp` |
| Function call | O(1) | O(1) per frame | `03_functions_recursion.cpp` |
| Factorial (recursive) | O(n) | O(n) | `03_functions_recursion.cpp` |
| Fibonacci (memoized) | O(n) | O(n) | `03_functions_recursion.cpp` |
| GCD (Euclid) | O(log n) | O(log n) | `03_functions_recursion.cpp` |
| Fast exponentiation | O(log n) | O(log n) | `03_functions_recursion.cpp` |
| Tower of Hanoi | O(2ⁿ) | O(n) | `03_functions_recursion.cpp` |
| Generate all subsets | O(2ⁿ) | O(n) | `03_functions_recursion.cpp` |
| Array sort (`std::sort`) | O(n log n) | O(log n) | `04_arrays_strings.cpp` |
| Array reverse (2-pointer) | O(n) | O(1) | `04_arrays_strings.cpp` |
| Array rotate (3-reversal) | O(n) | O(1) | `04_arrays_strings.cpp` |
| Sliding window max sum | O(n) | O(1) | `04_arrays_strings.cpp` |
| Missing number (formula) | O(n) | O(1) | `04_arrays_strings.cpp` |
| Matrix transpose | O(n²) | O(1) | `04_arrays_strings.cpp` |
| Palindrome check | O(n) | O(1) | `04_arrays_strings.cpp` |
| Anagram check (sort) | O(n log n) | O(1) | `04_arrays_strings.cpp` |
| Longest unique substring | O(n) | O(charset) | `04_arrays_strings.cpp` |

---

## 6. Common Mistakes

### Beginner Mistakes

- **Integer division pitfall:** `5 / 2 = 2`, not `2.5`. Promote at least one operand to `double`.
- **Missing `break` in switch:** Causes fall-through to the next case — a silent bug.
- **Forgetting base case in recursion:** Causes a stack overflow at runtime.
- **`sizeof` on array pointer:** `sizeof(ptr)` gives pointer size (8 bytes on 64-bit), not the array size. Only works for stack-declared arrays.
- **Comparing strings with `==` on C-style `char*`:** Use `strcmp()` or prefer `std::string`.
- **Signed integer overflow:** `INT_MAX + 1` wraps to `INT_MIN` — undefined behavior.
- **`auto` without initializer:** `auto x;` is a compile error. `auto` needs a value to infer from.

### Intermediate Mistakes

- **Modifying a loop variable inside the loop body:** Can cause infinite loops or skipped iterations.
- **`continue` inside deeply nested loops:** Only skips the innermost loop's current iteration.
- **Post-increment in complex expressions:** `arr[i++] = arr[i]` is undefined behavior in C++.
- **Passing large arrays by value:** Creates a full copy — use `const int*` or a reference instead.
- **Memoization cache not large enough:** Accessing `memo[n]` when `memo` has size `n` causes undefined behavior.
- **String method `find()` returning `string::npos`:** Always check before using the returned index.

---

## 7. Interview Relevance

### Frequently Asked Topics

| Topic | Common Interview Questions |
|-------|---------------------------|
| Data types | "What is the size of `int`? When use `long long`?" |
| Type casting | "What is the difference between C-style cast and `static_cast`?" |
| Operators | "Explain short-circuit evaluation. How to check if a number is a power of 2?" |
| Loops | "When do you use `do-while` vs `while`?" |
| Functions | "What is function overloading? How does the compiler resolve overloads?" |
| References | "What is the difference between pass-by-value and pass-by-reference?" |
| Recursion | "What is the time complexity of factorial? Can you write iterative Fibonacci?" |
| Bitwise | "How do you check if `n` is even using bitwise operators?" |
| Strings | "Check if a string is a palindrome. Find the longest non-repeating substring." |
| Patterns | "Print Pascal's triangle. Print a diamond pattern." |

### Key Points to Mention in Interviews

- Always mention **edge cases**: empty arrays, zero inputs, `INT_MAX` boundaries.
- Explain **why** you chose an approach (e.g., two-pointer is O(n) vs sort which is O(n log n)).
- For recursion, always state the **base case** and **recursive case** explicitly.
- Mention `static_cast` over C-style casts.
- For `auto`, mention it improves readability and avoids verbose type names.

---

## 8. Best Practices (C++ Specific)

### Code Style
```cpp
// ✅ Prefer const over #define for constants
const double PI = 3.14159;
// ❌ Avoid — no type safety, no scope
#define PI 3.14159

// ✅ Initialize variables at declaration
int count = 0;
// ❌ Uninitialized — undefined behavior
int count;

// ✅ auto for complex types
auto it = myMap.find(key);
// ❌ Verbose and error-prone
std::unordered_map<int, string>::iterator it = myMap.find(key);
```

### Performance Tips
- Use `'\n'` instead of `std::endl` — `endl` flushes the buffer (slow in tight loops).
- Prefer `++i` over `i++` for iterators and complex types (avoids creating a temporary copy).
- Pass large objects by `const&` to avoid copying.
- Avoid global variables — they persist for the program's lifetime and cause hard-to-trace bugs.

### Recursion Best Practices
- Always define the **base case first** to prevent infinite recursion.
- Add **memoization** when subproblems overlap (e.g., Fibonacci).
- For very deep recursion (n > ~10,000), consider an **iterative approach** to avoid stack overflow.
- Use `long long` for factorials and Fibonacci — they overflow `int` quickly.

### String Best Practices
- Prefer `std::string` over `char[]` — safer, resizable, STL-compatible.
- Use `getline(cin, str)` when reading strings with spaces.
- Call `cin.ignore()` before `getline` if mixing `cin >>` and `getline`.

---

## 9. Summary

```
cpp/basics/ — What's Covered
├── 01_variables.cpp    → Data types, auto, const, sizeof, type casting, INT limits
├── 02_control_flow.cpp → if-else, ternary, switch, for/while/do-while, break/continue, patterns
├── 03_functions_recursion.cpp → Overloading, default args, pass-by-ref, factorial,
│                               Fibonacci (memo), GCD (Euclid), fast power, Hanoi,
│                               subsets (backtracking), lambdas
├── 04_arrays_strings.cpp → Sort, reverse (2-ptr), rotate (3-reversal), sliding window,
│                           missing number, matrix transpose, palindrome, anagram,
│                           longest unique substring, string↔number conversion
├── 05_operators.cpp    → Arithmetic, relational, logical, bitwise, assignment,
│                         pre/post increment, ternary, sizeof, bitwise tricks
└── 06_patterns.cpp     → 10 patterns: triangle, pyramid, diamond, hollow square,
                          Floyd's, alphabet, Pascal's triangle
```

**Key Takeaways:**
- Master `int` vs `long long` — overflow is a common source of bugs in competitive programming.
- The **two-pointer** and **sliding window** patterns introduced here are the foundation of many DSA problems.
- Recursion + memoization = the basis of **dynamic programming** (covered in DSA module).
- Bitwise operators are O(1) alternatives to many arithmetic operations — heavily used in competitive coding.
- Pattern programs train your ability to think in terms of rows, columns, and conditions — a skill that transfers to 2D DP and matrix problems.

---

> **Next Steps:** Head to `cpp/intermediate/` for pointers, memory management, STL containers, file I/O, and exception handling.
