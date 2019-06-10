/*
Daily Coding Problem #1: Pair in Array Sum

This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

// O(n) solution (single pass)
bool solution(int k, vector<int> v) {
    // tracking elements seen so far
    unordered_set<int> seen;
    for(int i = 0; i < v.size(); i++) {
        // if we've seen an number that can add with the current number to k, we are done
        if(seen.find(k - v[i]) != seen.end()) {
            return true;
        }
        // otherwise, track this element
        seen.insert(v[i]);
    }
    return false;
}

/*
taking in arguments in the form:

k
a0, a1, a2, ..., an

where ai is the ith element in the list and n is the length of the list
*/
int main() {
    int k;
    cin >> k;
    cin.ignore();
    vector<int> v;
    string arrayStr;
    getline(cin, arrayStr);
    stringstream ss(arrayStr);
    int temp;
    while(!ss.eof()) {
        ss >> temp;
        v.push_back(temp);
    }

    cout << (solution(k, v) ? "TRUE" : "FALSE") << endl;
    return 0;
}