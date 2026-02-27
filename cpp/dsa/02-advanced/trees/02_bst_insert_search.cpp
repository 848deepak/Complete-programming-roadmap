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

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

Node* insertNode(Node* root, int value) {
    if (root == nullptr) return new Node(value);
    if (value < root->data) root->left = insertNode(root->left, value);
    else root->right = insertNode(root->right, value);
    return root;
}

bool searchNode(Node* root, int target) {
    if (root == nullptr) return false;
    if (root->data == target) return true;
    if (target < root->data) return searchNode(root->left, target);
    return searchNode(root->right, target);
}

int main() {
    Node* root = nullptr;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int value : values) root = insertNode(root, value);

    int target = 60;
    cout << "Search " << target << ": " << (searchNode(root, target) ? "Found" : "Not Found") << endl;
    return 0;
}

/*
Sample Output:
Search 60: Found
*/
