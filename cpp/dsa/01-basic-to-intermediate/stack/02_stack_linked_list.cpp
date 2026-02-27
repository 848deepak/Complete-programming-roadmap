// ============================================================
// DSA | C++ → Stack: Implementation Using Linked List
// ============================================================
// DESCRIPTION:
//   Stack implementation using a singly linked list.
//   Advantage over array: dynamic size — no capacity limit.
//   The top of the stack = head of the linked list.
//
// STACK OPERATIONS:
//   push(x)  → insert at head   O(1)
//   pop()    → remove from head  O(1)
//   peek()   → read head value   O(1)
//   isEmpty()→ check if empty    O(1)
//
// COMPILE & RUN:
//   g++ -std=c++17 02_stack_linked_list.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// ============================================================
// NODE STRUCTURE
// ============================================================
struct Node {
    int   data;
    Node* next;
    explicit Node(int val) : data(val), next(nullptr) {}
};

// ============================================================
// STACK USING LINKED LIST
// ============================================================

class StackLL {
private:
    Node* top_;    // head of list = top of stack
    int   size_;   // current number of elements

public:
    StackLL() : top_(nullptr), size_(0) {}

    /** 
     * Destructor: free all nodes to prevent memory leaks.
     * Called automatically when stack goes out of scope.
     */
    ~StackLL() {
        while (top_) {
            Node* tmp = top_;
            top_      = top_->next;
            delete tmp;
        }
    }

    /**
     * Push: creates a new node and places it at the top.
     * Time: O(1)  |  Space: O(1)
     */
    void push(int val) {
        Node* node = new Node(val);
        node->next = top_;    // new node points to current top
        top_       = node;    // update top to new node
        size_++;
    }

    /**
     * Pop: removes and returns the top element.
     * Throws underflow_error if stack is empty.
     * Time: O(1)  |  Space: O(1)
     */
    int pop() {
        if (empty()) throw underflow_error("Stack underflow: pop() on empty stack");
        Node* tmp = top_;
        int   val = top_->data;
        top_      = top_->next;
        delete tmp;            // free the removed node
        size_--;
        return val;
    }

    /**
     * Peek: returns the top element WITHOUT removing it.
     * Throws underflow_error if empty.
     * Time: O(1)
     */
    int peek() const {
        if (empty()) throw underflow_error("Stack underflow: peek() on empty stack");
        return top_->data;
    }

    bool empty() const { return top_ == nullptr; }
    int  size()  const { return size_; }

    /**
     * Print all elements from top to bottom.
     * Time: O(n)
     */
    void print(const string& label = "") const {
        if (!label.empty()) cout << label << "\n";
        cout << "  TOP → ";
        Node* curr = top_;
        while (curr) {
            cout << "[" << curr->data << "]";
            if (curr->next) cout << " → ";
            curr = curr->next;
        }
        cout << " → NULL  (size=" << size_ << ")\n";
    }
};

// ============================================================
// APPLICATION: REVERSE A STRING USING STACK
// ============================================================
/**
 * Reverses a string by pushing all chars onto a stack then popping.
 * Time: O(n)  |  Space: O(n)
 */
string reverseString(const string& s) {
    StackLL stk;
    for (char c : s) stk.push((int)c);   // push ASCII values

    string result;
    while (!stk.empty()) result += (char)stk.pop();
    return result;
}

// ============================================================
// APPLICATION: EVALUATE POSTFIX EXPRESSION
// ============================================================
/**
 * Evaluates a postfix (RPN) expression like "2 3 + 4 *".
 * Rules: operand → push; operator → pop 2 operands, compute, push result.
 *
 * Time: O(n)  |  Space: O(n)
 */
int evalPostfix(const string& expr) {
    StackLL stk;
    int i = 0, n = (int)expr.size();

    while (i < n) {
        if (expr[i] == ' ') { i++; continue; }   // skip spaces

        if (isdigit(expr[i])) {
            int num = 0;
            while (i < n && isdigit(expr[i])) { num = num * 10 + (expr[i] - '0'); i++; }
            stk.push(num);
        } else {
            // Operator: pop two operands (right operand first)
            int b = stk.pop();   // second operand (popped first!!)
            int a = stk.pop();   // first operand

            switch (expr[i]) {
                case '+': stk.push(a + b); break;
                case '-': stk.push(a - b); break;
                case '*': stk.push(a * b); break;
                case '/': if (b == 0) throw invalid_argument("Division by zero");
                          stk.push(a / b); break;
            }
            i++;
        }
    }

    return stk.pop();
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Basic operations ---
    cout << "=== STACK USING LINKED LIST ===" << "\n";
    StackLL stk;

    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.print("After pushing 10,20,30,40:");

    cout << "  peek() = " << stk.peek()  << "\n";
    cout << "  size() = " << stk.size()  << "\n";

    cout << "\n  Popping elements:\n";
    while (!stk.empty()) {
        cout << "  pop() → " << stk.pop() << "\n";
    }
    stk.print("After all pops:");

    // --- Underflow edge case ---
    cout << "\n=== EDGE: STACK UNDERFLOW ===" << "\n";
    try {
        stk.pop();
    } catch (const underflow_error& e) {
        cout << "  Caught: " << e.what() << "\n";
    }
    try {
        stk.peek();
    } catch (const underflow_error& e) {
        cout << "  Caught: " << e.what() << "\n";
    }

    // --- Application: reverse string ---
    cout << "\n=== APPLICATION: REVERSE STRING ===" << "\n";
    string original = "Hello, World!";
    cout << "  Original : \"" << original          << "\"\n";
    cout << "  Reversed : \"" << reverseString(original) << "\"\n";

    // --- Application: postfix evaluation ---
    cout << "\n=== APPLICATION: POSTFIX EVALUATION ===" << "\n";
    vector<pair<string,int>> exprs = {
        {"2 3 +",         5},     //  2 + 3 = 5
        {"5 1 2 + 4 * + 3 -", 14}, // 5 + (1+2)*4 - 3 = 14
        {"2 3 4 * +",     14},    //  2 + 3*4 = 14
        {"100 2 /",       50}     //  100 / 2 = 50
    };

    for (auto& [expr, expected] : exprs) {
        int result = evalPostfix(expr);
        cout << "  \"" << expr << "\" = " << result
             << (result == expected ? " ✓" : " ✗ (expected " + to_string(expected) + ")")
             << "\n";
    }

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   push   : O(1) time, O(1) space (allocate one node)
//   pop    : O(1) time, O(1) space (free one node)
//   peek   : O(1) time, O(1) space
//   size   : O(1) time
//   print  : O(n) time
//
// LINKED LIST vs ARRAY STACK:
//   Array stack: O(1) amortized, fixed max capacity, faster (cache-friendly)
//   LL stack   : O(1) always, unlimited capacity, slower (pointer chasing)
// ============================================================
