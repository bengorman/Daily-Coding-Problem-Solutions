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
    front = 0x0;
    back = 0x0;
}

void XORLinkedList::add(int val) {
    Node* newNode = new Node(val);
    if(front == nullptr) {
        front = newNode;
    }

    // iterate to end position
    Node* current = front;
    Node* next = current->both;
    Node* prev;
    while(next != nullptr) {
        prev = current;
        current = next;
        next = (Node*)((uintptr_t)prev ^ (uintptr_t)current->both);
    }

    // insert node, updating prev node's both
    newNode->both = current;
    current->both = (Node*)((uintptr_t)current->both ^ (uintptr_t)newNode);
}

Node* XORLinkedList::get(int index) {
    Node* current = front;
    Node* next = current->both;
    Node* prev;
    for(int i = 0; i < index; i++) {
        prev = current;
        current = next;
        next = (Node*)((uintptr_t)prev ^ (uintptr_t)current->both);
    }
}

int main() {
    XORLinkedList xll;
    xll.add(2);
    xll.add(4);
    xll.add(6);
    cout << xll.get(1) << endl; //get second element
    return 0;
}