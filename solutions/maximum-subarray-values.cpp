/*
Daily Coding Problem #18: Maximum Subarray Values

This problem was asked by Google.

Given an array of integers and a number k, where 1 <= k <= length of the array, compute the maximum
values of each subarray of length k.

For example, given array = [10, 5, 2, 7, 8, 7] and k = 3, we should get: [10, 7, 8, 8], since:

10 = max(10, 5, 2)
7 = max(5, 2, 7)
8 = max(2, 7, 8)
8 = max(7, 8, 7)
Do this in O(n) time and O(k) space. You can modify the input array in-place and you do not need to
store the results. You can simply print them out as you compute them.
*/

#include <iostream>
#include <deque>
#include <vector>
#include <sstream>

using namespace std;

/*
After struggling with this problem for a long time, a friend told me to try using a double-ended
queue, a deque. We'll track our window by storing indeces in the deque. At each point we add new
elements to the window and remove the elements that are no longer in the window.

It's important to note that when adding a number to the window, all of the previous elements in the
window that are smaller no longer matter. None of them will be the max value in the current window
or in any future window (because the new value is larger), so we can remove these values.

This results in the deque always being sorted high to low, so the max is always at the front.
*/
void solution(vector<int> v, int k) {
    deque<int> deq;
    for(int i = 0; i < v.size(); i++) {
        // remove elements that are out of the window
        while(!deq.empty() && deq.front() <= i - k) {
            deq.pop_front();
        }
        // remove previous elements that are smaller than the current
        while(!deq.empty() && v[deq.back()] < v[i]) {
            deq.pop_back();
        }
        deq.push_back(i);
        // print the current max
        if(i >= k - 1) {
            cout << v[deq.front()] << endl;
        }
    }
}

int main() {
    int k;
    vector<int> v;
    string arrayStr;
    printf("Enter array:\n> ");
    getline(cin, arrayStr);
    stringstream ss(arrayStr);
    while(!ss.eof()) {
        ss >> k;
        v.push_back(k);
    }
    printf("Enter k:\n> ");
    cin >> k;
    solution(v, k);
    return 0;
}