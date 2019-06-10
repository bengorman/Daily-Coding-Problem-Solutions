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
    // start with 0 so next == both for first node and prev == both for last node
    Node* both = 0x0;
    Node(int _val) : val(_val) {}
};

class XORLinkedList {
public:
    XORLinkedList();
    void addWithBack(int val);
    void addWithoutBack(int val);
    Node* get(int index);
    Node* front;
    Node* back;
};

XORLinkedList::XORLinkedList() {
    front = nullptr;
    back = nullptr;
}

/*
This solution assumes the LinkedList has no back pointer
This means the add method must iterate to the back of the list
*/
void XORLinkedList::addWithoutBack(int val) {
    Node* newNode = new Node(val);
    // if first element, set front
    if(front == nullptr) {
        front = newNode;
        return;
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

/*
This solution assumes the LinkedList has a back pointer
A back pointer makes it very easy to append new nodes to the end
*/
void XORLinkedList::addWithBack(int val) {
    Node* newNode = new Node(val);
    // if first element, set front and back
    if(front == nullptr) {
        front = newNode;
        back = newNode;
        return;
    }
    
    // update the last node's both to include the new node
    back->both = (Node*)((uintptr_t)back->both ^ (uintptr_t)newNode);
    // update the new node's both to include the previous node
    newNode->both = back;
    // update back pointer
    back = newNode;
}

Node* XORLinkedList::get(int index) {
    // iterate to index
    Node* current = front;
    // the front node has no prev, thus both == next (because both == 0 ^ next == next)
    Node* next = current->both;
    Node* prev;
    for(int i = 0; i < index; i++) {
        if(next == 0x0) {
            cout << "\tERROR: Index out of bounds" << endl;
            return nullptr;
        }
        prev = current;
        current = next;
        next = (Node*)((uintptr_t)prev ^ (uintptr_t)current->both);
    }
    return current;
}

int main() {
    XORLinkedList xll;
    /* 
    NOTE: cannot call addWithBack after addWithoutBack because addWithoutBack does not update
    back pointer!
    */
    xll.addWithoutBack(2);
    xll.addWithoutBack(4);
    xll.addWithoutBack(6);
    xll.addWithoutBack(8);
    xll.addWithoutBack(10);
    for(int i = 0; i < 6; i++) {
        Node* myNode = xll.get(i);
        if(myNode != nullptr) {
            cout << myNode->val << endl;
        } else {
            cout << "NULL Node" << endl;
        }
    }
    return 0;
}