/*
Daily Coding Problem #13: Longest Distinct Substring

This problem was asked by Amazon.

Given an integer k and a string s, find the length of the longest substring that contains at most k
distinct characters.

For example, given s = "abcba" and k = 2, the longest substring with k distinct characters is "bcb".
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>

using namespace std;

/*
This is a greedy solution that iterates through the string with a front and back index.
A map is used to track the frequency of characters in the current substring [front, back).
When the map is full (k chars in the map) and we encounter a new char, we move the front index
forward while decrmenting the front char's frequency in the map. If the frequency is zero, we
remove the char from the map, opening up a new space for the next char.

For example:
s = abacaa, k = 2
- Move back forward, adding elements to the map. Stop once the map is full and we encounter a new char
    - a->1
    - a->1, b->1
    - a->2, b->1
    - hit c, stop.
- c is not found in the map, and the map is full. This means we have found the end of a 2-distinct substring
    - Calculate the length and update max if necessary
        - back - front = 3 (length of "aba")
    - Move front forward, removing elements from the map until there is only one char in the map
        - a->1, b->1
        - a->1
    - now front is at s[2] ('a')
- Repeat until back hits the end of the string
    - a->1, c->1
    - a->2, c->1
    - a->3, c->1
    - END. back - front = 4 (length of "acaa")
*/
string solution(string s, int k) {
    unordered_map<char, int> seen;
    int front = 0;
    int back = 0;
    int maxLength = 0;
    int maxIndex = 0;
    while(back != s.length()) {
        if(seen.find(s[back]) == seen.end()) {
            // new char not in map
            if(seen.size() == k) {
                // map is full, new char not a part of last distinct substring
                if(back - front > maxLength) {
                    maxLength = back - front;
                    maxIndex = front;
                }
            }
            while(seen.size() == k) {
                // map is full, remove front elements until there is space for new char
                // decrement the char frequency
                if(--seen[s[front]] == 0) {
                    // no more chars left
                    seen.erase(s[front]);
                }
                front++;
            }
            seen.insert(make_pair(s[back++], 1));
        } else {
            seen[s[back++]]++;
        }
    }
    if(back - front > maxLength) {
        maxLength = back - front;
        maxIndex = front;
    }
    return s.substr(maxIndex, maxLength);
}


int main() {
    string s;
    int k;
    cin >> s >> k;
    cout << solution(s, k) << endl;
    return 0;
}