/*
Daily Coding Problem #20: Intersecting Linked Lists

This problem was asked by Google.

Given two singly linked lists that intersect at some point, find the intersecting node. The lists are non-cyclical.

For example, given A = 3 -> 7 -> 8 -> 10 and B = 99 -> 1 -> 8 -> 10, return the node with value 8.

In this example, assume nodes with the same value are the exact same node objects.

Do this in O(M + N) time (where M and N are the lengths of the lists) and constant space.
*/

#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v) {
        next = nullptr;
    }
};

class LinkedList {
public:
    Node* front;
    int length;
    LinkedList() {
        front = nullptr;
        length = 0;
    }
    void push_back(Node* newNode) {
        if(front == nullptr) {
            front = newNode;
        } else {
            Node* current = front;
            while(current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }
};

/*
This solution relies on the fact that for lists of equal length, we can compare node for node.
For example:
3      99   The lists are of equal length (4), so we can compar
 \     /     * 3 == 99
  7   1      * 7 == 1
   \ /       * 8 == 8
    8       And we have found the answer.
    |
    10

We skip nodes in the longer list until both are of equal length, then use the above method.
*/
Node* solution(LinkedList list1, LinkedList list2) {
    Node* one = list1.front;
    Node* two = list2.front;
    int match = list1.length - list2.length;
    while(match > 0) {
        one = one->next;
        match--;
    }
    while(match < 0) {
        two = two->next;
        match++;
    }
    while(one != nullptr && two != nullptr) {
        if(one == two) {
            return one;
        }
        one = one->next;
        two = two->next;
    }
    return nullptr;
}

int main() {
    LinkedList list1, list2;
    list1.push_back(new Node(3));
    list1.push_back(new Node(7));
    list2.push_back(new Node(99));
    list2.push_back(new Node(1));
    Node* intersect = new Node(8);
    list1.push_back(intersect);
    list2.push_back(intersect);
    intersect = new Node(10);
    list1.push_back(intersect);
    list2.push_back(intersect);

    Node* ret = solution(list1, list2);
    cout << (ret ? ret->val : -1) << endl;
    return 0;
}