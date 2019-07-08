/*
Daily Coding Problem #19: Coloring Houses

This problem was asked by Facebook.

A builder is looking to build a row of N houses that can be of K different colors. He has a goal of
minimizing cost while ensuring that no two neighboring houses are of the same color.

Given an N by K matrix where the nth row and kth column represents the cost to build the nth house
with kth color, return the minimum cost which achieves this goal.
*/

/*
house   red     green   blue
1       4       8       5
2       1       3       3
3       3       6       7
4       6       7       3
5       6       7       2
6       1       3       8
7       5       1       8
*/



#include <iostream>

using namespace std;


int DPSolution2(int N, int K, int** matrix) {
    int prevMin = INT_MAX;
    int prevSecond = INT_MAX;
    int prevIndex = -1;
    for(int i = 0; i < N; i++) {
        int currMin = INT_MAX;
        int currSecond = INT_MAX;
        int currIndex = -1;
        for(int j = 0; j < K; j++) {
            if(prevIndex == j) {
                matrix[i][j] += prevSecond;
            } else {
                matrix[i][j] += prevMin;
            }

            if(matrix[i][j] <= currMin) {
                currSecond = currMin;
                currMin = matrix[i][j];
                currIndex = j;
            }
        }
        prevMin = currMin;
        prevSecond = currSecond;
        prevIndex = currIndex;
    }

    return prevMin;
}

int DPSolution1(int N, int K, int** matrix) {
    int* currentCost = new int[K];
    for(int j = 0; j < K; j++) {
        currentCost[j] = matrix[0][j];
    }
    int min;
    for(int i = 1; i < N; i++) {
        for(int j = 0; j < K; j++) {
            min = INT_MAX;
            for(int k = 0; k < K; k++) {
                if(k != j && matrix[i-1][k] < min) {
                    min = matrix[i-1][k];
                }
            }
            currentCost[j] += min;
        }
    }
    min = INT_MAX;
    for(int j = 0; j < K; j++) {
        if(currentCost[j] < min) {
            min = currentCost[j];
        }
    }
    return min;
}

/*
Taking input in the form:

N K
a11 a12 ... a1K
a21 a22      :
:            :
aN1 ... ... aNK

where aij is the cost to paint the ith house the jth color
*/
int main() {
    int N, K;
    cin >> N >> K;
    int** matrix = new int*[N];
    for(int i = 0; i < N; i++) {
        matrix[i] = new int[K];
        for(int j = 0; j < K; j++) {
            cin >> matrix[i][j];
        }
    }
    cout << DPSolution1(N, K, matrix) << endl;
    return 0;
}