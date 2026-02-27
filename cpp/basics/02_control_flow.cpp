// ============================================================
// MODULE 02 | C++ BASICS → Control Flow
// ============================================================
// DESCRIPTION:
//   Covers all branching and looping constructs in C++:
//   if-else, switch, for, while, do-while, break, continue,
//   nested loops for patterns.
//
// COMPILE & RUN:
//   g++ -std=c++17 02_control_flow.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   === IF-ELSE ===
//   Grade: C
//   2024 is a leap year
//   === SWITCH ===
//   Wednesday
//   ...
// ============================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {

    // ================================================================
    // SECTION 1: IF / ELSE-IF / ELSE
    // ================================================================
    // Evaluates conditions from top to bottom, enters the first true block.
    // ----------------------------------------------------------------
    cout << "=== IF-ELSE ===" << endl;

    int marks = 72;

    if      (marks >= 90) cout << "Grade: A\n";   // 90–100
    else if (marks >= 80) cout << "Grade: B\n";   // 80–89
    else if (marks >= 70) cout << "Grade: C\n";   // 70–79  ← prints this
    else if (marks >= 60) cout << "Grade: D\n";   // 60–69
    else                  cout << "Grade: F\n";   // below 60

    // Ternary operator: condition ? value_if_true : value_if_false
    int year  = 2024;
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    cout << year << (leap ? " is" : " is NOT") << " a leap year\n";

    // ================================================================
    // SECTION 2: SWITCH STATEMENT
    // ================================================================
    // Better than chained if-else when comparing a variable to constants.
    // ALWAYS use 'break' to prevent fall-through to the next case.
    // ----------------------------------------------------------------
    cout << "\n=== SWITCH ===" << endl;

    int day = 3;   // 1=Mon, 2=Tue, ..., 7=Sun

    switch (day) {
        case 1:  cout << "Monday\n";    break;
        case 2:  cout << "Tuesday\n";   break;
        case 3:  cout << "Wednesday\n"; break;   // ← prints this
        case 4:  cout << "Thursday\n";  break;
        case 5:  cout << "Friday\n";    break;
        case 6:  cout << "Saturday\n";  break;
        case 7:  cout << "Sunday\n";    break;
        default: cout << "Invalid day\n";         // handles out-of-range values
    }

    // ================================================================
    // SECTION 3: FOR LOOP
    // ================================================================
    // Best when the number of iterations is known in advance.
    // Syntax: for (init; condition; increment)
    // ----------------------------------------------------------------
    cout << "\n=== FOR LOOP ===" << endl;

    // Classic for loop: sum of 1 to 100
    int sum = 0;
    for (int i = 1; i <= 100; i++) sum += i;
    cout << "Sum 1–100 = " << sum << endl;    // Formula: n*(n+1)/2 = 5050

    // Range-based for (C++11): iterate over a collection
    vector<string> langs = {"C++", "Java", "Python"};
    for (const string& lang : langs) cout << lang << " ";
    cout << endl;

    // ================================================================
    // SECTION 4: WHILE LOOP
    // ================================================================
    // Use when the number of iterations is NOT known in advance.
    // The condition is checked BEFORE each iteration.
    // ----------------------------------------------------------------
    cout << "\n=== WHILE ===" << endl;

    int p = 1;
    while (p < 1000) {
        cout << p << " ";   // powers of 2: 1 2 4 8 16 ... 512
        p *= 2;
    }
    cout << endl;

    // ================================================================
    // SECTION 5: DO-WHILE LOOP
    // ================================================================
    // The body executes AT LEAST ONCE because the condition is checked AFTER.
    // Useful for menus and input validation.
    // ----------------------------------------------------------------
    cout << "\n=== DO-WHILE ===" << endl;

    int n = 1;
    do {
        cout << n << " ";   // 1 2 3 4 5
        n++;
    } while (n <= 5);
    cout << endl;

    // ================================================================
    // SECTION 6: BREAK AND CONTINUE
    // ================================================================
    // break    → immediately exits the current loop
    // continue → skips the rest of the current iteration
    // ----------------------------------------------------------------
    cout << "\n=== BREAK ===" << endl;

    // Find the first multiple of 21 in [1, 100]
    for (int i = 1; i <= 100; i++) {
        if (i % 21 == 0) {
            cout << "First multiple of 21: " << i << "\n";  // 21
            break;   // no need to continue scanning
        }
    }

    // Print only odd numbers using continue
    cout << "Odd 1–15: ";
    for (int i = 1; i <= 15; i++) {
        if (i % 2 == 0) continue;   // skip even numbers
        cout << i << " ";
    }
    cout << endl;

    // ================================================================
    // SECTION 7: NESTED LOOPS — PATTERN PRINTING
    // ================================================================
    // Outer loop controls rows, inner loop controls columns.
    // ----------------------------------------------------------------
    cout << "\n=== PATTERNS ===" << endl;

    int rows = 5;

    // Pattern 1: Right-angle triangle of stars
    cout << "Right-angle triangle:\n";
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) cout << "* ";
        cout << "\n";
    }

    // Pattern 2: Pyramid (centred triangle)
    cout << "\nPyramid:\n";
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= rows - i; j++) cout << "  ";   // leading spaces
        for (int j = 1; j <= 2 * i - 1; j++) cout << "* ";  // stars
        cout << "\n";
    }

    // Pattern 3: Inverted triangle
    cout << "\nInverted triangle:\n";
    for (int i = rows; i >= 1; i--) {
        for (int j = 1; j <= i; j++) cout << "* ";
        cout << "\n";
    }

    // Pattern 4: Number triangle
    cout << "\nNumber triangle:\n";
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) cout << j << " ";
        cout << "\n";
    }

    return 0;
}
// ============================================================
// COMPLEXITY ANALYSIS
//   Time  : O(n²) for pattern loops, O(n) for single loops
//   Space : O(1) — no extra space used
// ============================================================
