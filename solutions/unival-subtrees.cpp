/*
Daily Coding Problem #8: Unival Subtrees

This problem was asked by Google.

A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.

Given the root to a binary tree, count the number of unival subtrees.

For example, the following tree has 6 unival subtrees:

   0
  / \
 1   0
    / \
   1   0
  / \   \
 1   1   0

*/

#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
   int val;
   Node* left = nullptr;
   Node* right = nullptr;
   Node(int _val) : val(_val) {}
};


/*
To determine what Nodes are roots of unival subtrees, I check:
- if the root is a leaf (true)
- if not, the root's children must be equal to it, and they must be unival subtrees themselves
(null nodes also return true for recursion purposes)

I'm  also tracking nodes I've already called the function on with a map. This way every time the
function is called it doesn't have to recurse all the way down the tree. Now each node will have
this function called on it at most twice.
*/
unordered_map<Node*, bool> seen;

bool isUnivalSubtree(Node* root) {
   // check in the map to see if the function has been called on this node before
   if(seen.find(root) != seen.end()) {
      return seen[root];
   }
   if(root == nullptr) {
      return true;
   }
   if(root->left == nullptr && root->right == nullptr) {
      seen.emplace(root, true);
      return true;
   }

   bool ret = true;
   if(root->left != nullptr && root->left->val != root->val) {
      ret = false;
   }
   if(root->right != nullptr && root->right->val != root->val) {
      ret = false;
   }
   if(ret) {
      ret = isUnivalSubtree(root->left) && isUnivalSubtree(root->right);
   }
   // insert answer into map for future use
   seen.emplace(root, ret);
   return ret;
}

// O(n) solution
int solution(Node* root) {
   if(root == nullptr) {
      return 0;
   }
   return (isUnivalSubtree(root) ? 1 : 0) + solution(root->left) + solution(root->right);
}

int main() {
   Node* root = new Node(0);
   root->left = new Node(1);
   root->right = new Node(0);
   root->right->left = new Node(1);
   root->right->right = new Node(0);
   root->right->left->left = new Node(1);
   root->right->left->right = new Node(1);
   root->right->right->right = new Node(0);

   cout << solution(root) << endl;

   return 0;
}