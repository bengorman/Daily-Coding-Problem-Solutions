/*
Daily Coding Problem #2: Product of Other Elements

This problem was asked by Uber.

Given an array of integers, return a new array such that each element at index i of the new array
is the product of all the numbers in the original array except the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. 
f our input was [3, 2, 1], the expected output would be [2, 3, 6].

Follow-up: what if you can't use division?
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>

using namespace std;

// O(n) solution
vector<int> solution(vector<int> v) {
    // first find the product of all numbers in the list
    int product = 1;
    for(int n : v) {
        product *= n;
    }

    for(int i = 0; i < v.size(); i++) {
        // answer for this index is total product divided by current element
        v[i] = product / v[i];
    }
    return v;
}

// O(n^2) solution without division
vector<int> solutionWithoutDivision(vector<int> v) {
    vector<int> sol(v.size(), 1);
    for(int i = 0; i < v.size(); i++) {
        for(int m : v) {
            if(m != v[i]) {
                sol[i] *= m;
            }
        }
    }
    return sol;
}

/*
taking in arguments in the form:

a0, a1, a2, ..., an

where ai is the ith element in the list and n is the length of the list
*/
int main() {
    vector<int> v;
    string arrayStr;
    getline(cin, arrayStr);
    stringstream ss(arrayStr);
    int temp;
    while(!ss.eof()) {
        ss >> temp;
        v.push_back(temp);
    }

    v = solution(v);                    // for alternate solution comment this line
    // v = solutionWithoutDivision(v);  // and uncomment this line
    for(int n : v) {
        printf("%d ", n);
    }
    printf("\n");
    return 0;
}