/*
Daily Coding Problem #15: Random Stream Element

This problem was asked by Facebook.

Given a stream of elements too large to store in memory, pick a random element from the stream with
uniform probability.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


/*
When I first read this problem I did not understand it properly. I made the assumption that I was
being given the stream length, and so my solution was to find a random number between 0 and the
stream length, wait until that many numbers had come through the function, and then return that
number.

I thought that this was probably too easy and that I didn't understand the question, so I Googled
it. The solution that popped up was assuming that it wasn't given the length of the stream, and
honestly, I don't think I could have come up with that solution alone, even if I was told that I
don't know the length. Reservoir sampling is a very interesting method that I now am knowledgeable
about thanks to this problem!
*/
int randomSoFar(int n) {
    static int counter = 0;
    static int ret;
    if(counter++ == 0) {
        ret = n;
    }
    else if((rand() % (counter+1)) == counter) {
        ret = n;;
    }
    return ret;
}

int randomWithLength(int n, int length) {
    static int counter = 0;
    static int ret;
    static int index = rand() % length;
    if(counter++ == index) {
        ret = n;
    }
    return ret;
}

int main() {
    srand(time(NULL));
    int n;
    cout << "select stream length:\n> ";
    cin >> n;
    vector<int> stream(n);
    for(int i = 0; i < n; i++) {
        stream[i] = i+1;
    }

    int ans;
    for(int i = 0; i < stream.size(); i++) {
        ans = randomSoFar(stream[i]);
    }
    cout << ans << endl;

    return 0;
}