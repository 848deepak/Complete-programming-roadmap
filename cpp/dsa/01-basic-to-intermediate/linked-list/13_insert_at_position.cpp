/*
Topic: Data Structures and Algorithms
Learning Goal: Insert a node at any valid position in a singly linked list.
Approach: Traverse to (position - 1), relink pointers, handle head as edge case.
Time Complexity: O(n)
Space Complexity: O(1)
How to Run: g++ -std=c++17 13_insert_at_position.cpp -o out && ./out
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    explicit Node(int value) : data(value), next(nullptr) {}
};

void printList(Node* head) {
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL\n";
}

void insertAtEnd(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next) current = current->next;
    current->next = newNode;
}

bool insertAtPosition(Node*& head, int value, int position) {
    if (position < 0) return false;

    if (position == 0) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        return true;
    }

    Node* current = head;
    for (int index = 0; index < position - 1; index++) {
        if (!current) return false;
        current = current->next;
    }

    if (!current) return false;

    Node* newNode = new Node(value);
    newNode->next = current->next;
    current->next = newNode;
    return true;
}

void freeList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;

    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtEnd(head, 40);

    cout << "Before insert: ";
    printList(head);

    bool ok = insertAtPosition(head, 30, 2);
    cout << "Insert 30 at position 2: " << (ok ? "Success" : "Failed") << "\n";
    printList(head);

    ok = insertAtPosition(head, 5, 0);
    cout << "Insert 5 at position 0: " << (ok ? "Success" : "Failed") << "\n";
    printList(head);

    ok = insertAtPosition(head, 100, 10);
    cout << "Insert 100 at position 10: " << (ok ? "Success" : "Failed") << "\n";
    printList(head);

    freeList(head);
    return 0;
}
