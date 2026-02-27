// ============================================================
// MODULE 03 | C++ BASICS → Functions & Recursion
// ============================================================
// DESCRIPTION:
//   Covers function declaration, overloading, default arguments,
//   pass-by-value vs pass-by-reference, and recursion patterns
//   including factorial, Fibonacci (memoized), GCD, fast power,
//   Tower of Hanoi, subset generation, and lambda functions.
//
// COMPILE & RUN:
//   g++ -std=c++17 03_functions_recursion.cpp -o out && ./out
//
// COMPLEXITY OVERVIEW:
//   Factorial  : Time O(n),      Space O(n) call stack
//   Fibonacci  : Time O(n),      Space O(n) with memoization
//   GCD        : Time O(log n),  Space O(log n) call stack
//   FastPow    : Time O(log n),  Space O(log n) call stack
//   Hanoi      : Time O(2^n),    Space O(n)  call stack
//   Subsets    : Time O(2^n),    Space O(n)  call stack
// ============================================================

#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// FUNCTION OVERLOADING
// ============================================================
// Multiple functions with the SAME name but DIFFERENT parameter types.
// The compiler picks the correct version based on the argument types.

/** Returns sum of two integers. */
int    add(int a, int b)        { return a + b; }

/** Returns sum of two doubles (overload for floating point). */
double add(double a, double b)  { return a + b; }

/** Returns sum of three integers (overload for 3 arguments). */
int    add(int a, int b, int c) { return a + b + c; }

// ============================================================
// DEFAULT ARGUMENTS
// ============================================================
// If the caller doesn't supply a value, the default is used.
// Default values must be on the RIGHTMOST parameters.

/**
 * Prints a greeting message.
 * @param name  Person's name (required)
 * @param msg   Greeting prefix (optional, defaults to "Hello")
 */
void greet(string name, string msg = "Hello") {
    cout << msg << ", " << name << "!\n";
}

// ============================================================
// PASS BY REFERENCE
// ============================================================
// Passing by reference (&) gives the function access to the
// ORIGINAL variable — changes inside affect the caller.

/**
 * Swaps two integers in-place using references.
 * Time: O(1)  |  Space: O(1)
 */
void swapRef(int& a, int& b) {
    int temp = a;   // save 'a'
    a = b;          // overwrite 'a' with 'b'
    b = temp;       // overwrite 'b' with saved 'a'
}

// ============================================================
// RECURSION: FACTORIAL
// ============================================================
// Base case: 0! = 1! = 1
// Recursive: n! = n × (n-1)!
// Time: O(n)  |  Space: O(n) — one stack frame per call

/**
 * Computes n! recursively.
 * Edge case: n <= 1 returns 1 (handles both 0! and 1!).
 */
long long factorial(int n) {
    if (n <= 1) return 1;              // base case
    return (long long)n * factorial(n - 1); // recursive case
}

// ============================================================
// RECURSION: MEMOIZED FIBONACCI
// ============================================================
// Naive recursion is O(2^n). Memoization caches results → O(n).
// memo[i] stores fib(i); initialized to -1 (= "not computed yet").

/**
 * Computes fib(n) with memoization.
 * @param n     Index in Fibonacci sequence (0-indexed)
 * @param memo  Cache array, size >= n+1, pre-filled with -1
 * Time: O(n)  |  Space: O(n) for memo table + call stack
 */
long long fibMemo(int n, vector<long long>& memo) {
    if (n <= 1) return n;                          // base: fib(0)=0, fib(1)=1
    if (memo[n] != -1) return memo[n];             // already computed → return cache
    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo); // compute & store
    return memo[n];
}

// ============================================================
// RECURSION: GCD (Euclid's Algorithm)
// ============================================================
// Based on the identity: gcd(a, b) = gcd(b, a % b)
// Base case: gcd(a, 0) = a
// Time: O(log(min(a,b)))  |  Space: O(log n) call stack

/**
 * Returns the greatest common divisor of a and b.
 * Edge case: gcd(0, 0) = 0 (mathematically undefined; returns 0 by convention).
 */
int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

// ============================================================
// RECURSION: FAST EXPONENTIATION
// ============================================================
// Naive x^n takes O(n) multiplications; divide-and-conquer → O(log n).
// If n is even: x^n = (x^(n/2))^2
// If n is odd : x^n = x * x^(n-1)

/**
 * Computes x raised to the power n efficiently.
 * Handles negative exponents: x^(-n) = 1 / x^n
 * Time: O(log n)  |  Space: O(log n)
 */
double fastPow(double x, int n) {
    if (n == 0) return 1.0;                       // x^0 = 1 always
    if (n < 0)  return 1.0 / fastPow(x, -n);     // handle negative exponent
    if (n % 2 == 0) {
        double half = fastPow(x, n / 2);          // compute x^(n/2) once
        return half * half;                        // square it
    }
    return x * fastPow(x, n - 1);                 // n is odd
}

// ============================================================
// RECURSION: TOWER OF HANOI
// ============================================================
// Move n disks from 'from' peg to 'to' peg using 'aux' as helper.
// Rule: never place a larger disk on a smaller one.
// Time: O(2^n)  |  Space: O(n) call stack

/**
 * Prints the sequence of moves to solve Tower of Hanoi.
 * @param n    Number of disks
 * @param from Source peg
 * @param to   Destination peg
 * @param aux  Auxiliary (helper) peg
 */
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        // Base case: move the single smallest disk directly
        cout << "  Disk 1: " << from << " → " << to << "\n";
        return;
    }
    hanoi(n - 1, from, aux, to);   // Step 1: move top (n-1) disks to aux
    cout << "  Disk " << n << ": " << from << " → " << to << "\n"; // Step 2
    hanoi(n - 1, aux, to, from);   // Step 3: move (n-1) disks from aux to 'to'
}

// ============================================================
// BACKTRACKING: GENERATE ALL SUBSETS
// ============================================================
// At each index we have two choices: EXCLUDE or INCLUDE the element.
// Total subsets for n elements: 2^n
// Time: O(2^n)  |  Space: O(n) call stack + current subset

/**
 * Prints all subsets of 'arr' starting from index 'idx'.
 * @param arr   Input array
 * @param idx   Current position in arr
 * @param curr  Current subset being built
 */
void subsets(vector<int>& arr, int idx, vector<int>& curr) {
    if (idx == (int)arr.size()) {
        // Reached the end — print the current subset
        cout << "{ ";
        for (int x : curr) cout << x << " ";
        cout << "}\n";
        return;
    }
    // Choice 1: EXCLUDE arr[idx] — move to next element
    subsets(arr, idx + 1, curr);

    // Choice 2: INCLUDE arr[idx] — add it, recurse, then remove (backtrack)
    curr.push_back(arr[idx]);
    subsets(arr, idx + 1, curr);
    curr.pop_back();   // ← backtrack: restore state for the caller
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Function Overloading ---
    cout << "=== FUNCTION OVERLOADING ===" << endl;
    cout << "add(5, 3)       = " << add(5, 3)       << endl;  // int version
    cout << "add(2.5, 3.1)   = " << add(2.5, 3.1)   << endl;  // double version
    cout << "add(1, 2, 3)    = " << add(1, 2, 3)     << endl;  // 3-arg version

    // --- Default Arguments ---
    cout << "\n=== DEFAULT ARGUMENTS ===" << endl;
    greet("Deepak");                    // uses default "Hello"
    greet("Deepak", "Good morning");    // overrides default

    // --- Pass By Reference ---
    cout << "\n=== PASS BY REFERENCE ===" << endl;
    int a = 10, b = 20;
    cout << "Before swap: a=" << a << " b=" << b << endl;
    swapRef(a, b);
    cout << "After swap:  a=" << a << " b=" << b << endl;

    // --- Factorial ---
    cout << "\n=== FACTORIAL ===" << endl;
    for (int i = 0; i <= 10; i++)
        cout << i << "! = " << factorial(i) << "\n";

    // --- Fibonacci ---
    cout << "\n=== FIBONACCI (memoized) ===" << endl;
    vector<long long> memo(50, -1);              // cache for indices 0–49
    cout << "fib(0–9): ";
    for (int i = 0; i < 10; i++) cout << fibMemo(i, memo) << " ";
    cout << "\nfib(40) = " << fibMemo(40, memo) << endl;   // 102334155

    // --- GCD ---
    cout << "\n=== GCD (Euclidean) ===" << endl;
    cout << "gcd(48, 18)   = " << gcd(48, 18)   << endl;  // 6
    cout << "gcd(100, 75)  = " << gcd(100, 75)  << endl;  // 25
    cout << "gcd(0, 5)     = " << gcd(0, 5)     << endl;  // 5 (edge case)

    // --- Fast Power ---
    cout << "\n=== FAST EXPONENTIATION ===" << endl;
    cout << "2^10  = " << (int)fastPow(2, 10) << endl;    // 1024
    cout << "3^5   = " << (int)fastPow(3, 5)  << endl;    // 243
    cout << "2^-3  = " << fastPow(2, -3)       << endl;   // 0.125

    // --- Tower of Hanoi ---
    cout << "\n=== TOWER OF HANOI (3 disks) ===" << endl;
    cout << "Moves needed: " << ((1 << 3) - 1) << " (= 2^n - 1)\n";
    hanoi(3, 'A', 'C', 'B');   // A=source, C=dest, B=helper

    // --- Subsets ---
    cout << "\n=== ALL SUBSETS of {1, 2, 3} ===" << endl;
    vector<int> arr = {1, 2, 3}, curr;
    subsets(arr, 0, curr);     // 2^3 = 8 subsets

    // --- Lambda Functions (C++11) ---
    cout << "\n=== LAMBDAS ===" << endl;
    // [capture](params) -> return_type { body }
    auto square = [](int x) { return x * x; };    // no capture
    int  factor = 3;
    auto scale  = [factor](int x) { return x * factor; };  // capture by value

    cout << "square(6)  = " << square(6)  << endl;  // 36
    cout << "scale(7)   = " << scale(7)   << endl;  // 21

    return 0;
}
