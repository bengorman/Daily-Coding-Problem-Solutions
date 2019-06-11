/*
Daily Coding Problem #11: Autocomplete System

This problem was asked by Twitter.

Implement an autocomplete system. That is, given a query string s and a set of all possible query
strings, return all strings in the set that have s as a prefix.

For example, given the query string de and the set of strings [dog, deer, deal], return [deer, deal].

Hint: Try preprocessing the dictionary into a more efficient data structure to speed up queries.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;

/*
I chose to construct a tree to make queries very quick. The idea is that each character in the
query corresponds to a path down the tree, thus limitting the number of results for each character.

Nodes hold values that are only used when the node is a leaf. Querying traverses down the tree
character by character. Once the traversal is complete, we return all leaves of this subtree.
*/
struct Node {
    string val;
    unordered_map<char, Node*> next;
    Node(string s) : val(s) {}
};

/*
Initially, nodes are not inserted at the full character path of the string. This would be
unnecessary in most cases.
For example:
Dictionary with words: abc, def, ghi
It would not be necessary to store abc at a->b->c because there is nothing else in a. So we can
store abc in a.

When a new word comes into the dictionary at the same path, the node is given two new children: one
for the new word and one for the word that was stored there initially.
*/
void insertNode(string s, Node* root) {
    for(int i = 0; i < s.length(); i++) {
        char c = s[i];
        if(root->next.find(c) == root->next.end()) {
            // key does not yet exist in map - insert
            Node* newNode = new Node(s);
            root->next.insert(make_pair(c, newNode));
            break;
        } else {
            // need to separate nodes. move old value down in the tree
            Node* moveNode = new Node(root->next[c]->val);
            root->next[c]->val = "";
            root->next[c]->next.insert(make_pair(moveNode->val[i+1], moveNode));
        }
        root = root->next[c];
    }
}

Node* constructTree(vector<string> dictionary) {
    Node* root = new Node("");
    for(string s : dictionary) {
        insertNode(s, root);
    }
    return root;
}


void addAllDescendants(Node* root, vector<string>* v) {
    if(root->val != "") {
        v->push_back(root->val);
        return;
    }
    for(auto it : root->next) {
        addAllDescendants(it.second, v);
    }
}

vector<string> query(Node* root, string q) {
    for(char c : q) {
        if(root->next.find(c) == root->next.end()) {
            // query not found
            return vector<string>(1, "ERROR: No results for query: " + q);
        }
        if(root->next[c]->val != "" && root->next[c]->val.find(q) == 0) {
            // we've hit a leaf that contains our query
            return vector<string>(1, root->next[c]->val);
        }
        root = root->next[c];
    }
    vector<string> ret;
    addAllDescendants(root, &ret);
    return ret;
}

/*
taking in arguments in the form:

s1, s2, ..., sn
q

where si is the ith string in the list, n is the length of the list, and q is the query string
*/
int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> dictionary((istream_iterator<string>(iss)), istream_iterator<string>());
    string q;
    cin >> q;

    Node* root = constructTree(dictionary);
    vector<string> results = query(root, q);
    for(string s : results) {
        printf("\t%s\n", s.c_str());
    }

    return 0;
}