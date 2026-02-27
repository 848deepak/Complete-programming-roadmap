/*
Topic: Data Structures and Algorithms
Learning Goal: Understand this concept with a runnable example.
Approach: Read main() first, then helper function(s), then modify sample input.
Time Complexity: Analyze the core operation in this file while practicing.
Space Complexity: Check recursion/auxiliary data structure usage.
How to Run: Compile and run this file; verify output shown in terminal.
Practice Task: Change inputs and test at least 3 edge cases.
*/

#include <iostream>
using namespace std;

class Stack {
    int arr[100];
    int top;

public:
    Stack() : top(-1) {}

    void push(int value) {
        if (top == 99) return;
        arr[++top] = value;
    }

    void pop() {
        if (top == -1) return;
        top--;
    }

    int peek() {
        if (top == -1) return -1;
        return arr[top];
    }
};

int main() {
    Stack stack;
    stack.push(10);
    stack.push(20);
    cout << stack.peek() << endl;
    stack.pop();
    cout << stack.peek() << endl;
    return 0;
}
