// ============================================================
// MODULE 05 | C++ BASICS → Operators
// ============================================================
// DESCRIPTION:
//   Covers all operator categories in C++:
//   Arithmetic, Relational, Logical, Bitwise, Assignment,
//   Increment/Decrement, Ternary, sizeof, and comma operators.
//
// COMPILE & RUN:
//   g++ -std=c++17 05_operators.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   === ARITHMETIC ===
//   5 + 3 = 8   5 - 3 = 2   5 * 3 = 15   5 / 3 = 1   5 % 3 = 2
//   ...
// ============================================================

#include <iostream>
using namespace std;

int main() {

    // ================================================================
    // SECTION 1: ARITHMETIC OPERATORS
    // ================================================================
    // +  Addition         -  Subtraction     *  Multiplication
    // /  Division         %  Modulus (remainder — integers only)
    // ----------------------------------------------------------------
    cout << "=== ARITHMETIC OPERATORS ===" << endl;

    int a = 5, b = 3;
    cout << a << " + " << b << " = " << a + b << endl;   // 8
    cout << a << " - " << b << " = " << a - b << endl;   // 2
    cout << a << " * " << b << " = " << a * b << endl;   // 15
    cout << a << " / " << b << " = " << a / b << endl;   // 1  (integer division!)
    cout << a << " % " << b << " = " << a % b << endl;   // 2  (remainder)

    // Integer division vs float division
    cout << "5.0 / 2   = " << 5.0 / 2 << " (float division)\n";
    cout << "5   / 2   = " << 5 / 2   << " (integer division — truncates)\n";

    // ================================================================
    // SECTION 2: RELATIONAL (COMPARISON) OPERATORS
    // ================================================================
    // Return bool: true (1) or false (0)
    // ==  equal         !=  not equal
    // <   less than     >   greater than
    // <=  less/equal    >=  greater/equal
    // ----------------------------------------------------------------
    cout << "\n=== RELATIONAL OPERATORS ===" << endl;

    int x = 10, y = 20;
    cout << boolalpha;  // print "true"/"false" instead of 1/0
    cout << x << " == " << y << " : " << (x == y) << endl;   // false
    cout << x << " != " << y << " : " << (x != y) << endl;   // true
    cout << x << " <  " << y << " : " << (x < y)  << endl;   // true
    cout << x << " >  " << y << " : " << (x > y)  << endl;   // false
    cout << x << " <= " << y << " : " << (x <= y) << endl;   // true
    cout << x << " >= " << y << " : " << (x >= y) << endl;   // false

    // ================================================================
    // SECTION 3: LOGICAL OPERATORS
    // ================================================================
    // &&  AND — true only if BOTH operands are true
    // ||  OR  — true if AT LEAST ONE operand is true
    // !   NOT — inverts the boolean value
    // Short-circuit: && stops at first false; || stops at first true
    // ----------------------------------------------------------------
    cout << "\n=== LOGICAL OPERATORS ===" << endl;

    bool p = true, q = false;
    cout << "p=" << p << " q=" << q << endl;
    cout << "p && q  = " << (p && q)  << endl;   // false
    cout << "p || q  = " << (p || q)  << endl;   // true
    cout << "!p      = " << (!p)      << endl;   // false
    cout << "!q      = " << (!q)      << endl;   // true
    cout << "p && !q = " << (p && !q) << endl;   // true  (AND NOT)

    // Practical example: input validation
    int age = 25;
    bool hasID = true;
    bool canEnter = (age >= 18) && hasID;
    cout << "Can enter club: " << canEnter << endl;    // true

    // ================================================================
    // SECTION 4: BITWISE OPERATORS
    // ================================================================
    // Operate on individual bits of integer values.
    // &   AND    |   OR     ^  XOR    ~  NOT
    // <<  left shift  (multiply by 2)
    // >>  right shift (divide by 2)
    // ----------------------------------------------------------------
    cout << "\n=== BITWISE OPERATORS ===" << endl;

    int m = 12, n = 10;   // 12 = 1100₂,  10 = 1010₂

    cout << "m  = " << m << " (binary: 1100)\n";
    cout << "n  = " << n << " (binary: 1010)\n";
    cout << "m & n  = " << (m & n)   << "  (1000 = 8)  AND bit-by-bit\n";
    cout << "m | n  = " << (m | n)   << "  (1110 = 14) OR  bit-by-bit\n";
    cout << "m ^ n  = " << (m ^ n)   << "  (0110 = 6)  XOR bit-by-bit\n";
    cout << "~m     = " << (~m)      << "  (two's complement, = -13)\n";
    cout << "m << 1 = " << (m << 1)  << "  (left shift  = ×2 = 24)\n";
    cout << "m >> 1 = " << (m >> 1)  << "  (right shift = ÷2 = 6)\n";

    // Useful bitwise tricks:
    cout << "\n--- Bitwise Tricks ---\n";
    int num = 7;
    cout << "Is " << num << " even? " << ((num & 1) == 0 ? "yes" : "no") << "\n";  // odd
    cout << "Is " << 8  << " power of 2? " << ((8 & (8-1)) == 0 ? "yes" : "no") << "\n";  // yes

    // ================================================================
    // SECTION 5: ASSIGNMENT OPERATORS
    // ================================================================
    // Shorthand: op= is equivalent to variable = variable op value
    // ----------------------------------------------------------------
    cout << "\n=== ASSIGNMENT OPERATORS ===" << endl;

    int val = 10;
    cout << "val = " << val << endl;     // 10
    val += 5;  cout << "val += 5  → " << val << endl;  // 15
    val -= 3;  cout << "val -= 3  → " << val << endl;  // 12
    val *= 2;  cout << "val *= 2  → " << val << endl;  // 24
    val /= 4;  cout << "val /= 4  → " << val << endl;  // 6
    val %= 4;  cout << "val %= 4  → " << val << endl;  // 2
    val <<= 2; cout << "val <<= 2 → " << val << endl;  // 8  (left shift 2)
    val >>= 1; cout << "val >>= 1 → " << val << endl;  // 4  (right shift 1)

    // ================================================================
    // SECTION 6: INCREMENT / DECREMENT
    // ================================================================
    // Pre-increment  (++x): increment first, then use the value
    // Post-increment (x++): use the value first, then increment
    // ----------------------------------------------------------------
    cout << "\n=== INCREMENT / DECREMENT ===" << endl;

    int c = 5;
    cout << "c   = " << c   << endl;   // 5
    cout << "c++ = " << c++ << endl;   // 5  (post: returns old value)
    cout << "c   = " << c   << endl;   // 6  (now incremented)
    cout << "++c = " << ++c << endl;   // 7  (pre: increments first, returns new value)
    cout << "c-- = " << c-- << endl;   // 7  (post-decrement)
    cout << "c   = " << c   << endl;   // 6

    // ================================================================
    // SECTION 7: TERNARY (CONDITIONAL) OPERATOR
    // ================================================================
    // Syntax: condition ? value_if_true : value_if_false
    // Compact substitute for simple if-else expressions.
    // ----------------------------------------------------------------
    cout << "\n=== TERNARY OPERATOR ===" << endl;

    int score = 75;
    string grade = (score >= 90) ? "A" :
                   (score >= 80) ? "B" :
                   (score >= 70) ? "C" : "F";
    cout << "Score " << score << " → Grade: " << grade << endl;    // C

    int bigger = (a > b) ? a : b;
    cout << "max(" << a << ", " << b << ") = " << bigger << endl;  // 5

    // ================================================================
    // SECTION 8: sizeof OPERATOR
    // ================================================================
    // Returns the size (in bytes) of a type or variable at compile time.
    // ----------------------------------------------------------------
    cout << "\n=== sizeof OPERATOR ===" << endl;
    cout << "sizeof(int)    = " << sizeof(int)    << " bytes\n";
    cout << "sizeof(double) = " << sizeof(double) << " bytes\n";
    cout << "sizeof(char)   = " << sizeof(char)   << " bytes\n";
    cout << "sizeof(bool)   = " << sizeof(bool)   << " bytes\n";
    cout << "sizeof(long long) = " << sizeof(long long) << " bytes\n";

    // sizeof an array gives total bytes, not the number of elements
    int arr[] = {1, 2, 3, 4, 5};
    cout << "sizeof(arr)    = " << sizeof(arr) << " bytes (5 ints × 4 = 20)\n";
    cout << "arr length     = " << sizeof(arr) / sizeof(arr[0]) << " elements\n";

    return 0;
}
// ============================================================
// KEY TAKEAWAYS
//   • Integer division truncates (5/2 = 2, not 2.5)
//   • Use & with 1 to check even/odd (fast alternative to %)
//   • Left shift (<<1) ≡ ×2; right shift (>>1) ≡ ÷2 (for positive ints)
//   • Pre-increment is slightly more efficient in complex types (e.g., iterators)
// ============================================================
