/*
Daily Coding Problem #4: First Missing Positive

This problem was asked by Stripe.

Given an array of integers, find the first missing positive integer in linear time and constant
space. In other words, find the lowest positive integer that does not exist in the array. The array
can contain duplicates and negative numbers as well.

For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.

You can modify the input array in-place.
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


int solution(vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        // flipping current element with element at index {element} (-1 to start at 0)
        // for example, if current = 1, insert current into v[0].
        // this keeps track of contiguous numbers starting at 1.
        int temp;
        if(v[i] > 0 && v[i] <= v.size() && v[i] != v[v[i]-1]) {
            temp = v[v[i]-1];
            v[v[i]-1] = v[i];
            v[i] = temp;
            i--;    // do this again to hit the flipped number
        }
    }
    int i;
    for(i = 0; i < v.size(); i++) {
        if(v[i] != i+1) {
            return i+1;
        }
    }
    return i+1;
}

// O(nlogn solution)
int sortSolution(vector<int> v) {
    sort(v.begin(), v.end());
    int counter = 1;
    for(int n : v) {
        if(n > counter) {
            return counter;
        }
        if(n == counter) {
            counter++;
        }
        // else n < counter, continue (duplicate or < 1)
    }
    return counter;
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

    cout << solution(v) << endl;
    return 0;
}