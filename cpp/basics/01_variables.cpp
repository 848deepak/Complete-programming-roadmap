// ============================================================
// MODULE 01 | C++ BASICS → Variables & Data Types
// ============================================================
// DESCRIPTION:
//   Demonstrates all primitive and complex data types in C++,
//   type sizes, type casting, overflow, and the 'auto' keyword.
//
// COMPILE & RUN:
//   g++ -std=c++17 01_variables.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   === INTEGER TYPES ===
//   int:          2147483647  size=4B
//   long long:    9223372036854775807  size=8B
//   ...
// ============================================================

#include <iostream>
#include <climits>    // INT_MAX, INT_MIN, LLONG_MAX etc.
#include <string>
using namespace std;

int main() {

    // ================================================================
    // SECTION 1: INTEGER TYPES
    // ================================================================
    // Integers store whole numbers. The size determines the range.
    // ----------------------------------------------------------------
    cout << "=== INTEGER TYPES ===" << endl;

    int         i  = 2147483647;         // 4 bytes → range: -2^31 to 2^31-1
    long long   ll = 9223372036854775807LL; // 8 bytes → range: -2^63 to 2^63-1
    short       s  = 32767;              // 2 bytes → range: -32768 to 32767
    unsigned int u = 4294967295U;        // 4 bytes → non-negative only: 0 to 2^32-1

    cout << "int:          " << i  << "  size=" << sizeof(i)  << "B" << endl;
    cout << "long long:    " << ll << "  size=" << sizeof(ll) << "B" << endl;
    cout << "short:        " << s  << "  size=" << sizeof(s)  << "B" << endl;
    cout << "unsigned int: " << u  << "  size=" << sizeof(u)  << "B" << endl;

    // ================================================================
    // SECTION 2: FLOATING POINT TYPES
    // ================================================================
    // Used for decimal numbers. 'double' is preferred for precision.
    // ----------------------------------------------------------------
    cout << "\n=== FLOATING POINT ===" << endl;

    float  f1 = 3.14f;               // 4 bytes, ~7 decimal digits of precision
    double f2 = 3.141592653589793;   // 8 bytes, ~15 decimal digits of precision

    cout << "float:  " << f1 << "  size=" << sizeof(f1) << "B" << endl;
    cout << "double: " << f2 << "  size=" << sizeof(f2) << "B" << endl;

    // ================================================================
    // SECTION 3: CHAR AND BOOL
    // ================================================================
    // char stores a single character using its ASCII value (0–127).
    // bool stores true (1) or false (0).
    // ----------------------------------------------------------------
    cout << "\n=== CHAR & BOOL ===" << endl;

    char ch   = 'A';       // ASCII value 65
    bool flag = true;

    cout << "char 'A' = ASCII " << (int)ch << endl;    // cast to int to see value
    cout << boolalpha << "bool: " << flag << " / " << !flag << endl; // boolalpha prints "true"/"false"

    // ================================================================
    // SECTION 4: STRING
    // ================================================================
    // std::string is a class that manages a sequence of characters.
    // ----------------------------------------------------------------
    cout << "\n=== STRING ===" << endl;

    string name = "Deepak";
    cout << "name=" << name << "  len=" << name.length() << endl;

    // Iterate character-by-character and convert to uppercase
    cout << "upper: ";
    for (char c : name) cout << (char)toupper(c);
    cout << endl;

    // ================================================================
    // SECTION 5: AUTO (Type Inference, C++11)
    // ================================================================
    // 'auto' lets the compiler infer the type from the initializer.
    // Use when the type is obvious or verbose (e.g., iterators).
    // ----------------------------------------------------------------
    cout << "\n=== AUTO ===" << endl;

    auto x = 42;            // compiler deduces: int
    auto y = 3.14;          // compiler deduces: double
    auto z = string("Hi");  // compiler deduces: string

    cout << "auto int: "    << x << endl;
    cout << "auto double: " << y << endl;
    cout << "auto string: " << z << endl;

    // ================================================================
    // SECTION 6: CONST
    // ================================================================
    // 'const' makes a variable read-only after initialization.
    // Use for values that should not change (e.g., mathematical constants).
    // ----------------------------------------------------------------
    cout << "\n=== CONST ===" << endl;

    const double PI = 3.14159265358979;
    cout << "PI = " << PI << endl;
    // PI = 3.0;  // ← ERROR: assignment of read-only variable

    // ================================================================
    // SECTION 7: INTEGER LIMITS (from <climits>)
    // ================================================================
    cout << "\n=== LIMITS ===" << endl;

    cout << "INT_MAX = " << INT_MAX << endl;   // 2147483647
    cout << "INT_MIN = " << INT_MIN << endl;   // -2147483648
    cout << "LLONG_MAX = " << LLONG_MAX << endl;

    // EDGE CASE: Integer overflow wraps around (undefined behavior for signed)
    cout << "INT_MAX + 1 (overflow!) = " << INT_MAX + 1 << endl; // → -2147483648

    // ================================================================
    // SECTION 8: TYPE CASTING
    // ================================================================
    // Explicit casting converts one type to another.
    // Implicit casting (promotion) happens automatically (e.g., int → double).
    // ----------------------------------------------------------------
    cout << "\n=== TYPE CASTING ===" << endl;

    double d = 9.99;
    cout << "(int)9.99  = " << (int)d  << "  (truncates decimal!)" << endl;

    int n = 5;
    cout << "5 / 2   (int division)  = " << n / 2   << endl;   // 2
    cout << "5 / 2.0 (float result)  = " << n / 2.0 << endl;   // 2.5

    // static_cast is the C++ preferred way (safer than C-style)
    cout << "static_cast<double>(5)/2 = " << static_cast<double>(n) / 2 << endl;

    return 0;
}
// ============================================================
// COMPLEXITY ANALYSIS
//   Time  : O(1) — each operation is constant time
//   Space : O(1) — no dynamic allocation
// ============================================================
