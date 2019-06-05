/*
Daily Coding Problem #6: XOR Linked List

This problem was asked by Google.

An XOR linked list is a more memory efficient doubly linked list.
Instead of each node holding next and prev fields, it holds a field named both, which is an XOR of
the next node and the previous node. Implement an XOR linked list; it has an add(element) which
adds the element to the end, and a get(index) which returns the node at index.
*/

#include <iostream>
#include <stdint.h>

using namespace std;

struct Node {
    int val;
    Node* both = 0x0;
    Node(int _val) : val(_val) {}
};

class XORLinkedList {
public:
    XORLinkedList();
    void add(int val);
    Node* get(int index);
    Node* front;
};

XORLinkedList::XORLinkedList() {
    front = nullptr;
}

void XORLinkedList::add(int val) {
    Node* newNode = new Node(val);
    if(front == nullptr) {
        front = newNode;
    }

    // iterate to end position
    Node* current = front;
    // the front node has no prev, thus both == next (because both == 0 ^ next == next)
    Node* next = current->both;
    Node* prev;
    while(next != nullptr) {
        prev = current;
        current = next;
        // casting to int required for bitwise XOR operation
        next = (Node*)((uintptr_t)prev ^ (uintptr_t)current->both);
    }

    // newNode has no next, so both == prev (current)
    newNode->both = current;
    // add newNode to list by updating current's both pointer by XORing with newNode
    current->both = (Node*)((uintptr_t)current->both ^ (uintptr_t)newNode);
}

Node* XORLinkedList::get(int index) {
    Node* current = front;
    Node* next = current->both;
    Node* prev;
    for(int i = 0; i < index; i++) {
        if(next == 0x0) {
            cout << "ERROR: Index out of bounds" << endl;
            return;
        }
        prev = current;
        current = next;
        next = (Node*)((uintptr_t)prev ^ (uintptr_t)current->both);
    }
    return current;
}

int main() {
    XORLinkedList xll;
    xll.add(2);
    xll.add(4);
    xll.add(6);
    xll.add(8);
    xll.add(10);
    for(int i = 0; i < 6; i++) {
        Node* myNode = xll.get(i);
        cout << myNode->val << endl;
    }
    return 0;
}