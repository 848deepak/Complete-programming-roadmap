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

int main() {
    int arr[10] = {1, 2, 3, 4, 5};
    int n = 5;
    int position = 2;
    int value = 99;

    for (int i = n; i > position; i--) {
        arr[i] = arr[i - 1];
    }
    arr[position] = value;
    n++;

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
