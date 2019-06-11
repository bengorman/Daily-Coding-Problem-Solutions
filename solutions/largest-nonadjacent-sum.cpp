/*
Daily Coding Problem #9: Largest Non-Adjacent Sum

This problem was asked by Airbnb.

Given a list of integers, write a function that returns the largest sum of non-adjacent numbers.
Numbers can be 0 or negative.

For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should
return 10, since we pick 5 and 5.

Follow-up: Can you do this in O(N) time and constant space?
*/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*
I'll admit that this was the first Daily Coding Problem I couldn't get on my own. After coming back
to this problem a couple days in a row I decided to get a little help online. I found that the
solution is a greedy algorithm that tracks the maximum so far if you include the current element
and if you don't.

At each point the new include number becomes the old exclude + the current number because by
including the current number we are exlcluding the last number.
Then the new exclude number becomes the max of the old exclude and include because both of these
numbers do not yet include the current number, so we take the highest.

This is an O(n) solution that requires only one pass through the array and constant space.
*/
int solution(vector<int> vec) {
    int include = vec[0];
    int exclude = 0;
    int temp;
    for(int i = 1; i < vec.size(); i++) {
        temp = include;
        include = exclude + vec[i];
        exclude = max(temp, exclude);
    }
    return max(include, exclude);
}

int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> vec((istream_iterator<int>(iss)), istream_iterator<int>());
    cout << solution(vec) << endl;
    return 0;
}