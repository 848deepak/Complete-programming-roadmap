// ============================================================
// DSA | C++ → Linked Lists: Singly Linked List Basics
// ============================================================
// DESCRIPTION:
//   A complete singly linked list example in one file:
//   - Insert at beginning/end/position
//   - Delete from beginning/end/position
//   - Search element
//   - Reverse list
//   - Print and free memory
//
// COMPILE & RUN:
//   g++ -std=c++17 01_linked_list.cpp -o out && ./out
// ============================================================

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    explicit Node(int value) : data(value), next(nullptr) {}
};

void printList(Node* head) {
    cout << "  ";
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL\n";
}

void insertAtBeginning(Node*& head, int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
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
        insertAtBeginning(head, value);
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

bool deleteFromBeginning(Node*& head) {
    if (!head) return false;
    Node* temp = head;
    head = head->next;
    delete temp;
    return true;
}

bool deleteFromEnd(Node*& head) {
    if (!head) return false;
    if (!head->next) {
        delete head;
        head = nullptr;
        return true;
    }

    Node* prev = nullptr;
    Node* current = head;
    while (current->next) {
        prev = current;
        current = current->next;
    }

    prev->next = nullptr;
    delete current;
    return true;
}

bool deleteFromPosition(Node*& head, int position) {
    if (position < 0 || !head) return false;
    if (position == 0) return deleteFromBeginning(head);

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

Node* search(Node* head, int key) {
    while (head) {
        if (head->data == key) return head;
        head = head->next;
    }
    return nullptr;
}

void reverseList(Node*& head) {
    Node* prev = nullptr;
    Node* current = head;

    while (current) {
        Node* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    head = prev;
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

    cout << "=== SINGLY LINKED LIST DEMO ===\n";

    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtEnd(head, 30);
    cout << "After insertAtEnd(10,20,30):\n";
    printList(head);

    insertAtBeginning(head, 5);
    cout << "After insertAtBeginning(5):\n";
    printList(head);

    insertAtPosition(head, 25, 2);
    cout << "After insertAtPosition(25, 2):\n";
    printList(head);

    deleteFromBeginning(head);
    cout << "After deleteFromBeginning():\n";
    printList(head);

    deleteFromPosition(head, 2);
    cout << "After deleteFromPosition(2):\n";
    printList(head);

    deleteFromEnd(head);
    cout << "After deleteFromEnd():\n";
    printList(head);

    int key = 20;
    cout << "Search " << key << ": "
         << (search(head, key) ? "Found" : "Not Found") << "\n";

    reverseList(head);
    cout << "After reverseList():\n";
    printList(head);

    freeList(head);
    return 0;
}
