/*
Daily Coding Problem #12: Staircase Steps

This problem was asked by Amazon.

There exists a staircase with N steps, and you can climb up either 1 or 2 steps at a time. Given N,
write a function that returns the number of unique ways you can climb the staircase. The order of
the steps matters.

For example, if N is 4, then there are 5 unique ways:

1, 1, 1, 1
2, 1, 1
1, 2, 1
1, 1, 2
2, 2

What if, instead of being able to climb 1 or 2 steps at a time, you could climb any number from a
set of positive integers X? For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

/*
My approach to this problem involved a modification on the fibonacci sequence. I figured that
fibonacci would be relavent due to the fact that this problem is concerned with increasingly large
combinatorial possibilities (I just saw something similar in Daily Coding Problem #7: Decode
Combinations).

After writing out some solutions and proofs, I have devised that the formula to answer this problem
is a recurrence relation that takes the step sizes as parameters.
The formula is:
f(n) = f(n-s1) + f(n-s2) + ... + f(n-sm)
where n is the index of the sequence, si is the ith step size, and m is the number of step sizes.

For example:
If the step sizes are 1 and 2 (the original problem), then
f(n) = f(n-1) + f(n-2)
which is just the fibonacci sequence.

I implemented the solution using dynamic programming, building up the solution one number at a time.
This solution has time complexity of O(n) (assuming constant number of step sizes - O(nm) otherwise).
It also uses O(n) space.

I believe there is a solution that could use less space because we do not need to track every
single number in the sequence forever. We do, however need to track back to the highest step size
(starting with the lowest).

For example:
If the step sizes are 2 and 4, then we only need to track the (i-2)th, (i-3)th, and (i-4)th elements.
But considering the worst case that our minimum and maximum step sizes are very far apart (close to n
apart), this would still require O(n) space, so I chose not to implement this optimization.
*/
int solution(vector<int> v, int n) {
    int f[n+2];
    int i;
    f[0] = 1;
    for(i = 1; i <= n; i++) {
        f[i] = 0;
        for(int m : v) {
            f[i] += (i-m < 0 ? 0 : f[i-m]);
        }
    }
    return f[n];
}

/*
taking input in the form

a1, a2, ... , am
n

where ai is the ith step size, m is the number of step sizes, and n is the number of stairs in the
staircase.
*/
int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> v((istream_iterator<int>(iss)), istream_iterator<int>());
    int n;
    cin >> n;

    cout << solution(v, n) << endl;
    return 0;
}