// ============================================================
// MODULE 06 | C++ BASICS → Pattern Programs
// ============================================================
// DESCRIPTION:
//   10 classic pattern programs using nested loops.
//   Patterns test loop control, logic, and spatial thinking —
//   frequently asked in interviews and entrance exams.
//
// COMPILE & RUN:
//   g++ -std=c++17 06_patterns.cpp -o out && ./out
//
// COMPLEXITY (all patterns):
//   Time  : O(n²) — two nested loops of size n
//   Space : O(1)  — no extra data structures
// ============================================================

#include <iostream>
using namespace std;

int main() {
    int n = 5;   // Number of rows (change to see different sizes)

    // ================================================================
    // PATTERN 1: Right-Angle Triangle (Stars)
    // ================================================================
    //   *
    //   * *
    //   * * *
    //   * * * *
    //   * * * * *
    // ----------------------------------------------------------------
    cout << "PATTERN 1: Right-Angle Triangle\n";
    for (int i = 1; i <= n; i++) {           // row loop: 1 to n
        for (int j = 1; j <= i; j++)         // column: print i stars
            cout << "* ";
        cout << "\n";
    }

    // ================================================================
    // PATTERN 2: Inverted Right-Angle Triangle
    // ================================================================
    //   * * * * *
    //   * * * *
    //   * * *
    //   * *
    //   *
    // ----------------------------------------------------------------
    cout << "\nPATTERN 2: Inverted Triangle\n";
    for (int i = n; i >= 1; i--) {           // row loop: n down to 1
        for (int j = 1; j <= i; j++)
            cout << "* ";
        cout << "\n";
    }

    // ================================================================
    // PATTERN 3: Pyramid (Centred)
    // ================================================================
    //           *
    //         * * *
    //       * * * * *
    //     * * * * * * *
    //   * * * * * * * * *
    // ----------------------------------------------------------------
    cout << "\nPATTERN 3: Pyramid\n";
    for (int i = 1; i <= n; i++) {
        // Print (n-i) leading spaces to centre the row
        for (int j = 1; j <= n - i; j++) cout << "  ";
        // Print (2i - 1) stars
        for (int j = 1; j <= 2 * i - 1; j++) cout << "* ";
        cout << "\n";
    }

    // ================================================================
    // PATTERN 4: Inverted Pyramid
    // ================================================================
    //   * * * * * * * * *
    //     * * * * * * *
    //       * * * * *
    //         * * *
    //           *
    // ----------------------------------------------------------------
    cout << "\nPATTERN 4: Inverted Pyramid\n";
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) cout << "  ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << "* ";
        cout << "\n";
    }

    // ================================================================
    // PATTERN 5: Diamond
    // ================================================================
    // Upper half (pyramid) + Lower half (inverted pyramid)
    // ----------------------------------------------------------------
    cout << "\nPATTERN 5: Diamond\n";
    // Upper half (including middle row)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << "*";
        cout << "\n";
    }
    // Lower half
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << "*";
        cout << "\n";
    }

    // ================================================================
    // PATTERN 6: Hollow Square
    // ================================================================
    //   * * * * *
    //   *       *
    //   *       *
    //   *       *
    //   * * * * *
    // ----------------------------------------------------------------
    cout << "\nPATTERN 6: Hollow Square\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // Print star on borders only; space inside
            if (i == 1 || i == n || j == 1 || j == n)
                cout << "* ";
            else
                cout << "  ";
        }
        cout << "\n";
    }

    // ================================================================
    // PATTERN 7: Number Triangle
    // ================================================================
    //   1
    //   1 2
    //   1 2 3
    //   1 2 3 4
    //   1 2 3 4 5
    // ----------------------------------------------------------------
    cout << "\nPATTERN 7: Number Triangle\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++)
            cout << j << " ";
        cout << "\n";
    }

    // ================================================================
    // PATTERN 8: Floyd's Triangle (consecutive numbers)
    // ================================================================
    //   1
    //   2  3
    //   4  5  6
    //   7  8  9  10
    //   11 12 13 14 15
    // ----------------------------------------------------------------
    cout << "\nPATTERN 8: Floyd's Triangle\n";
    int num = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++)
            cout << num++ << " ";
        cout << "\n";
    }

    // ================================================================
    // PATTERN 9: Alphabet Triangle
    // ================================================================
    //   A
    //   A B
    //   A B C
    //   A B C D
    //   A B C D E
    // ----------------------------------------------------------------
    cout << "\nPATTERN 9: Alphabet Triangle\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            cout << (char)('A' + j) << " ";   // 'A' + 0 = 'A', + 1 = 'B', ...
        cout << "\n";
    }

    // ================================================================
    // PATTERN 10: Pascal's Triangle
    // ================================================================
    //       1
    //      1 1
    //     1 2 1
    //    1 3 3 1
    //   1 4 6 4 1
    // Each element = element directly above + element above-left
    // (Binomial coefficients: C(row, col))
    // ----------------------------------------------------------------
    cout << "\nPATTERN 10: Pascal's Triangle\n";
    for (int i = 0; i < n; i++) {
        // Print leading spaces for centering
        for (int j = 0; j < n - i - 1; j++) cout << " ";

        int val = 1;   // start of each row is always 1
        for (int j = 0; j <= i; j++) {
            cout << val << " ";
            val = val * (i - j) / (j + 1);   // compute next binomial coefficient
        }
        cout << "\n";
    }

    return 0;
}
