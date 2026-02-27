// ============================================================
// DSA | C++ → Stack: Balanced Parentheses
// ============================================================
// DESCRIPTION:
//   Classic stack application — check if brackets in a string
//   are correctly matched and balanced.
//
// PROBLEM:
//   Given string s containing '(', ')', '{', '}', '[', ']',
//   determine if the input is valid.
//   Valid means: each open bracket is closed by the correct
//   close bracket in the correct order.
//
// COMPILE & RUN:
//   g++ -std=c++17 03_balanced_parentheses.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   "()[]{}" → BALANCED
//   "([)]"   → NOT BALANCED
// ============================================================

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// ============================================================
// SECTION 1: BASIC BALANCED PARENTHESES CHECK
// ============================================================
// Algorithm:
//   For each character in s:
//     - Opening bracket → push onto stack
//     - Closing bracket → if stack empty or top doesn't match → invalid
//                         else pop from stack
//   After full scan: valid only if stack is EMPTY
//
// Time: O(n)  |  Space: O(n) worst case (all opening brackets)
// ------------------------------------------------------------ 

/**
 * Returns true if the bracket string s is balanced.
 *
 * @param s  String containing brackets (and possibly other chars)
 */
bool isBalanced(const string& s) {
    stack<char> stk;

    // Map each closing bracket to its corresponding opening bracket
    unordered_map<char, char> matchFor = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            stk.push(ch);              // opening bracket → push
        } else if (matchFor.count(ch)) {
            // Closing bracket
            if (stk.empty() || stk.top() != matchFor[ch]) {
                return false;          // no matching open, or wrong type
            }
            stk.pop();                 // matched → pop
        }
        // other characters (letters, digits, spaces) are ignored
    }

    return stk.empty();   // valid only if all opens were matched
}

// ============================================================
// SECTION 2: MINIMUM BRACKET REVERSALS TO BALANCE
// ============================================================
// Given a string of only { and }, find minimum reversals to balance.
// Example: "}}{" → 3 reversals needed.
//
// Algorithm:
//   1. Use a stack to cancel matched pairs.
//   2. After processing, unmatched { and } remain.
//   3. If we have 'a' unmatched { and 'b' unmatched }:
//      Reversals = ceil(a/2) + ceil(b/2)
//
// Time: O(n)  |  Space: O(n)
// ------------------------------------------------------------ 

int minReversals(const string& s) {
    if (s.size() % 2 != 0) return -1;   // odd length → never balanceable

    stack<char> stk;
    for (char ch : s) {
        if (ch == '{') {
            stk.push(ch);
        } else {  // ch == '}'
            if (!stk.empty() && stk.top() == '{')
                stk.pop();    // matched pair — cancel out
            else
                stk.push(ch); // unmatched } — push
        }
    }

    // stk holds unmatched: some { at bottom, some } at top
    int unmatched_open  = 0;   // count of {
    int unmatched_close = 0;   // count of }

    while (!stk.empty()) {
        if (stk.top() == '{') unmatched_open++;
        else                  unmatched_close++;
        stk.pop();
    }

    // ceil(a/2) + ceil(b/2) = (a/2) + (b/2) + (a%2) + (b%2) / 2
    // Simplified: (a + 1) / 2 + (b + 1) / 2
    return (unmatched_open + 1) / 2 + (unmatched_close + 1) / 2;
}

// ============================================================
// SECTION 3: SCORE OF PARENTHESES
// ============================================================
// Given balanced "()", each empty "()" has score 1.
// "AB" has score A + B (concatenation).
// "(A)" has score 2 * A (nesting).
//
// Example: "(())" → 2, "()()" → 2, "(()(()))" → 6
//
// Algorithm: stack of running scores per nesting level.
//
// Time: O(n)  |  Space: O(n)
// ------------------------------------------------------------ 

int scoreOfParentheses(const string& s) {
    stack<int> stk;
    stk.push(0);   // score of current "level"

    for (char ch : s) {
        if (ch == '(') {
            stk.push(0);           // new deeper level starts with score 0
        } else {
            int v = stk.top();     // score accumulated at this depth
            stk.pop();

            int contribution = max(2 * v, 1);   // empty () = 1, nested = 2*inner
            stk.top() += contribution;           // add to enclosing level
        }
    }

    return stk.top();
}

// ============================================================
// SECTION 4: FIND LONGEST VALID PARENTHESES SUBSTRING
// ============================================================
// Given a string of '(' and ')', find the length of the longest
// balanced (valid) substring.
//
// Algorithm:
//   Stack stores indices. Push -1 as a base index.
//   For '(' → push index onto stack.
//   For ')' → pop one element:
//     - if stack empty after pop → push current index as new base
//     - else current_length = i - stack.top()
//
// Time: O(n)  |  Space: O(n)
// ------------------------------------------------------------ 

int longestValidParentheses(const string& s) {
    stack<int> stk;
    stk.push(-1);   // base index
    int maxLen = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            stk.push(i);           // push index of '('
        } else {
            stk.pop();             // pop matching '(', or the base index

            if (stk.empty()) {
                stk.push(i);       // current ')' is unmatched → new base
            } else {
                maxLen = max(maxLen, i - stk.top());
            }
        }
    }

    return maxLen;
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- isBalanced ---
    cout << "=== BALANCED PARENTHESES ===" << "\n";
    vector<pair<string, bool>> tests = {
        {"()",            true},
        {"()[]{}",        true},
        {"([{}])",        true},
        {"([)]",          false},
        {"{[]",           false},
        {"",              true},   // empty string is balanced
        {"(((",           false},
        {"((()))",        true},
        {"int main() { return 0; }", true}   // code with other chars
    };

    for (auto& [s, expected] : tests) {
        bool result = isBalanced(s);
        cout << "  \"" << s << "\"\n"
             << "    → " << (result ? "BALANCED" : "NOT BALANCED")
             << (result == expected ? " ✓" : " ✗")
             << "\n";
    }

    // --- minReversals ---
    cout << "\n=== MINIMUM REVERSALS TO BALANCE ===" << "\n";
    vector<pair<string, int>> rTests = {
        {"}}{{",   2},   // "}}{{"  → swap 1st and last: "{{" + "}}" → still 2
        {"}}",     1},
        {"{{}}",   0},   // already balanced
        {"{}{}",   0},
        {"{{{",   -1},   // odd length
        {"}}{{}}",  1}
    };
    for (auto& [s, expected] : rTests) {
        int result = minReversals(s);
        cout << "  \"" << s << "\" → " << result
             << (result == expected ? " ✓" : " ✗ (expected " + to_string(expected) + ")")
             << "\n";
    }

    // --- scoreOfParentheses ---
    cout << "\n=== SCORE OF PARENTHESES ===" << "\n";
    vector<pair<string, int>> sTests = {
        {"()",        1},
        {"(())",      2},
        {"()()",      2},
        {"(()(()))",  6}
    };
    for (auto& [s, expected] : sTests) {
        int result = scoreOfParentheses(s);
        cout << "  \"" << s << "\" → " << result
             << (result == expected ? " ✓" : " ✗")
             << "\n";
    }

    // --- longestValidParentheses ---
    cout << "\n=== LONGEST VALID PARENTHESES ===" << "\n";
    vector<pair<string, int>> lTests = {
        {"(()",        2},
        {")()())",     4},
        {"",           0},
        {"()(())",     6},
        {"((((",        0}
    };
    for (auto& [s, expected] : lTests) {
        int result = longestValidParentheses(s);
        cout << "  \"" << s << "\" → " << result
             << (result == expected ? " ✓" : " ✗")
             << "\n";
    }

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   isBalanced              : O(n) time, O(n) space
//   minReversals            : O(n) time, O(n) space
//   scoreOfParentheses      : O(n) time, O(n) space
//   longestValidParentheses : O(n) time, O(n) space
// ============================================================
