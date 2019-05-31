/*
Daily Coding Problem # 1: Pair in Array Sum

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

bool solution(int k, vector<int> vec) {
    unordered_set<int> seen;
    for(int i = 0; i < vec.size(); i++) {
        if(seen.find(k - vec[i]) != seen.end()) {
            return true;
        }
        seen.insert(vec[i]);
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
    vector<int> vec;
    string arrayStr;
    getline(cin, arrayStr);
    stringstream ss(arrayStr);
    int temp;
    while(!ss.eof()) {
        ss >> temp;
        vec.push_back(temp);
    }
    cout << (solution(k, vec) ? "TRUE" : "FALSE") << endl;
    return 0;
}