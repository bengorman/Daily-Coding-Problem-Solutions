/*
Daily Coding Problem #19: Coloring Houses

This problem was asked by Facebook.

A builder is looking to build a row of N houses that can be of K different colors. He has a goal of
minimizing cost while ensuring that no two neighboring houses are of the same color.

Given an N by K matrix where the nth row and kth column represents the cost to build the nth house
with kth color, return the minimum cost which achieves this goal.
*/

#include <iostream>
#include<algorithm>

using namespace std;


int solution(int n, int k, int** matrix) {

}

int main() {
    int n, k;
    cout << "Enter matrix dimensions separated by a space (eg. \"N K\"):\n> ";
    cin >> n >> k;
    cout << "Enter matrix separated by spaces and newlines:\n";
    int** matrix = new int*[n];
    for(int i = 0; i < n; i++) {
        matrix[i] = new int[k];
        for(int j = 0; j < k; j++) {
            cin >> matrix[i][j];
        }
    }
    cout << solution(n, k, matrix) << endl;
    return 0;
}