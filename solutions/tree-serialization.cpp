/*
Daily Coding Problem #3: Tree Serialization

This problem was asked by Google.

Given the root to a binary tree, implement serialize(root), which serializes the tree into a
string, and deserialize(s), which deserializes the string back into the tree.
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

/*
I chose the values of each node to be  a char.
It could be any data type, but I made it a char for the sake of simplicity.
*/
struct Node {
    char val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(char _val) : val(_val) {}
};

/*
O(n) serialize function

Serialize top-down. ie root, root->left, root->right, root->left->left, etc.

I decided to go with this method because it is easily reversible. The deserialize function moves
top-down as well, and therefore does not need to know the depth of the tree (a pre-, post-, or
in-order traversal would need to know depth to know which nodes are leaves and when to move back
up the tree).
*/ 
vector<char> serialize(Node* root) {
    vector<char> v;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        if(q.front() == nullptr) {
            // empty spaces in the tree are tracked with underscores
            v.push_back('_');
            q.pop();
            continue;
        }
        v.push_back(q.front()->val);
        q.push(q.front()->left);
        q.push(q.front()->right);
        q.pop();
    }
    return v;
}

Node* deserialize(vector<char> v) {
    queue<Node*> q;
    int i = 0;
    Node* root = new Node(v[i++]);
    q.push(root);
    Node* newNode;
    while(!q.empty()) {
        newNode = nullptr;
        if(v[i] != '_') {
            newNode = new Node(v[i]);
            q.push(newNode);
        }
        q.front()->left = newNode;
        i++;
        newNode = nullptr;
        if(v[i] != '_') {
            newNode = new Node(v[i]);
            q.push(newNode);
        }
        q.front()->right = newNode;
        i++;
        q.pop();
    }
    return root;
}

/*
I only made one testcase for the sake of time.
Feel free to link against this file with your own tree generation code,
or just change/add testcases in main.
*/
int main() {
    Node* root = new Node('A');
    root->left = new Node('B');
    root->right = new Node('C');
    root->left->left = new Node('D');
    // skip root->left->right 'E'
    root->right->left = new Node('F');
    root->right->right = new Node('G');
    
    vector<char> serialized = serialize(root);
    for(char c : serialized) {
        cout << c;
    }
    cout << endl;

    root = deserialize(serialized);
    printf("%c\n", root->val);
    printf("%c %c\n", root->left->val, root->right->val);
    printf("%c %s %c %c\n", root->left->left->val, "_", root->right->left->val, root->right->right->val);

    return 0;
}