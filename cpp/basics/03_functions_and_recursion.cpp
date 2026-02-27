// ============================================================
// C++ | Basics → Functions & Recursion
// ============================================================
// DESCRIPTION:
//   - Function declaration, calling conventions, overloading
//   - Default arguments
//   - Pass by value, reference, pointer
//   - Inline functions
//   - Recursion: factorial, Fibonacci, power, binary search
//   - Tail recursion
//   - std::function and lambdas
//
// COMPILE & RUN:
//   g++ -std=c++17 03_functions_and_recursion.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// SECTION 1: BASIC FUNCTIONS & DEFAULT ARGUMENTS
// ============================================================

int add(int a, int b) { return a + b; }

double circleArea(double r) {
    return 3.14159265 * r * r;
}

// Default arguments — must appear at the END of the param list
void greet(const string& name, const string& msg = "Hello") {
    cout << msg << ", " << name << "!\n";
}

// ============================================================
// SECTION 2: FUNCTION OVERLOADING
// ============================================================
// Same name, different parameter types — compiler picks the right one.

int    square(int x)          { return x * x; }
double square(double x)       { return x * x; }
string square(const string& s){ return s + s; }

// ============================================================
// SECTION 3: PASS BY VALUE / REFERENCE / POINTER
// ============================================================

void doubleVal(int n)    { n *= 2; }              // copy — original unchanged
void doubleRef(int& n)   { n *= 2; }              // alias — affects original
void doublePtr(int* n)   { *n *= 2; }             // address — must dereference

// Return by reference: allows direct modification through return value
int& getElement(vector<int>& v, int i) { return v[i]; }

inline int maxOf(int a, int b) { return a > b ? a : b; }  // inline hint

// ============================================================
// SECTION 4: RECURSION
// ============================================================
// Every recursive function needs:
//   1. Base case   — stopping condition
//   2. Recursive case — reduces problem size

/** n! = n × (n-1)! | Base: 0! = 1 | Time: O(n) | Space: O(n) stack */
long long factorial(int n) {
    if (n <= 1) return 1;              // base case
    return n * factorial(n - 1);      // recursive case
}

/** Naive Fibonacci — O(2^n) time — use memoization in practice */
long long fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

/** Fibonacci with memoization — O(n) time, O(n) space */
long long fibMemo(int n, vector<long long>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibMemo(n-1, memo) + fibMemo(n-2, memo);
    return memo[n];
}

/**
 * Fast power using divide & conquer: base^exp.
 * base^exp = (base^(exp/2))^2 for even, base * base^(exp-1) for odd.
 * Time: O(log n)  |  Space: O(log n)
 */
double fastPow(double base, int exp) {
    if (exp == 0) return 1.0;
    if (exp < 0)  return 1.0 / fastPow(base, -exp);
    if (exp % 2 == 0) {
        double half = fastPow(base, exp / 2);
        return half * half;
    }
    return base * fastPow(base, exp - 1);
}

/** Sum of array via recursion — O(n) */
int sumArray(const vector<int>& a, int n) {
    if (n == 0) return 0;
    return a[n-1] + sumArray(a, n-1);
}

/** Recursive binary search — O(log n) */
int binarySearch(const vector<int>& a, int lo, int hi, int target) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == target) return mid;
    return a[mid] < target ? binarySearch(a, mid+1, hi, target)
                           : binarySearch(a, lo, mid-1, target);
}

// ============================================================
// SECTION 5: TAIL RECURSION
// ============================================================
// The recursive call is the LAST operation → compiler can optimise
// into a loop (no extra stack frames).

long long factTail(int n, long long acc = 1) {
    if (n <= 1) return acc;
    return factTail(n - 1, n * acc);   // acc carries the result
}

// ============================================================
// SECTION 6: STD::FUNCTION & LAMBDAS
// ============================================================

int multiply(int a, int b) { return a * b; }

// Accepts any callable via std::function (lambdas, function ptrs, functors)
int applyOp(int a, int b, function<int(int,int)> op) { return op(a, b); }

// ============================================================
// MAIN
// ============================================================
int main() {

    cout << "=== BASIC FUNCTIONS ===" << "\n";
    cout << "  add(3,4): " << add(3,4) << "\n";
    cout << "  circleArea(5): " << circleArea(5.0) << "\n";

    cout << "\n=== DEFAULT ARGUMENTS ===" << "\n";
    greet("Alice");
    greet("Bob", "Good morning");

    cout << "\n=== OVERLOADING ===" << "\n";
    cout << "  square(5):      " << square(5) << "\n";
    cout << "  square(3.14):   " << square(3.14) << "\n";
    cout << "  square(\"hi\"):   " << square(string("hi")) << "\n";

    cout << "\n=== PASS BY VALUE / REF / POINTER ===" << "\n";
    int n = 10;
    doubleVal(n); cout << "  after doubleVal: " << n << " (unchanged)\n";
    doubleRef(n); cout << "  after doubleRef: " << n << " (doubled)\n";
    doublePtr(&n);cout << "  after doublePtr: " << n << " (doubled)\n";

    vector<int> v = {1,2,3,4,5};
    getElement(v, 2) = 99;
    cout << "  v[2] set via ref return: " << v[2] << "\n";

    cout << "\n=== RECURSION ===" << "\n";
    cout << "  factorial(5):  " << factorial(5)  << "\n";
    cout << "  factorial(10): " << factorial(10) << "\n";
    cout << "  fib(8): "        << fib(8)         << "\n";

    vector<long long> memo(50, -1);
    cout << "  fib(40) memo: "  << fibMemo(40, memo) << "\n";

    cout << "  fastPow(2,10): " << fastPow(2,10) << "\n";
    cout << "  fastPow(3,-2): " << fastPow(3,-2) << "\n";

    vector<int> arr = {1,2,3,4,5};
    cout << "  sumArray({1..5}): " << sumArray(arr, 5) << "\n";

    vector<int> sorted = {1,3,5,7,9};
    cout << "  binarySearch(7): idx " << binarySearch(sorted,0,4,7) << "\n";

    cout << "\n=== TAIL RECURSION ===" << "\n";
    cout << "  factTail(7): " << factTail(7) << "\n";

    cout << "\n=== STD::FUNCTION & LAMBDAS ===" << "\n";
    cout << "  applyOp(6,7, multiply): " << applyOp(6,7,multiply) << "\n";

    auto addLambda = [](int a, int b){ return a+b; };
    cout << "  applyOp(6,7, lambda+): " << applyOp(6,7,addLambda) << "\n";

    // Closure — captures outer variable
    int offset = 10;
    auto addOffset = [offset](int x){ return x + offset; };
    cout << "  addOffset(5): " << addOffset(5) << "\n";

    return 0;
}
