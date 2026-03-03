/*
Topic: Data Structures and Algorithms
Learning Goal: Delete a node at any valid position in a singly linked list.
Approach: Traverse to (position - 1), bypass target node, handle head as edge case.
Time Complexity: O(n)
Space Complexity: O(1)
How to Run: g++ -std=c++17 14_delete_from_position.cpp -o out && ./out
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

bool deleteFromPosition(Node*& head, int position) {
    if (position < 0 || !head) return false;

    if (position == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;
    for (int index = 0; index < position - 1; index++) {
        if (!current) return false;
        current = current->next;
    }

    if (!current || !current->next) return false;

    Node* target = current->next;
    current->next = target->next;
    delete target;
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
    insertAtEnd(head, 30);
    insertAtEnd(head, 40);

    cout << "Before delete: ";
    printList(head);

    bool ok = deleteFromPosition(head, 2);
    cout << "Delete position 2: " << (ok ? "Success" : "Failed") << "\n";
    printList(head);

    ok = deleteFromPosition(head, 0);
    cout << "Delete position 0: " << (ok ? "Success" : "Failed") << "\n";
    printList(head);

    ok = deleteFromPosition(head, 10);
    cout << "Delete position 10: " << (ok ? "Success" : "Failed") << "\n";
    printList(head);

    freeList(head);
    return 0;
}
