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

class Queue {
    int arr[100];
    int front;
    int rear;

public:
    Queue() : front(0), rear(-1) {}

    void enqueue(int value) {
        if (rear == 99) return;
        arr[++rear] = value;
    }

    void dequeue() {
        if (front > rear) return;
        front++;
    }

    int peek() {
        if (front > rear) return -1;
        return arr[front];
    }
};

int main() {
    Queue queue;
    queue.enqueue(5);
    queue.enqueue(15);
    cout << queue.peek() << endl;
    queue.dequeue();
    cout << queue.peek() << endl;
    return 0;
}
