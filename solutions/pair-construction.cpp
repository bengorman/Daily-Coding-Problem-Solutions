/*
Daily Coding Problem #5: Pair Construction

This problem was asked by Jane Street.

cons(a, b) constructs a pair, and car(pair) and cdr(pair) returns the first and last element of
that pair. For example, car(cons(3, 4)) returns 3, and cdr(cons(3, 4)) returns 4.

Given this implementation of cons:

def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair
Implement car and cdr.
*/

#include <iostream>
#include <utility>

using namespace std;

pair<int, int> cons(int a, int b) {
    return make_pair(a, b);
}

int car(pair<int, int> p) {
    return p.first;
}

int cdr(pair<int, int> p) {
    return p.second;
}

int main() {
    cout << car(cons(3,4)) << endl;
    cout << cdr(cons(3,4)) << endl;
}