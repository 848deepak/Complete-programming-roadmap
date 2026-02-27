/*
Topic: Data Structures and Algorithms
Learning Goal: Understand this concept with a runnable example.
Approach: Read main() first, then helper function(s), then modify sample input.
Time Complexity: Analyze the core operation in this file while practicing.
Space Complexity: Check recursion/auxiliary data structure usage.
How to Run: Compile and run this file; verify output shown in terminal.
Practice Task: Change inputs and test at least 3 edge cases.
*/

class StackUsingArray {
    private int[] stack = new int[100];
    private int top = -1;

    public void push(int value) {
        if (top < 99) stack[++top] = value;
    }

    public void pop() {
        if (top >= 0) top--;
    }

    public int peek() {
        return (top >= 0) ? stack[top] : -1;
    }

    public static void main(String[] args) {
        StackUsingArray stack = new StackUsingArray();
        stack.push(10);
        stack.push(20);
        System.out.println(stack.peek());
        stack.pop();
        System.out.println(stack.peek());
    }
}
